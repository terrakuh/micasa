#pragma once

#include <QtWidgets\QDialog>
#include <QtGui\QPixmap>
#include <QtGui\QMovie>
#include <QtCore\QFileInfo>
#include <QtCore\QPropertyAnimation>

#include "image_window_ui.hpp"


class image_window : public QDialog
{
public:
	image_window(QWidget * _parent) : QDialog(_parent, Qt::WindowType::Dialog | Qt::FramelessWindowHint)
	{
		_ui.setupUi(this);
		_ui.retranslateUi(this);
	}
	void load_resource(const wchar_t * _path)
	{
		QFileInfo _info(QString::fromWCharArray(_path));

		// Is movie
		if (QMovie::supportedFormats().contains(_info.suffix().toUtf8())) {
			auto _movie = new QMovie(_info.absoluteFilePath());

			if (_movie->isValid()) {
				_movie->setCacheMode(QMovie::CacheAll);
				_movie->jumpToFrame(0);
				_current_size = _movie->currentImage().size();
				resize(_current_size);
				//_movie->start();
				_ui.label->setMovie(_movie);

				show();

				return;
			}

			delete _movie;
		} // Try image
		else {
			_ui.label->setPixmap(QPixmap(_info.absoluteFilePath()));

			if (!_ui.label->pixmap()->isNull()) {
				_current_size = _ui.label->pixmap()->size();
				resize(_current_size);

				show();

				return;
			}
		}

		hide();
	}
	void showing_animation()
	{
		auto _animation = new QPropertyAnimation(this, "size");

		_animation->setStartValue(QSize(0, 0));
		_animation->setEndValue(_current_size);
		_animation->setEasingCurve(QEasingCurve::InOutQuad);
		_animation->setLoopCount(5000);
		_animation->setDuration(500);

		_animation->start(QAbstractAnimation::DeleteWhenStopped);
	}

protected:
	virtual void resizeEvent(QResizeEvent *event) override
	{
		auto _pos = (parentWidget()->size() - size()) / 2;
		move(_pos.width(), _pos.height());
		event->accept();
	}

private:
	Ui_Image _ui;
	QSize _current_size;
};