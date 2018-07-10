#include "main_window.hpp"

main_window::main_window()
{
	_ui.setupUi(this);
	_ui.retranslateUi(this);

	_context_menu.addAction("Play", []() {

	});
	_context_menu.addAction("Pause", []() {

	});
	_context_menu.addAction("Reverse", []() {
		puts("reverse");
	});

	// Open fullscreen
	setWindowFlags(Qt::FramelessWindowHint);
	setWindowState(Qt::WindowFullScreen);

	// Create scene
	_ui.graphicsView->setScene(_scene = new scene(size()));

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
	auto _background = _screen->grabWindow(0);

	// Draken background
	QPainter _painter(&_background);

	_painter.setBrush(QColor(0, 0, 0, 114));
	_painter.drawRect(_background.rect());

	_scene->setBackgroundBrush(_background);
}

image_item * main_window::get_image()
{
	return _scene->get_image();
}

void main_window::keyPressEvent(QKeyEvent * _event)
{
	if (_event->key() == Qt::Key_Escape) {
		_scene->close_animation_and_quit();
		_event->accept();
	}
}

void main_window::showEvent(QShowEvent * _event)
{
	_scene->show_animation();

	QMainWindow::showEvent(_event);
}

void main_window::contextMenuEvent(QContextMenuEvent * _event)
{
	_context_menu.exec(_event->globalPos());
	_event->accept();
}
