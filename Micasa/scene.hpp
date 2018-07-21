#pragma once

#include <QtWidgets\QGraphicsScene>
#include <QtWidgets\QGraphicsSceneMouseEvent>
#include <QtGui\QPainter>
#include <QtGui\QKeyEvent>
#include <QtCore\QObject>
#include <QtCore\QPropertyAnimation>
#include <future>

#include "folder_view.hpp"
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
	void blacken_background(bool _blacken);
	void set_background();
	bool open(const wchar_t * _path);
	double get_image_scale();
	image_item * get_image();

protected:
	virtual void keyPressEvent(QKeyEvent * _event) override;
	/*virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent * _event) override
	{
		puts("hi");
	}*/
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

private:
	static std::wregex _filter;
	folder_view _folder_view;
	QPixmap _background;
	image_item * _image;
};