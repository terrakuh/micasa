#include "scene.hpp"

#include <QGraphicsSceneWheelEvent>

using namespace micasa::image;

scene::scene(QObject* parent) : QGraphicsScene{ parent }, _scaler{ _item }
{
	addItem(&_item);
}

QVariantAnimation* scene::make_finish_animation()
{
	const auto animation = new QVariantAnimation{ this };

	connect(animation, &QVariantAnimation::valueChanged, [this](const QVariant& value) {
		_item.setPos(_item.pos() +
		             QPointF{ _item.boundingRect().width() * _item.scale() / 2,
		                      _item.boundingRect().height() * _item.scale() / 2 } -
		             QPointF{ _item.boundingRect().width() * value.toDouble() / 2,
		                      _item.boundingRect().height() * value.toDouble() / 2 });
		_item.setScale(value.toDouble());
	});

	animation->setStartValue(1.0);
	animation->setEndValue(0.0);
	animation->setEasingCurve(QEasingCurve::OutCubic);
	animation->setDuration(350);

	return animation;
}

void scene::wheelEvent(QGraphicsSceneWheelEvent* event)
{
	_scaler.add_steps(event->delta());
	event->accept();
}
