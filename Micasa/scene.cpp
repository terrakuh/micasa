#include "scene.hpp"

scene::scene(const QSize & _size) : QGraphicsScene(0, 0, _size.width(), _size.height())
{
	addItem(_image = new image_item());
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
	_animation->setDuration(600);

	_animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void scene::close_animation_and_quit()
{
	auto _animation = new QPropertyAnimation(this, "image_scale");

	_animation->setStartValue(1.0);
	_animation->setEndValue(0.0);
	_animation->setEasingCurve(QEasingCurve::InCubic);
	_animation->setDuration(200);

	_animation->start(QAbstractAnimation::DeleteWhenStopped);

	connect(_animation, &QPropertyAnimation::finished, &QApplication::quit);
}

double scene::get_image_scale()
{
	return _image->scale();
}

image_item * scene::get_image()
{
	return _image;
}
