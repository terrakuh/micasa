#pragma once

#include <atlbase.h>
#include <Windows.h>
#include <ShObjIdl.h>
#include <ShlObj.h>
#include <string>
#include <cstring>
#include <vector>
#include <regex>
#include <mutex>
#include <experimental\filesystem>


class folder_view
{
public:
	folder_view();
	void select_item(const wchar_t * _path);
	bool load_files(const wchar_t * _path);
	bool valid() const;
	std::wstring neighbor_item(bool _next, const std::wregex & _filter);

	/*static void a(const wchar_t * _path)
	{
		// Get open explorer HWND in top-down Z-Order
		_explorer_hwnds.clear();

		EnumWindows(&folder_view::enumerate_callback, 0);

		// Check if one of the open windows was the source
		if (!_explorer_hwnds.empty()) {

		}
	}*/

private:
	std::mutex _mutex;
	CComPtr<IShellItemArray> _items;
	int _current;



	static void compare_existing(const std::vector<HWND> & _window_hwnds)
	{
		CComPtr<IShellWindows> _windows;

		if (SUCCEEDED(CoCreateInstance(CLSID_ShellWindows, nullptr, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&_windows)))) {
			VARIANT _count = { VT_I4 };

			if (SUCCEEDED(_windows->get_Count(&_count.lVal))) {
				for (auto _hwnd : _window_hwnds) {
					while (_count.lVal--) {
						CComPtr<IDispatch> _dispatch;

						if (_windows->Item(_count, &_dispatch) == S_OK) {
							CComPtr<IWebBrowser2> _browser;

							if (SUCCEEDED(_dispatch->QueryInterface(IID_PPV_ARGS(&_browser)))) {
								SHANDLE_PTR _other;

								// Match
								if (SUCCEEDED(_browser->get_HWND(&_other)) && reinterpret_cast<HWND>(_other) == _hwnd) {

								}
							}
						}
					}
				}
			}
		}
	}
	static BOOL CALLBACK enumerate_callback(HWND _hwnd, LPARAM _lparam);
};