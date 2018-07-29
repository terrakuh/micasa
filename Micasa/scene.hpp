#pragma once

#include <cmath>
#include <QtWidgets\QGraphicsScene>
#include <QtWidgets\QGraphicsSceneMouseEvent>
#include <QtWidgets\QDesktopWidget>
#include <QtGui\QPainter>
#include <QtGui\QKeyEvent>
#include <QtCore\QObject>
#include <QtCore\QPropertyAnimation>
#include <QtCore\QTimeLine>

#include "folder_view.hpp"
#include "image_item.hpp"
#include "pixmap_item.hpp"
#include "config.hpp"
#include "thread_pool.h"


class scene : public QGraphicsScene
{
	Q_OBJECT
	Q_PROPERTY(double image_scale READ get_image_scale WRITE set_image_scale)
		
public:
	scene(QWidget * _parent, const QSize & _size);
	virtual ~scene();

	void set_image_scale(double _factor);
	void show_animation();
	void close_animation_and_quit();
	void blacken_background(bool _blacken);
	void set_background();
	void toggle_diashow();
	bool open(const wchar_t * _path);
	bool next_item(bool _prev);
	double get_image_scale();
	image_item * get_image();

protected:
	virtual void timerEvent(QTimerEvent * _event) override;
	virtual void keyPressEvent(QKeyEvent * _event) override;
	virtual void keyReleaseEvent(QKeyEvent * _event) override;
	virtual void wheelEvent(QGraphicsSceneWheelEvent * _event) override;
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
	int _d;
	int _g;
	int _diashow_timer;
	static std::wregex _filter;
	folder_view _folder_view;
	QPixmap _background;
	QTimeLine _scaler;
	image_item * _image;

	
	static double image_scaling_function(double _x);
};