#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <vector>
#include <memory>


class thread_pool
{
public:
	typedef std::function<void()> task_type;

	thread_pool(unsigned int _pool_size);
	~thread_pool();
	void terminate();
	bool queue(task_type && _task);
	static std::shared_ptr<thread_pool> & global_thread_pool();

private:
	static std::shared_ptr<thread_pool> _global_thread_pool;
	std::vector<std::thread> _workers;
	std::queue<task_type> _tasks;
	std::mutex _mutex;
	std::condition_variable _cv;
	bool _stop;

	void worker_main();
};