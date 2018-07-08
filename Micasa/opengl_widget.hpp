#pragma once

#include <cstdint>
#include <memory>
#include <QtWidgets\QOpenGLWidget>
#include <QtGui\QPainter>
#include <QtGui\QPixmap>
#include <QtWidgets\QApplication>

#include "background.hpp"


class opengl_widget : public QOpenGLWidget
{
public:
	opengl_widget(QWidget * _parent) : QOpenGLWidget(_parent), _pixmap("P:/test.jpg")
	{
		_background.take_background();
		_background.cut_area(QRect(100, 500, 1000, 300));
	}

protected:
	virtual void paintGL() override
	{
		QPainter _painter;

		_painter.begin(this);
		
		_background.draw_background(_painter);
		//paint_image(_painter);
		//paint_overlay(_painter);

		_painter.end();
	}

private:
	QPixmap _pixmap;
	background _background;

	//void paint_image(QPainter & _painter);
	//void paint_overlay(QPainter & _painter);
};