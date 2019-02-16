#include "image_scaler.hpp"

image_scaler::image_scaler(QWidget * _widget, image_item ** _image)
{
	_destination_level = 0;

	_scaler.setDuration(200);
	_scaler.setUpdateInterval(20);
	_scaler.setCurveShape(QTimeLine::LinearCurve);

	QObject::connect(&_scaler, &QTimeLine::valueChanged, [=](double _x) {
		auto _y = scaling_function((_destination_level - (*_image)->_scale_level) * _x + (*_image)->_scale_level);

		(*_image)->set_scale(_y, _widget->mapFromGlobal(QCursor::pos()));
	});
	QObject::connect(&_scaler, &QTimeLine::stateChanged, [=](QTimeLine::State _state) {
		if (_state == QTimeLine::NotRunning) {
			(*_image)->_scale_level = _destination_level;
			_destination_level = 0;
		} else if (_state == QTimeLine::Running) {
			_destination_level += (*_image)->_scale_level;
		}
	});
}

void image_scaler::add_steps(int _steps)
{
	_destination_level += _steps;
	_destination_level = (std::min)((std::max)(_destination_level, -20), 20);

	if (_scaler.state() != QTimeLine::Running) {
		_scaler.start();
	}
}

double image_scaler::scaling_function(double _x)
{
	return std::exp(0.18 * _x);
}
