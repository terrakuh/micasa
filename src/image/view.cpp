#include "view.hpp"

#include "item.hpp"

#include <QApplication>
#include <QVariantAnimation>

using namespace micasa::image;

view::view(QWidget* parent) : QGraphicsView{ parent }
{
	_scene = new QGraphicsScene{ this };
	_item  = new item{};

	_scene->addItem(_item);
	setScene(_scene);
	setFrameStyle(QFrame::Shape::NoFrame);
	setStyleSheet("background-color: transparent;");
}

void view::play_finish_and_exit()
{
	const auto animation = new QVariantAnimation{ this };

	connect(animation, &QVariantAnimation::valueChanged, [this](const QVariant& value) {
		_item->setPos(_item->pos() +
		              QPointF{ _item->boundingRect().width() * _item->scale() / 2,
		                       _item->boundingRect().height() * _item->scale() / 2 } -
		              QPointF{ _item->boundingRect().width() * value.toDouble() / 2,
		                       _item->boundingRect().height() * value.toDouble() / 2 });
		_item->setScale(value.toDouble());
	});
	connect(animation, &QVariantAnimation::finished, &QApplication::quit);

	animation->setStartValue(1.0);
	animation->setEndValue(0.0);
	animation->setEasingCurve(QEasingCurve::OutCubic);
	animation->setDuration(350);
	animation->start(QVariantAnimation::DeleteWhenStopped);
}

void view::resizeEvent(QResizeEvent* event)
{
	_scene->setSceneRect(QRectF{ QPointF{ 0, 0 }, size() });
	_item->setPos(_scene->sceneRect().center() - _item->boundingRect().center());
}
