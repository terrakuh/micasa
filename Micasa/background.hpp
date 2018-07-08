#pragma once

#include <QtCore\QRect>
#include <QtGui\QPainter>
#include <QtGui\QPixmap>
#include <QtWidgets\QApplication>
#include <QtGui\QScreen>


class background
{
public:
	void take_background();
	void draw_background(QPainter & _painter);
	void cut_area(const QRect & _area);

private:
	QPixmap _background;
	QRect _cut_area;
	QRect _drawn_area[4];

	void draw_area(int _x, int _y, int _width, int _height, QPainter & _painter, QRect & _drawn);
};