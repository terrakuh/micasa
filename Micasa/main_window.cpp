#include "main_window.hpp"

main_window::main_window()
{
	_ui.setupUi(this);
	_ui.retranslateUi(this);

	// Load icon
	setWindowIcon(QIcon(QPixmap(RESOURCE_ICON)));

	// Open fullscreen
	setWindowFlags(Qt::FramelessWindowHint);
	setWindowState(Qt::WindowFullScreen);

	// Create scene
	_ui.graphicsView->setScene(_scene = new scene(this, size()));

	//connect(_ui.pushButton, &QPushButton::clicked, &QApplication::quit);

	//settings::initialize();
}

main_window::~main_window()
{
	//settings::finalize();
}

scene * main_window::get_scene()
{
	return _scene;
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
	_scene->get_image()->get_context_menu().show_active_menu(_event->globalPos());
}
