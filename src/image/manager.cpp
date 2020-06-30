#include "manager.hpp"

using namespace micasa::image;

manager::manager(QString image) : _current{std::move(image)}
{}

QString manager::current() const
{
	return _current;
}
