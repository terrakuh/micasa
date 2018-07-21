#include "scene.hpp"


std::wregex scene::_filter(image_item::get_filter_rule(), std::regex_constants::icase);

scene::scene(const QSize & _size) : QGraphicsScene(0, 0, _size.width(), _size.height())
{
	addItem(_image = new image_item());

	auto _close = new pixmap_item(RESOURCE_CLOSE_BUTTON, std::bind(&scene::close_animation_and_quit, this));

	_close->setPos(_size.width() - _close->boundingRect().width(), 0);
	_close->setZValue(ZORDER_CLOSE_BUTTON);

	addItem(_close);

	set_background();
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
	auto _screen = QApplication::primaryScreen();
	
	_background = _screen->grabWindow(0);

	// Draken background
	QPainter _painter(&_background);

	_painter.setBrush(QColor(0, 0, 0, 114));
	_painter.drawRect(_background.rect());

	setBackgroundBrush(_background);
}

bool scene::open(const wchar_t * _path)
{
	thread_pool::global_thread_pool()->queue(std::bind([this](const std::wstring & _path) {
		_folder_view.load_files(QFileInfo(QString::fromStdWString(_path)).absolutePath().toStdWString().c_str());
		_folder_view.select_item(_path.c_str());
	}, std::wstring(_path)));

	return _image->load_resource(_path);
}

double scene::get_image_scale()
{
	return _image->scale();
}

image_item * scene::get_image()
{
	return _image;
}

void scene::keyPressEvent(QKeyEvent * _event)
{
	std::wstring _file;

	switch (_event->key()) {
	case Qt::Key_Right:
		_file = _folder_view.neighbor_item(true, _filter);
		
		break;
	case Qt::Key_Left:
		_file = _folder_view.neighbor_item(false, _filter);

		break;
	default:
		QGraphicsScene::keyPressEvent(_event);

		return;
	}

	if (!_file.empty()) {
		_image->load_resource(_file.c_str());
	}
}
