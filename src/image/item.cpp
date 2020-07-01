#include "item.hpp"

#include "manager.hpp"

#include <QCursor>

using namespace micasa::image;

item::item() : _original{ manager::current() }
{
	setPixmap(_original);
	setFlag(QGraphicsItem::ItemIsMovable);
	setCursor(QCursor{ Qt::CursorShape::SizeAllCursor });
}

void item::zoom(double percentage, Qt::TransformationMode mode)
{
	setPixmap(_original.scaled(_original.size() * percentage, Qt::AspectRatioMode::KeepAspectRatio, mode));
}
