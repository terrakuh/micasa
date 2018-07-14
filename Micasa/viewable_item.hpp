#pragma once


class viewable_item
{
public:
	virtual void center_item() = 0;
	virtual void load_resource(const wchar_t * _path) = 0;
};