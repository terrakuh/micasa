#include "main_window.hpp"

#include <QtWidgets\QApplication>
#include <Windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//int main(int argc, char ** argv)
{
	int _argc = 0;
	auto _argv = CommandLineToArgvW(GetCommandLineW(), &_argc);
	
	if (_argc <= 1 || !_argv) {
		return 1;
	}

	QApplication app(_argc, reinterpret_cast<char**>(_argv));

	main_window _main;

	_main.get_image()->load_resource(_argv[1]);
	_main.show();

	return app.exec();
}
