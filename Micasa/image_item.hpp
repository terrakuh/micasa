#pragma once

#include <functional>
#include <QtWidgets\QApplication>
#include <QtWidgets\QDesktopWidget>
#include <QtWidgets\QGraphicsItem>
#include <QtWidgets\QGraphicsScene>
#include <QtGui\QCursor>
#include <QtGui\QScreen>
#include <QtGui\QPixmap>
#include <QtGui\QMovie>
#include <QtCore\QFileInfo>
#include <QtCore\QTimer>


class image_item : public QGraphicsPixmapItem
{
public:
	image_item();
	void center_item();
	void load_resource(const wchar_t * _path);

private:
	QSize _current_size;
	QSize _scene_size;
	QMovie * _movie;
	double _normal_scale;

	void show_next_movie_frame();
	void set_size(const QSize & _size);
};