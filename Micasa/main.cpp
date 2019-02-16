#include "main_window.hpp"
#include "thread_pool.h"

#include <QtWidgets\QApplication>
#include <QtCore\QResource>
#include <QtCore\QDir>
#include <QtCore\QFileInfo>
#include <Windows.h>


#if !defined(_DEBUG)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char ** argv)
#endif
{
	if (SUCCEEDED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
		struct terminator
		{
			~terminator()
			{
				CoUninitialize();
			}
		} _terminator;

		int _argc = 0;
		auto _argv = CommandLineToArgvW(GetCommandLineW(), &_argc);

#if !defined(_DEBUG)
		if (_argc <= 1 || !_argv) {
			return 1;
		}
#endif

		QApplication app(_argc, reinterpret_cast<char**>(_argv));
		QDir::setCurrent(QFileInfo(QString::fromWCharArray(_argv[0])).absolutePath());

		// Register resources
		QResource::registerResource(QDir::currentPath() + "/resources.rcc");

		// Create thread pool
		thread_pool::global_thread_pool().reset(new thread_pool(1));

		main_window _main;

		// Load image
		_main.get_scene()->open(
#if !defined(_DEBUG)
		_argv[1]
#else
		L"d:/test.jpg"
#endif
		);

		_main.show();

		return app.exec();
	}

	return 1;
}
