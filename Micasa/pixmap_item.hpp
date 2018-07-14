#pragma once

#include <functional>
#include <QtWidgets\QGraphicsItem>
#include <QtGui\QPixmap>
#include <QtGui\QCursor>


class pixmap_item : public QGraphicsPixmapItem
{
public:
	pixmap_item(const char * _resource, std::function<void()> && _click_action);

protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * _event) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * _event) override;

private:
	std::function<void()> _click_action;
};