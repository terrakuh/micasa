#pragma once

#include <QtWidgets\QApplication>
#include <QtWidgets\QDesktopWidget>
#include <QtWidgets\QGraphicsItem>
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
	QMovie * _movie;

	void show_next_movie_frame();
};