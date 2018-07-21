#include "image_item.hpp"
#include "scene.hpp"


image_item::image_item() : _context_menu(this)
{
	_fullscreen = false;
	_play = false;
	_reversed = false;

	setFlag(QGraphicsItem::ItemIsMovable);
	setCursor(QCursor(Qt::CursorShape::SizeAllCursor));
}

void image_item::open_with()
{
}

void image_item::play()
{
	if (_movie) {
		_play = true;

		QTimer::singleShot(0, [&]() {
			show_next_movie_frame(_movie);
		});
	}
}

void image_item::pause()
{
	if (_movie) {
		_play = false;
	}
}

void image_item::rewind()
{
	if (_movie) {
		_movie->jumpToFrame(0);
	}
}

void image_item::reverse()
{
	_reversed = !_reversed;
}

void image_item::copy()
{
}

void image_item::delete_from_disk()
{
}

void image_item::hide()
{
}

void image_item::cut()
{
}

void image_item::resize()
{
}

void image_item::rotate_clockwise()
{
}

void image_item::rotate_counterclockwise()
{
}

void image_item::quit()
{
	static_cast<::scene*>(scene())->close_animation_and_quit();
}

void image_item::center_item()
{
	auto _scale = scale();

	setPos((_scene_size.width() - _current_size.width() * _scale) / 2, (_scene_size.height() - _current_size.height() * _scale) / 2);
}

bool image_item::load_resource(const wchar_t * _path)
{
	QFileInfo _info(QString::fromWCharArray(_path));
	auto _recurred = false;

	_movie = nullptr;

	// Is movie
	if (QMovie::supportedFormats().contains(_info.suffix().toUtf8())) {
		_movie = new QMovie(_info.absoluteFilePath());

		if (_movie->isValid()) {
			_movie->setCacheMode(QMovie::CacheAll);
			_movie->jumpToFrame(0);
			_current_size = _movie->currentPixmap().size();
			_context_menu.set_active_menu(context_menu::ACTIVE_MENU::MOVIE);
			_play = true;
			_reversed = false;

			scale_view(_current_size);

			QTimer::singleShot(0, [&]() {
				center_item();
				show_next_movie_frame(_movie);
			});

			return true;
		}

		delete _movie;
		_movie = nullptr;
	} // Try image
	else {
		_original_image = QPixmap(_info.absoluteFilePath());

	gt_image_entry:;

		if (!_original_image.isNull()) {
			_current_size = _original_image.size();
			_context_menu.set_active_menu(context_menu::ACTIVE_MENU::IMAGE);

			if (scale_view(_current_size)) {
				setPixmap(_original_image.scaled(_current_size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
			} else {
				setPixmap(_original_image);
			}

			center_item();

			return true;
		}
	}

	// Load image failed
	if (!_recurred) {
		_original_image = QPixmap(RESOURCE_INVALID_IMAGE);
		_recurred = true;

		goto gt_image_entry;
	}

	return false;
}

context_menu & image_item::get_context_menu()
{
	return _context_menu;
}

const wchar_t * image_item::get_filter_rule()
{
	return LR"(.+?\.(?:jpeg|jpg|png|bmp|tiff|gif|webp)$)";
}

void image_item::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * _event)
{
	_fullscreen = !_fullscreen;

	// Set image size
	if (_movie) {
		_current_size = _movie->currentPixmap().size();
		
		if (scale_view(_current_size)) {
			//_movie->setScaledSize(_current_size);
		}
	} else {
		_current_size = _original_image.size();
		
		if (scale_view(_current_size)) {
			setPixmap(_original_image.scaled(_current_size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		} else {
			setPixmap(_original_image);
		}
	}

	static_cast<::scene*>(scene())->blacken_background(_fullscreen);

	if (_fullscreen) {
		center_item();
	}
}

void image_item::show_next_movie_frame(const void * _address)
{
	if (_movie == _address && _play) {
		setPixmap(_movie->currentPixmap().scaled(_current_size));

		// Jump to next frame
		if (_reversed) {
			auto _frame = _movie->currentFrameNumber();

			if (_frame == 0) {
				_frame = _movie->frameCount();
			}

			_movie->jumpToFrame(_frame - 1);
		} else {
			_movie->jumpToNextFrame();
		}

		// Schedule show
		QTimer::singleShot(_movie->nextFrameDelay(), [=]() {
			show_next_movie_frame(_address);
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
	double _scale;

	if (_fullscreen) {
		_scale = (std::min)(static_cast<double>(_scene_size.width()) / _size.width(), static_cast<double>(_scene_size.height()) / _size.height());
	} else {
		_scale = (std::min)(_scene_size.width() * 0.95 / _size.width(), _scene_size.height() * 0.9 / _size.height());
	}

	_size.setWidth(_size.width() * _scale);
	_size.setHeight(_size.height() * _scale);

	return true;
}


