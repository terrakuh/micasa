#include "image_item.hpp"

image_item::image_item()
{
	setFlag(QGraphicsItem::ItemIsMovable);
	setCursor(QCursor(Qt::CursorShape::SizeAllCursor));
}

void image_item::center_item()
{
	setPos((1920 - pixmap().width()) / 2, (1080 - pixmap().height()) / 2);
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
