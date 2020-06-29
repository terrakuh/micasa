#ifndef MICASA_CONFIG_THEME_HPP_
#define MICASA_CONFIG_THEME_HPP_

#include <QJsonObject>

namespace micasa {
namespace config {

struct theme
{
	double opacity     = 0.6;
	QString background = "#000000";

	theme(const QJsonObject& obj)
	{
		opacity    = obj.value("opacity").toDouble(opacity);
		background = obj.value("background").toString(background);
	}
};

} // namespace config
} // namespace micasa

#endif
