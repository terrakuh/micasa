#include "screen.hpp"

#pragma comment(lib, "Qt5Cored.lib")
#pragma comment(lib, "Qt5Guid.lib")
#pragma comment(lib, "Qt5Widgetsd.lib")

#include <iostream>
#include <boost\filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <filesystem>
#include <ShObjIdl.h>
#include <QtGui\QPixmap>
#include <QtWidgets\QDialog>
#include <QtGui\QKeyEvent>
#include <QtGui\QMovie>
#include <QtWidgets\QApplication>
#include "main_window.hpp"
#include <SQLiteCpp\Database.h>
#include <SQLiteCpp\Statement.h>
using namespace boost::filesystem;
namespace fs = std::filesystem;

#include <QtCore\QDir>
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	main_window _main;
	//_main.get_image().load_resource(L"P:/test.jpg");
	//_main.get_image().showing_animation();
	_main.show();
	return app.exec();

	//char ** w = nullptr;
	/*QApplication as(argc, argv);
	Ma a;
	//a.setWindowFlags(Qt::FramelessWindowHint);
	a.show();
	//a.cc.show();
	return as.exec();*/
	system("pause");


	/*if (args <= 1) {
		return 0;
	}*/

	screen::initialize(GetModuleHandle(0), 0, 0, 0);
	screen::show();
	screen::show_image(L"P:/test.jpg");
	//screen::show_image(argv[1]);
	screen::main();
}
