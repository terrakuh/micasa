#include "scene.hpp"


std::wregex scene::_filter(image_item::get_filter_rule(), std::regex_constants::icase);

scene::scene(QObject * _parent, const QSize & _size) : QGraphicsScene(0, 0, _size.width(), _size.height(), _parent), _scaler(200)
{
	_diashow_timer = 0;

	addItem(_image = new image_item());

	// Add close button
	auto _button = new pixmap_item(RESOURCE_CLOSE_BUTTON, std::bind(&scene::close_animation_and_quit, this));

	_button->setPos(_size.width() - _button->boundingRect().width(), 0);
	_button->setZValue(ZORDER_CLOSE_BUTTON);

	addItem(_button);

	printf("%p\n", _button->parentItem());

	// Add play button
	_button = new pixmap_item(RESOURCE_PLAY, [this]() {
		toggle_diashow();
	});

	_button->setPos((_size.width() - _button->boundingRect().width()) / 2, _size.height() * 0.95 + (_size.height() * 0.05 - _button->boundingRect().height()) / 2);
	_button->setZValue(ZORDER_PLAY_BUTTON);

	addItem(_button);

	// Add next button
	_button = new pixmap_item(RESOURCE_NEXT, [this]() {
		next_item(false);
	});

	_button->setPos((_size.width() - _button->boundingRect().width()) / 2 + 75, _size.height() * 0.95 + (_size.height() * 0.05 - _button->boundingRect().height()) / 2);
	_button->setZValue(ZORDER_PLAY_BUTTON);

	addItem(_button);

	// Add prev button
	_button = new pixmap_item(RESOURCE_PREV, [this]() {
		next_item(true);
	});

	_button->setPos((_size.width() - _button->boundingRect().width()) / 2 - 75, _size.height() * 0.95 + (_size.height() * 0.05 - _button->boundingRect().height()) / 2);
	_button->setZValue(ZORDER_PLAY_BUTTON);

	addItem(_button);

	set_background();
	_d = 0;
	_g = 0;
	// Timeline scaler
	_scaler.setCurveShape(QTimeLine::LinearCurve);
	_scaler.setUpdateInterval(20);
	connect(&_scaler, &QTimeLine::valueChanged, [this](double _x) {
		auto _y = image_scaling_function((_d - _g) * _x + _g);
		auto _y1 = image_scaling_function(_g);
		auto _old = _image->scale();
		_image->setScale(_y);
		_image->center_item();
		printf("%f => %f\n", _old, _y);
	});
	connect(&_scaler, &QTimeLine::finished, [this]() {
		_g = _d;
	});
}

scene::~scene()
{
	// Delete all items
	for (auto _item : items()) {
		delete _item;
	}
}

void scene::set_image_scale(double _factor)
{
	_image->setScale(_factor);
	_image->center_item();
}

void scene::show_animation()
{
	auto _animation = new QPropertyAnimation(this, "image_scale");

	_animation->setStartValue(0.0);
	_animation->setEndValue(1.0);
	_animation->setEasingCurve(QEasingCurve::OutCubic);
	_animation->setDuration(750);

	_animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void scene::close_animation_and_quit()
{
	auto _animation = new QPropertyAnimation(this, "image_scale");

	_animation->setStartValue(1.0);
	_animation->setEndValue(0.0);
	_animation->setEasingCurve(QEasingCurve::InCubic);
	_animation->setDuration(250);

	_animation->start(QAbstractAnimation::DeleteWhenStopped);

	connect(_animation, &QPropertyAnimation::finished, &QApplication::quit);
}

void scene::blacken_background(bool _blacken)
{
	if (_blacken) {
		setBackgroundBrush(QColor(0, 0, 0));
	} else {
		setBackgroundBrush(_background);
	}
}

void scene::set_background()
{
	auto _desktop = QApplication::desktop();
	auto _index = _desktop->screenNumber(static_cast<QWidget*>(parent()));

	// Fall back to primary screen
	if (_index == -1) {
		_index = _desktop->primaryScreen();
	}
	
	// Take screenshot
	_background = QApplication::screens()[_index]->grabWindow(0);

	// Draken background
	QPainter _painter(&_background);

	_painter.setBrush(QColor(0, 0, 0, 114));
	_painter.drawRect(_background.rect());

	setBackgroundBrush(_background);
}

void scene::toggle_diashow()
{
	_image->toggle_fullscreen();
	_image->center_item();

	// Stop timer
	if (_diashow_timer) {
		blacken_background(false);
		killTimer(_diashow_timer);

		_diashow_timer = 0;
	} // Start timer
	else {
		blacken_background(true);

		_diashow_timer = startTimer(static_cast<int>(_image->get_diashow_time().count()));
	}
}

bool scene::open(const wchar_t * _path)
{
	thread_pool::global_thread_pool()->queue(std::bind([this](const std::wstring & _path) {
		_folder_view.load_files(QFileInfo(QString::fromStdWString(_path)).absolutePath().toStdWString().c_str());
		_folder_view.select_item(_path.c_str());
	}, std::wstring(_path)));

	return _image->load_resource(_path);
}

bool scene::next_item(bool _prev)
{
	if (_folder_view.valid()) {
		auto _file = _folder_view.neighbor_item(!_prev, _filter);

		if (!_file.empty()) {
			_image->load_resource(_file.c_str());

			return true;
		}
	}

	return false;
}

double scene::get_image_scale()
{
	return _image->scale();
}

image_item * scene::get_image()
{
	return _image;
}

void scene::timerEvent(QTimerEvent * _event)
{
	if (_event->timerId() == _diashow_timer) {
		// Stop if there is no next item
		if (!next_item(false)) {
			toggle_diashow();
		}
	}
}

void scene::keyPressEvent(QKeyEvent * _event)
{
	switch (_event->key()) {
	case Qt::Key_Right:
		next_item(false);

		break;
	case Qt::Key_Left:
		next_item(true);

		break;
	default:
		QGraphicsScene::keyPressEvent(_event);

		break;
	}
}

void scene::keyReleaseEvent(QKeyEvent * _event)
{
	switch (_event->key()) {
	case Qt::Key_Space:
	{
		toggle_diashow();

		break;
	}
	default:
		QGraphicsScene::keyReleaseEvent(_event);

		break;
	}
}

void scene::wheelEvent(QGraphicsSceneWheelEvent * _event)
{

	/*if (_event->delta() > 0) {
		_scaler.setDirection(QTimeLine::Forward);
	} else {
		_scaler.setDirection(QTimeLine::Backward);
	}*/

	auto _steps = _event->delta() /120;

	_d += _steps;
	_d = (std::min)((std::max)(_d, -20), 20);
	
	_scaler.start();
}

double scene::image_scaling_function(double _x)
{
	return std::exp(0.18 * _x);
}
