#include "main_window.hpp"

main_window::main_window()
{
	_ui.setupUi(this);
	_ui.retranslateUi(this);

	// Open fullscreen
	setWindowFlags(Qt::FramelessWindowHint);
	setWindowState(Qt::WindowFullScreen);

	// Create scene
	auto _size = size();

	_ui.graphicsView->setScene(new QGraphicsScene(0, 0, _size.width(), _size.height()));
	_ui.graphicsView->scene()->addItem(_image = new image_item());
	// Setup background
	set_background();

	

	//connect(_ui.pushButton, &QPushButton::clicked, &QApplication::quit);

	//settings::initialize();
}

main_window::~main_window()
{
	//settings::finalize();
}

void main_window::set_background()
{
	auto _screen = QApplication::primaryScreen();

	_ui.graphicsView->scene()->setBackgroundBrush(QBrush(_screen->grabWindow(0)));
}

image_item * main_window::get_image()
{
	return _image;
}

void main_window::keyPressEvent(QKeyEvent * _event)
{
	if (_event->key() == Qt::Key_Escape) {
		QApplication::quit();
		_event->accept();
	}
}
