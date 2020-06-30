#include "item.hpp"

#include "manager.hpp"

#include <QCursor>

using namespace micasa::image;

item::item() : QGraphicsPixmapItem{ QPixmap(manager::current()) }
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setCursor(QCursor{ Qt::CursorShape::SizeAllCursor });
}
