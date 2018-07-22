#pragma once

#include <functional>
#include <QtWidgets\QMenu>

#include "editable_item.hpp"


class context_menu
{
public:
	enum class ACTIVE_MENU
	{
		IMAGE,
		MOVIE
	};

	context_menu(editable_item * _editable);
	void set_active_menu(ACTIVE_MENU _menu);
	void show_active_menu(const QPoint & _position);
	ACTIVE_MENU get_active_menu() const;
	
private:
	ACTIVE_MENU _menu;
	QMenu _image;
	QMenu _movie;
	QMenu _diashow;
	editable_item * _editable;
};