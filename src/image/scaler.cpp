#include "scaler.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

using namespace micasa::image;

inline double scaling_function(int& steps)
{
	constexpr auto scale = 600;
	steps                = std::min(std::max(steps, 60 - scale), 4 * scale);

	return static_cast<double>(steps + scale) / scale;
}

scaler::scaler(item& item)
{
	_scaler.setDuration(200);
	_scaler.setUpdateInterval(20);
	_scaler.setCurveShape(QTimeLine::CurveShape::LinearCurve);

	QObject::connect(&_scaler, &QTimeLine::valueChanged, [&](double x) {
		item.zoom((_to - _from) * x + _from, Qt::TransformationMode::FastTransformation);
	});
	QObject::connect(&_scaler, &QTimeLine::finished, [&] {
		printf("scale %f, to %f\n", item.scale(), _to);
		_from = _to;

		item.zoom(_to, Qt::TransformationMode::SmoothTransformation);
	});
}

void scaler::add_steps(int count)
{
	const auto old = _to;
	_steps += count;
	_to = scaling_function(_steps);

	if (std::abs(_to - old) > std::numeric_limits<double>::epsilon() &&
	    _scaler.state() != QTimeLine::State::Running) {
		_scaler.start();
	}
}
