#include "context_menu.hpp"

context_menu::context_menu()
{
	// Image context menu
	_image.addAction("Open with...");
	_image.addSeparator();
	_image.addAction("Copy");
	_image.addAction("Delete");
	_image.addAction("Hide");
	_image.addSeparator();
	_image.addAction("Cut");
	_image.addAction("Resize");
	_image.addAction("Rotate clockwise");
	_image.addAction("Rotate counterclockwise");
	_image.addSeparator();
	_image.addAction("Quit");

	// Movie context menu
	_movie.addAction("Open with...");
	_movie.addSeparator();
	_movie.addAction("Play");
	_movie.addAction("Pause");
	_movie.addAction("Rewind");
	_movie.addAction("Reverse");
	_movie.addSeparator();
	_movie.addAction("Copy");
	_movie.addAction("Delete");
	_movie.addAction("Hide");
	_movie.addSeparator();
	_movie.addAction("Cut");
	_movie.addAction("Resize");
	_movie.addAction("Rotate clockwise");
	_movie.addAction("Rotate counterclockwise");
	_movie.addSeparator();
	_movie.addAction("Quit");
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
