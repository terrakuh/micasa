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
#include "settings.hpp"
#include "scene.hpp"


class main_window : public QMainWindow
{
public:
	main_window();
	~main_window();
	void set_background();
	image_item * get_image();

protected:
	virtual void keyPressEvent(QKeyEvent * _event) override;
	virtual void showEvent(QShowEvent * event) override;

private:
	Ui_MainWindow _ui;
	scene * _scene;
};