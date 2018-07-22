#include "context_menu.hpp"

context_menu::context_menu(editable_item * _editable)
{
	using namespace std::chrono_literals;

	// Diashow menu
	_diashow.setTitle("Diashow");

	_diashow.addAction("1 second", [=]() {
		auto _actions = _diashow.actions();

		// Uncheck all others
		for (auto _action : _actions) {
			_action->setChecked(false);
		}

		_actions[0]->setChecked(true);
		_editable->set_diashow_time(1s);
	})->setCheckable(true);
	auto _action = _diashow.addAction("3 seconds", [=]() {
		auto _actions = _diashow.actions();

		// Uncheck all others
		for (auto _action : _actions) {
			_action->setChecked(false);
		}

		_actions[1]->setChecked(true);
		_editable->set_diashow_time(3s);
	});
	_diashow.addAction("4 seconds", [=]() {
		auto _actions = _diashow.actions();

		// Uncheck all others
		for (auto _action : _actions) {
			_action->setChecked(false);
		}

		_actions[2]->setChecked(true);
		_editable->set_diashow_time(4s);
	})->setCheckable(true);
	_diashow.addAction("5 seconds", [=]() {
		auto _actions = _diashow.actions();

		// Uncheck all others
		for (auto _action : _actions) {
			_action->setChecked(false);
		}

		_actions[3]->setChecked(true);
		_editable->set_diashow_time(5s);
	})->setCheckable(true);
	_diashow.addAction("8 seconds", [=]() {
		auto _actions = _diashow.actions();

		// Uncheck all others
		for (auto _action : _actions) {
			_action->setChecked(false);
		}

		_actions[4]->setChecked(true);
		_editable->set_diashow_time(8s);
	})->setCheckable(true);

	// Set default to 3 seconds
	_action->setCheckable(true);
	_action->activate(QAction::Trigger);


	// Image context menu
	_image.addAction("Open with...", std::bind(&editable_item::open_with, _editable));
	_image.addMenu(&_diashow);
	_image.addSeparator();
	_image.addAction("Copy", std::bind(&editable_item::copy, _editable));
	_image.addAction("Delete", std::bind(&editable_item::delete_from_disk, _editable));
	_image.addAction("Hide", std::bind(&editable_item::hide, _editable));
	_image.addSeparator();
	_image.addAction("Cut", std::bind(&editable_item::cut, _editable))->parent();
	_image.addAction("Resize", std::bind(&editable_item::resize, _editable));
	_image.addAction("Rotate clockwise", std::bind(&editable_item::rotate_clockwise, _editable));
	_image.addAction("Rotate counterclockwise", std::bind(&editable_item::rotate_counterclockwise, _editable));
	_image.addSeparator();
	_image.addAction("Quit", std::bind(&editable_item::quit, _editable));

	// Movie context menu
	_movie.addAction("Open with...", std::bind(&editable_item::open_with, _editable));
	_movie.addMenu(&_diashow);
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
