#pragma once

#include <cmath>
#include <QtWidgets\QWidget>
#include <QtCore\QTimeLine>

#include "image_item.hpp"


class image_scaler
{
public:
	image_scaler(QWidget * _widget, image_item ** _image);

	void add_steps(int _steps);
private:
	int _destination_level;
	QTimeLine _scaler;

	static double scaling_function(double _x);
};