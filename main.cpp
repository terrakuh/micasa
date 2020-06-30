#include "src/config/main.hpp"

#include "src/image/item.hpp"
#include "src/image/manager.hpp"
#include "src/main_window.hpp"

#include <QApplication>
#include <QGraphicsOpacityEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QMainWindow>
#include <iostream>

int main(int argc, char** argv)
{
	QApplication app{ argc, argv };

	micasa::config::load("settings.json");

	/*QMainWindow window;

	QHBoxLayout layout;

	QWidget w;
	auto ge = new QGraphicsOpacityEffect{&w};
	ge->setOpacity(0.5);
	w.setGraphicsEffect(ge);
	w.setStyleSheet("QWidget{background: #ff0000}");
	w.setAutoFillBackground(true);
	layout.addWidget(&w);

	QWidget q;
	q.setStyleSheet("QWidget{background: #0000ff}");
	layout.addWidget(&q);

	QWidget l;
	l.setLayout(&layout);
	window.setCentralWidget(&l);

	window.setWindowFlags(Qt::FramelessWindowHint);
	window.setAttribute(Qt::WA_TranslucentBackground);
	window.show();*/

	micasa::image::manager manager{ "sample_images/test.png" };
	micasa::main_window window;

	/*const auto view  = new QGraphicsView{ &window };
	const auto scene = new QGraphicsScene{ view };
	const auto item  = new QGraphicsPixmapItem{ QPixmap{ manager.current() } };

	std::cout << item->boundingRect().width() << "x" << item->boundingRect().height() << std::endl;

	item->setFlag(QGraphicsItem::ItemIsMovable);
	item->setCursor(QCursor{ Qt::CursorShape::SizeAllCursor });
	scene->addItem(item);
	view->setScene(scene);
	// scene->setSceneRect(QRect{ QPoint{ 0, 0 }, QSize{1920, 1080} });
	// view->setMinimumSize(QSize{1920, 1080});
	// view->setMinimumSize(720, 480);
	// view->setSceneRect(scene->sceneRect());
	view->setFrameStyle(QFrame::NoFrame);
	view->setStyleSheet("background-color: transparent;");
	view->show();
	scene->setSceneRect(0, 0, view->width(), view->height());

	std::cout << view->width() << "x" << view->height() << std::endl;
	
	window.foo = [view, item, scene](QSize s) {
		view->resize(s);
		scene->setSceneRect(scene->itemsBoundingRect());
		//scene->setSceneRect(item->sceneBoundingRect());
	};*/
	//window.showFullScreen();

	return app.exec();
}
