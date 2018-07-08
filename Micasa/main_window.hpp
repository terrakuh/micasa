#pragma once

#include <QtWidgets\QApplication>
#include <QtWidgets\QDesktopWidget>
#include <QtWidgets\QGraphicsItem>
#include <QtGui\QCursor>
#include <QtGui\QScreen>
#include <QtGui\QPixmap>
#include <QtGui\QMovie>
#include <QtGui\QKeyEvent>
#include <QtCore\QFileInfo>

#include "main_window_ui.hpp"
#include "image_item.hpp"
#include "settings.hpp"


class main_window : public QMainWindow
{
public:
	main_window();
	~main_window();
	void set_background();
	image_item * get_image();

protected:
	virtual void keyPressEvent(QKeyEvent * _event) override;

private:
	Ui_MainWindow _ui;
	image_item * _image;
};