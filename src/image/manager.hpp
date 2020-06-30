#ifndef MICASA_IMAGE_MANAGER_HPP_
#define MICASA_IMAGE_MANAGER_HPP_

#include <QString>

namespace micasa {
namespace image {

class manager
{
public:
	manager(QString image);
	QString current() const;

private:
	QString _current;
};

} // namespace image
} // namespace micasa

#endif
