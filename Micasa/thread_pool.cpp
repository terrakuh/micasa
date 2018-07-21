#include "thread_pool.h"


std::shared_ptr<thread_pool> thread_pool::_global_thread_pool;

thread_pool::thread_pool(unsigned int _pool_size)
{
	_workers.resize(_pool_size);
	_stop = false;

	// Start all workers
	while (_pool_size--) {
		_workers[_pool_size] = std::thread(&thread_pool::worker_main, this);
	}
}

thread_pool::~thread_pool()
{
	terminate();

	// Wait for all workers
	for (auto & _worker : _workers) {
		_worker.join();
	}
}

void thread_pool::terminate()
{
	std::unique_lock<std::mutex> _lck(_mutex);

	_stop = true;
	
	while (!_tasks.empty()) {
		_tasks.pop();
	}

	_lck.unlock();
	_cv.notify_all();
}

bool thread_pool::queue(task_type && _task)
{
	if (!_stop && _task) {
		std::unique_lock<std::mutex> _lck(_mutex);

		_tasks.emplace(std::move(_task));

		_lck.unlock();
		_cv.notify_one();
	}

	return false;
}

std::shared_ptr<thread_pool> & thread_pool::global_thread_pool()
{
	return _global_thread_pool;
}

void thread_pool::worker_main()
{
	task_type _task;

	while (true) {
		{
			std::unique_lock<std::mutex> _lck(_mutex);

			_cv.wait(_lck, [this]() {
				return _stop || !_tasks.empty();
			});

			// Stop
			if (_stop) {
				break;
			}

			// Get task
			_task = std::move(_tasks.front());

			_tasks.pop();
		}

		// Execute task
		_task();
	}
}

