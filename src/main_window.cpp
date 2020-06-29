#include "main_window.hpp"
#include "config/main.hpp"
#include <QApplication>
#include <QKeyEvent>

using namespace micasa;

main_window::main_window()
{
	setWindowOpacity(config::get().theme.opacity);
	setStyleSheet("QWidget{background: " + config::get().theme.background + "}");
	setWindowFlags(Qt::FramelessWindowHint);
	setWindowState(Qt::WindowFullScreen);
}

void main_window::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape) {
		QApplication::quit();
		event->accept();
	}
}
