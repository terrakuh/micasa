#ifndef MICASA_IMAGE_VIEW_HPP_
#define MICASA_IMAGE_VIEW_HPP_

#include "scene.hpp"

#include <QGraphicsView>
#include <QResizeEvent>

namespace micasa {
namespace image {

class view : public QGraphicsView
{
public:
	view(QWidget* parent);

	void play_finish_and_exit();

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	class scene _scene;
};

} // namespace image
} // namespace micasa

#endif
