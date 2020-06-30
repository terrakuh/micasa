#ifndef MICASA_IMAGE_MANAGER_HPP_
#define MICASA_IMAGE_MANAGER_HPP_

#include <QString>

namespace micasa {
namespace image {

class manager
{
public:
	static void init(QString path);
	static QString current();
};

} // namespace image
} // namespace micasa

#endif
