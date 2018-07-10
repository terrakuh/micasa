#include "pixmap_item.hpp"

pixmap_item::pixmap_item(const char * _resource, std::function<void()> && _click_action) : QGraphicsPixmapItem(QPixmap(_resource)), _click_action(std::move(_click_action))
{
	setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
	setCursor(Qt::CursorShape::ArrowCursor);
}

void pixmap_item::mousePressEvent(QGraphicsSceneMouseEvent * _event)
{
}

void pixmap_item::mouseReleaseEvent(QGraphicsSceneMouseEvent * _event)
{
	_click_action();
}
