#pragma once


#include "main_window_ui.hpp"
#include "image_window.hpp"


class main_window : public QMainWindow
{
public:
	main_window() : _image(this)
	{
		_ui.setupUi(this);
		_ui.retranslateUi(this);

		setWindowState(windowState() | Qt::WindowFullScreen);

		//connect(_ui.pushButton, &QPushButton::clicked, &QApplication::quit);
	}
	image_window & get_image()
	{
		return _image;
	}

private:
	Ui_MainWindow _ui;
	image_window _image;
};