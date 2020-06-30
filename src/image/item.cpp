#include "item.hpp"

#include <QCursor>

using namespace micasa::image;

item::item() : QGraphicsPixmapItem{ QPixmap("sample_images/test.png") }
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setCursor(QCursor{ Qt::CursorShape::SizeAllCursor });
}
