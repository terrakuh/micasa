#include "context_menu.hpp"

context_menu::context_menu(editable_item * _editable)
{
	// Image context menu
	_image.addAction("Open with...", std::bind(&editable_item::open_with, _editable));
	_image.addSeparator();
	_image.addAction("Copy", std::bind(&editable_item::copy, _editable));
	_image.addAction("Delete", std::bind(&editable_item::delete_from_disk, _editable));
	_image.addAction("Hide", std::bind(&editable_item::hide, _editable));
	_image.addSeparator();
	_image.addAction("Cut", std::bind(&editable_item::cut, _editable));
	_image.addAction("Resize", std::bind(&editable_item::resize, _editable));
	_image.addAction("Rotate clockwise", std::bind(&editable_item::rotate_clockwise, _editable));
	_image.addAction("Rotate counterclockwise", std::bind(&editable_item::rotate_counterclockwise, _editable));
	_image.addSeparator();
	_image.addAction("Quit", std::bind(&editable_item::quit, _editable));

	// Movie context menu
	_movie.addAction("Open with...", std::bind(&editable_item::open_with, _editable));
	_movie.addSeparator();
	_movie.addAction("Play", std::bind(&editable_item::play, _editable));
	_movie.addAction("Pause", std::bind(&editable_item::pause, _editable));
	_movie.addAction("Rewind", std::bind(&editable_item::rewind, _editable));
	_movie.addAction("Reverse", std::bind(&editable_item::reverse, _editable));
	_movie.addSeparator();
	_movie.addAction("Copy", std::bind(&editable_item::copy, _editable));
	_movie.addAction("Delete", std::bind(&editable_item::delete_from_disk, _editable));
	_movie.addAction("Hide", std::bind(&editable_item::hide, _editable));
	_movie.addSeparator();
	_movie.addAction("Cut", std::bind(&editable_item::cut, _editable));
	_movie.addAction("Resize", std::bind(&editable_item::resize, _editable));
	_movie.addAction("Rotate clockwise", std::bind(&editable_item::rotate_clockwise, _editable));
	_movie.addAction("Rotate counterclockwise", std::bind(&editable_item::rotate_counterclockwise, _editable));
	_movie.addSeparator();
	_movie.addAction("Quit", std::bind(&editable_item::quit, _editable));
}

void context_menu::set_active_menu(ACTIVE_MENU _menu)
{
	this->_menu = _menu;
}

void context_menu::show_active_menu(const QPoint & _position)
{
	switch (_menu) {
	case ACTIVE_MENU::IMAGE:
		_image.exec(_position);

		break;
	case ACTIVE_MENU::MOVIE:
		_movie.exec(_position);

		break;
	}
}

context_menu::ACTIVE_MENU context_menu::get_active_menu() const
{
	return _menu;
}
