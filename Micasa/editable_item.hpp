#pragma once

#include <chrono>


class editable_item
{
public:
	virtual void open_with() = 0;
	virtual void set_diashow_time(std::chrono::milliseconds _time) = 0;
	virtual void play() = 0;
	virtual void pause() = 0;
	virtual void rewind() = 0;
	virtual void reverse() = 0;
	virtual void copy() = 0;
	virtual void delete_from_disk() = 0;
	virtual void hide() = 0;
	virtual void cut() = 0;
	virtual void resize() = 0;
	virtual void rotate_clockwise() = 0;
	virtual void rotate_counterclockwise() = 0;
	virtual void quit() = 0;
};