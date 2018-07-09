#include "image_item.hpp"

image_item::image_item()
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setCursor(QCursor(Qt::CursorShape::SizeAllCursor));
}

void image_item::center_item()
{
	auto _scale = scale() * _normal_scale;

	setScale(_scale);

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

			set_size(_movie->currentPixmap().size());
			center_item();

			QTimer::singleShot(_movie->nextFrameDelay(), [&]() {
				show_next_movie_frame();
			});
			//_current_size = _movie->currentImage().size();
			//resize(_current_size);
			//_movie->start();
			//_ui.label->setMovie(_movie);

			//show();

			return;
		}

		delete _movie;
	} // Try image
	else {
		setPixmap(QPixmap(_info.absoluteFilePath()));

		if (!pixmap().isNull()) {
			set_size(pixmap().size());
			center_item();

			return;
		}
	}

	_movie = nullptr;
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

void image_item::set_size(const QSize & _size)
{
	auto _rect = scene()->sceneRect();

	_current_size = _size;
	_scene_size.setWidth(_rect.width());
	_scene_size.setHeight(_rect.height());
	
	if (_current_size.width() < _scene_size.width() * 0.95 && _current_size.height() < _scene_size.height() * 0.9) {
		_normal_scale = 1.0;
	} else {
		_normal_scale = std::min(_scene_size.width() * 0.95 / _current_size.width(), _scene_size.height() * 0.9 / _current_size.height());
	}
}
