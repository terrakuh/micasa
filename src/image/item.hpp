#ifndef MICASA_IMAGE_ITEM_HPP_
#define MICASA_IMAGE_ITEM_HPP_

#include <QGraphicsPixmapItem>

namespace micasa {
namespace image {

class item : public QGraphicsPixmapItem
{
public:
	item();

	void zoom(double percentage, Qt::TransformationMode mode);

private:
	QPixmap _original;
};

} // namespace image
} // namespace micasa

#endif
