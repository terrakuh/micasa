#include "main_window.hpp"

#include <QtWidgets\QApplication>

#pragma comment(lib, "Qt5Cored.lib")
#pragma comment(lib, "Qt5Guid.lib")
#pragma comment(lib, "Qt5Widgetsd.lib")


//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	main_window _main;

	_main.get_image()->load_resource(L"P:/test.jpg");
	_main.show();

	return app.exec();
}
