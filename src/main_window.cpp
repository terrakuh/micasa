#include "main_window.hpp"

#include "config/main.hpp"

#include <QApplication>
#include <QGraphicsOpacityEffect>
#include <QKeyEvent>

using namespace micasa;

main_window::main_window()
{
	_background        = new QWidget(this);
	_view              = new image::view{ this };
	const auto opacity = new QGraphicsOpacityEffect{ _background };

	opacity->setOpacity(config::get().theme.opacity);
	_background->setStyleSheet("background: " + config::get().theme.background);
	_background->setGraphicsEffect(opacity);
	_background->setAutoFillBackground(true);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setCentralWidget(_background);
	setWindowTitle("Micasa");

	_view->show();
	showFullScreen();
}

void main_window::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape) {
		_view->play_finish_and_exit();
		event->accept();
	}
}

void main_window::resizeEvent(QResizeEvent* event)
{
	_view->resize(size());
}
