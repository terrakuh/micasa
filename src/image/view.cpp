#include "view.hpp"

#include <QApplication>

using namespace micasa::image;

view::view(QWidget* parent)
    : QGraphicsView{ parent }, _scene{ nullptr }
{
	setScene(&_scene);
	setFrameStyle(QFrame::Shape::NoFrame);
	setStyleSheet("background-color: transparent;");
}

void view::play_finish_and_exit()
{
	const auto animation = _scene.make_finish_animation();

	connect(animation, &QVariantAnimation::finished, &QApplication::quit);
	animation->start(QVariantAnimation::DeleteWhenStopped);
}

void view::resizeEvent(QResizeEvent* event)
{
	_scene.setSceneRect(QRectF{ QPointF{ 0, 0 }, size() });
	//_item->setPos(_scene->sceneRect().center() - _item->boundingRect().center());
}
