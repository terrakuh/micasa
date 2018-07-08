#pragma once

#include <memory>
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

	static void initialize();
	static void finalize();
	static void set_default(folder_view _view);
	static void set_folder_view(const char * _path, folder_view _view);
	static folder_view get_folder_view(const char * _path);

private:
	static std::unique_ptr<SQLite::Database> _db;
	static std::unique_ptr<SQLite::Statement> _get_sort_settings;
	static std::unique_ptr<SQLite::Statement> _set_folder_view;

	static const char * create_table_sql();
	static const char * get_sort_setting_sql();
	static const char * set_folder_view_sql();
};