#include "main.hpp"

#include <QFile>
#include <QJsonDocument>
#include <memory>
#include <stdexcept>

using namespace micasa::config;

inline std::unique_ptr<main> config;

main::main(const QJsonObject& obj) : theme{ obj.value("theme").toObject() }
{}

void micasa::config::load(const QString& file)
{
	QFile f{ file };

	if (!f.open(QFile::ReadOnly | QFile::Text)) {
		throw std::runtime_error{ "file cannot be opened" };
	}

	const auto doc = QJsonDocument::fromJson(f.readAll());

	f.close();

	::config.reset(new main{ doc.object() });
}

main& micasa::config::get() noexcept
{
	return *::config;
}
