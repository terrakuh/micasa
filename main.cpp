#include "src/config/main.hpp"

#include "src/main_window.hpp"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char** argv)
{
	QApplication app{ argc, argv };

	micasa::config::load("settings.json");

	micasa::main_window window;

	window.show();

	return app.exec();
}
