#pragma once

#include <QtWidgets\QGraphicsScene>
#include <QtWidgets\QGraphicsSceneMouseEvent>
#include <QtCore\QObject>
#include <QtCore\QPropertyAnimation>

#include "image_item.hpp"
#include "pixmap_item.hpp"
#include "config.hpp"


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
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent * _event) override
	{
		puts("hi");
	}
	virtual void dragEnterEvent(QGraphicsSceneDragDropEvent * _event) override
	{
		for (auto _item : items()) {
			if (_item != _image) {
				_item->hide();
			}
		}
	}
	virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent * _event) override
	{
		for (auto _item : items()) {
			if (_item != _image) {
				_item->show();
			}
		}
	}

	image_item * _image;
};