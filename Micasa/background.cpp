#include "background.hpp"

void background::take_background()
{
	auto _screen = QApplication::primaryScreen();

	_background = _screen->grabWindow(0);
}

void background::draw_background(QPainter & _painter)
{
	// Draw left rect
	draw_area(0, 0, _cut_area.x(), _background.height(), _painter, _drawn_area[0]);

	// Draw right rect
	draw_area(_cut_area.x() + _cut_area.width(), 0, _background.width(), _background.height(), _painter, _drawn_area[1]);

	// Draw top rect
	draw_area(_cut_area.x(), 0, _cut_area.x() + _cut_area.width(), _cut_area.y(), _painter, _drawn_area[2]);

	// Draw bottom rect
	draw_area(_cut_area.x(), _cut_area.y() + _cut_area.height(), _cut_area.x() + _cut_area.width(), _background.height(), _painter, _drawn_area[3]);
}

void background::cut_area(const QRect & _area)
{
	_cut_area = _area;
}

void background::draw_area(int _x1, int _y1, int _x2, int _y2, QPainter & _painter, QRect & _drawn)
{
	// Don't draw


	_x2 -= _x1;
	_y2 -= _y1;

	_painter.drawPixmap(_x1, _y1, _x2, _y2, _background, _x1, _y1, _x2, _y2);
}
