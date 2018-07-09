#pragma once

#include <QtWidgets\QGraphicsScene>
#include <QtWidgets\QGraphicsSceneMouseEvent>
#include <QtCore\QObject>
#include <QtCore\QPropertyAnimation>

#include "image_item.hpp"


class scene : public QGraphicsScene
{
	Q_OBJECT
	Q_PROPERTY(double image_scale READ get_image_scale WRITE set_image_scale)
		
public:
	scene(const QSize & _size);

	void set_image_scale(double _factor);
	void show_animation();
	void close_animation_and_quit();
	double get_image_scale();
	image_item * get_image();

private:
	image_item * _image;
};