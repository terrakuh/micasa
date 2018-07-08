#pragma once

#include <QtWidgets\QApplication>
#include <QtWidgets\QDesktopWidget>
#include <QtWidgets\QGraphicsItem>
#include <QtGui\QCursor>
#include <QtGui\QScreen>
#include <QtGui\QPixmap>
#include <QtGui\QMovie>
#include <QtCore\QFileInfo>

#include "main_window_ui.hpp"
#include "image_item.hpp"


class main_window : public QMainWindow
{
public:
	main_window()
	{
		_ui.setupUi(this);
		_ui.retranslateUi(this);

		// Create scene
		auto _size = QApplication::desktop()->size();

		_ui.graphicsView->setScene(new QGraphicsScene(0, 0, _size.width(), _size.height()));
		_ui.graphicsView->scene()->addItem(_image = new image_item());

		// Setup background
		set_background();

		// Open fullscreen
		setWindowState(windowState() | Qt::WindowFullScreen);

		//connect(_ui.pushButton, &QPushButton::clicked, &QApplication::quit);
	}
	void set_background()
	{
		auto _screen = QApplication::primaryScreen();

		_ui.graphicsView->scene()->setBackgroundBrush(QBrush(_screen->grabWindow(0)));
	}
	image_item * get_image()
	{
		return _image;
	}
private:
	Ui_MainWindow _ui;
	image_item * _image;
};