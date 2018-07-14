#pragma once

#include <algorithm>
#include <QtWidgets\QApplication>
#include <QtWidgets\QDesktopWidget>
#include <QtWidgets\QGraphicsItem>
#include <QtWidgets\QGraphicsScene>
#include <QtWidgets\QMenu>
#include <QtGui\QCursor>
#include <QtGui\QScreen>
#include <QtGui\QPixmap>
#include <QtGui\QMovie>
#include <QtCore\QFileInfo>
#include <QtCore\QTimer>

#include "viewable_item.hpp"


class image_item : public QGraphicsPixmapItem, public viewable_item
{
public:
	image_item();
	virtual void center_item() override;
	virtual bool load_resource(const wchar_t * _path) override;

protected:
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent * _event) override;

private:
	QSize _current_size;
	QSize _scene_size;
	QMovie * _movie;
	QPixmap _original_image;
	double _normal_scale;

	void show_next_movie_frame();
	bool scale_view(QSize & _size);
};