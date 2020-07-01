#ifndef MICASA_IMAGE_SCALER_HPP_
#define MICASA_IMAGE_SCALER_HPP_

#include "item.hpp"

#include <QTimeLine>

namespace micasa {
namespace image {

class scaler
{
public:
	scaler(item& item);

	void add_steps(int count);

private:
	QTimeLine _scaler;
	int _steps   = 0;
	double _from = 1.0;
	double _to   = 1.0;
};

} // namespace image
} // namespace micasa

#endif
