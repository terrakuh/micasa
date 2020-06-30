#include "manager.hpp"

using namespace micasa::image;

inline QString current;

void manager::init(QString path)
{
	::current = std::move(path);
}

QString manager::current()
{
	return ::current;
}
