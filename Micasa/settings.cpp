#include "settings.hpp"


std::unique_ptr<SQLite::Database> settings::_db;
std::unique_ptr<SQLite::Statement> settings::_get_sort_settings;
std::unique_ptr<SQLite::Statement> settings::_set_folder_view;

void settings::initialize()
{
	_db.reset(new SQLite::Database("Micasa.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE));
	_get_sort_settings.reset(new SQLite::Statement(*_db.get(), get_sort_setting_sql()));
	_set_folder_view.reset(new SQLite::Statement(*_db.get(), set_folder_view_sql()));

	_db->exec(create_table_sql());
}

void settings::finalize()
{
	_set_folder_view.reset();
	_get_sort_settings.reset();
	_db.reset();
}

void settings::set_default(folder_view _view)
{
	set_folder_view("", _view);
}

void settings::set_folder_view(const char * _path, folder_view _view)
{
	_set_folder_view->bindNoCopy(1, _path);
	_set_folder_view->bind(2, _view.sort_type);
	_set_folder_view->bind(3, _view.sort_order);

	_set_folder_view->exec();
}

settings::folder_view settings::get_folder_view(const char * _path)
{
	folder_view _view{};

	_get_sort_settings->bindNoCopy(1, _path);
	_get_sort_settings->bindNoCopy(2, _path);

	// Read settings from database
	if (_get_sort_settings->executeStep()) {
		_view.sort_type = _get_sort_settings->getColumn(0).getInt();
		_view.sort_order = _get_sort_settings->getColumn(1).getInt();
	}

	return _view;
}

const char * settings::create_table_sql()
{
	return R"(
create table if not exists	folder_views(
	path text not null unique,
	sort_type integer not null,
	sort_order integer not null
))";
}

const char * settings::get_sort_setting_sql()
{
	return R"(
select sort_type, sort_order from folder_views where path=?
	union all 
select * from (select sort_type, sort_order from folder_views where ? like (path || "%") order by length(path))
)";
}

const char * settings::set_folder_view_sql()
{
	return R"(
insert or replace into folder_views(path, sort_type, sort_order)
	values(?, ?, ?)
)";
}
