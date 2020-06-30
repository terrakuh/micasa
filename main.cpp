#include "src/config/main.hpp"

#include "src/image/manager.hpp"
#include "src/main_window.hpp"

#include <QApplication>

int main(int argc, char** argv)
{
	QApplication app{ argc, argv };

	micasa::config::load("settings.json");
	micasa::image::manager::init("sample_images/test.png");

	micasa::main_window window;

	return app.exec();
}
