#pragma once

#include <algorithm>
#include <QtWidgets\QApplication>
#include <QtWidgets\QDesktopWidget>
#include <QtWidgets\QGraphicsItem>
#include <QtWidgets\QGraphicsScene>
#include <QtWidgets\QMenu>
#include <QtWidgets\QGraphicsSceneEvent>
#include <QtGui\QCursor>
#include <QtGui\QScreen>
#include <QtGui\QPixmap>
#include <QtGui\QMovie>
#include <QtCore\QFileInfo>
#include <QtCore\QTimer>

#include "viewable_item.hpp"
#include "context_menu.hpp"


class image_item : public QGraphicsPixmapItem, public viewable_item
{
public:
	image_item();
	virtual void center_item() override;
	virtual bool load_resource(const wchar_t * _path) override;
	context_menu & get_context_menu();

protected:
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * _event) override;

private:
	bool _fullscreen;
	QSize _current_size;
	QSize _scene_size;
	QMovie * _movie;
	QPixmap _original_image;
	context_menu _menu;

	void show_next_movie_frame();
	bool scale_view(QSize & _size);
};