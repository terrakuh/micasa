#ifndef MICASA_MAIN_WINDOW_HPP_
#define MICASA_MAIN_WINDOW_HPP_

#include <QMainWindow>

namespace micasa
{

class main_window : public QMainWindow
{
public:
	main_window();

protected:
	void keyPressEvent(QKeyEvent* event) override;

private:
};

}

#endif
