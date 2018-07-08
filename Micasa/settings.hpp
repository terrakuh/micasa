#pragma once

#include <SQLiteCpp\Database.h>
#include <SQLiteCpp\Statement.h>


class settings
{
public:
	struct folder_view
	{
		int sort_type;
		int sort_order;
	};

	settings();

	void set_default(folder_view _view);
	void set_folder_view(const char * _path, folder_view _view);
	folder_view get_folder_view(const char * _path);

private:
	SQLite::Database _db;
	SQLite::Statement _get_sort_settings;
	SQLite::Statement _set_folder_view;

	static const char * create_table_sql();
	static const char * get_sort_setting_sql();
	static const char * set_folder_view_sql();
};