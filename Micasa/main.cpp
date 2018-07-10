#include "main_window.hpp"

#include <QtWidgets\QApplication>
#include <QtCore\QResource>
#include <Windows.h>


#if not defined(_DEBUG)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char ** argv)
#endif
{
	int _argc = 0;
	auto _argv = CommandLineToArgvW(GetCommandLineW(), &_argc);

#if not defined(_DEBUG)
	if (_argc <= 1 || !_argv) {
		return 1;
	}
#endif

	QApplication app(_argc, reinterpret_cast<char**>(_argv));
	
	// Register resources
	QResource::registerResource("resources.rcc");
	
	main_window _main;

#if not defined(_DEBUG)
	_main.get_image()->load_resource(_argv[1]);
#else
	_main.get_image()->load_resource(L"p:/test.gif");
#endif

	_main.show();

	return app.exec();
}
