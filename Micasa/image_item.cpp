#include "image_item.hpp"

image_item::image_item()
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setCursor(QCursor(Qt::CursorShape::SizeAllCursor));
}

void image_item::center_item()
{
	auto _scale = scale();

	setPos((_scene_size.width() - _current_size.width() * _scale) / 2, (_scene_size.height() - _current_size.height() * _scale) / 2);
}

void image_item::load_resource(const wchar_t * _path)
{
	QFileInfo _info(QString::fromWCharArray(_path));
	
	// Is movie
	if (QMovie::supportedFormats().contains(_info.suffix().toUtf8())) {
		_movie = new QMovie(_info.absoluteFilePath());

		if (_movie->isValid()) {
			_movie->setCacheMode(QMovie::CacheAll);
			_movie->jumpToFrame(0);
			_current_size = _movie->currentPixmap().size();

			if (scale_view(_current_size)) {
				_movie->setScaledSize(_current_size);
			}

			center_item();

			QTimer::singleShot(_movie->nextFrameDelay(), [&]() {
				show_next_movie_frame();
			});

			return;
		}

		delete _movie;
	} // Try image
	else {
		_original_image = QPixmap(_info.absoluteFilePath());
		
		if (!_original_image.isNull()) {
			_current_size = _original_image.size();

			if (scale_view(_current_size)) {
				setPixmap(_original_image.scaled(_current_size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
			} else {
				setPixmap(_original_image);
			}

			center_item();

			return;
		}
	}

	_movie = nullptr;
}

void image_item::contextMenuEvent(QGraphicsSceneContextMenuEvent * _event)
{
}

void image_item::show_next_movie_frame()
{
	if (_movie) {
		setPixmap(_movie->currentPixmap());
		_movie->jumpToNextFrame();

		QTimer::singleShot(_movie->nextFrameDelay(), [this]() {
			show_next_movie_frame();
		});
	}
}

bool image_item::scale_view(QSize & _size)
{
	auto _rect = scene()->sceneRect();

	_scene_size.setWidth(_rect.width());
	_scene_size.setHeight(_rect.height());

	if (_size.width() < _scene_size.width() * 0.95 && _size.height() < _scene_size.height() * 0.9) {
		return false;
	}
	
	// Rescale
	auto _scale = std::min(_scene_size.width() * 0.95 / _size.width(), _scene_size.height() * 0.9 / _size.height());

	_size.setWidth(_size.width() * _scale);
	_size.setHeight(_size.height() * _scale);

	return true;
}
