#pragma once

#include <QtWidgets\QApplication>
#include <QtWidgets\QDesktopWidget>
#include <QtWidgets\QGraphicsItem>
#include <QtGui\QCursor>
#include <QtGui\QScreen>
#include <QtGui\QPixmap>
#include <QtGui\QMovie>
#include <QtCore\QFileInfo>



class image_item : public QGraphicsPixmapItem
{
public:
	image_item()
	{
		setFlag(QGraphicsItem::ItemIsMovable);
		setCursor(QCursor(Qt::CursorShape::SizeAllCursor));
	}
	void center_item()
	{
		setPos((1920 - pixmap().width()) / 2, (1080 - pixmap().height()) / 2);
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
	}

protected:
	/*virtual void resizeEvent(QResizeEvent *event) override
	{
		auto _pos = (parentWidget()->size() - size()) / 2;
		move(_pos.width(), _pos.height());
		event->accept();
	}*/

private:
};