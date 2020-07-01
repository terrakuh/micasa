#ifndef MICASA_IMAGE_SCENE_HPP_
#define MICASA_IMAGE_SCENE_HPP_

#include "scaler.hpp"

#include <QGraphicsScene>
#include <QVariantAnimation>

namespace micasa {
namespace image {

class scene : public QGraphicsScene
{
public:
	scene(QObject* parent);

	QVariantAnimation* make_finish_animation();

protected:
	void wheelEvent(QGraphicsSceneWheelEvent* event) override;

private:
	item _item;
	scaler _scaler;
};

} // namespace image
} // namespace micasa

#endif
