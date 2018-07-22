#pragma once

#include <algorithm>
#include <memory>
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


class image_item : public QGraphicsPixmapItem, public viewable_item, public editable_item
{
public:
	image_item();
	virtual void open_with() override;
	virtual void set_diashow_time(std::chrono::milliseconds _time) override;
	virtual void play() override;
	virtual void pause() override;
	virtual void rewind() override;
	virtual void reverse() override;
	virtual void copy() override;
	virtual void delete_from_disk() override;
	virtual void hide() override;
	virtual void cut() override;
	virtual void resize() override;
	virtual void rotate_clockwise() override;
	virtual void rotate_counterclockwise() override;
	virtual void quit() override;
	virtual void center_item() override;
	void toggle_fullscreen();
	virtual bool load_resource(const wchar_t * _path) override;
	std::chrono::milliseconds get_diashow_time() const;
	context_menu & get_context_menu();
	static const wchar_t * get_filter_rule();

protected:
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * _event) override;

private:
	bool _fullscreen;
	bool _play;
	bool _reversed;
	int _movie_id;
	std::chrono::milliseconds _diashow_time;
	QSize _current_size;
	QSize _scene_size;
	std::unique_ptr<QMovie> _movie;
	QPixmap _original_image;
	context_menu _context_menu;

	void show_next_movie_frame(int _id);
	bool scale_view(QSize & _size);
};