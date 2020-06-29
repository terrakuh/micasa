#ifndef MICASA_CONFIG_MAIN_HPP_
#define MICASA_CONFIG_MAIN_HPP_

#include "theme.hpp"

#include <QString>
#include <QJsonObject>

namespace micasa {
namespace config {

struct main
{
	struct theme theme;

	main(const QJsonObject& obj);
};

void load(const QString& file);
main& get() noexcept;

} // namespace config
} // namespace micasa

#endif
