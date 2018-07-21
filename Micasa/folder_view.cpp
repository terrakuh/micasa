#include "folder_view.hpp"

folder_view::folder_view()
{
	_current = 0;
}

void folder_view::select_item(const wchar_t * _path)
{
	if (!valid()) {
		return;
	}

	std::lock_guard<std::mutex> _lck(_mutex);
	DWORD _max_items;
	std::experimental::filesystem::path _p = _path;

	if (SUCCEEDED(_items->GetCount(&_max_items))) {
		for (DWORD i = 0; i < _max_items; ++i) {
			CComPtr<IShellItem> _item;

			if (SUCCEEDED(_items->GetItemAt(i, &_item))) {
				LPWSTR _name;

				if (SUCCEEDED(_item->GetDisplayName(SIGDN_FILESYSPATH, &_name))) {
					if (std::experimental::filesystem::equivalent(_name, _p)) {
						//if (!StrCmpW(_path, _name)) {
						_current = i;

						CoTaskMemFree(_name);

						break;
					}
					CoTaskMemFree(_name);
				}
			}
		}
	}
}

bool folder_view::load_files(const wchar_t * _path)
{
	CComPtr<IWebBrowser2> _browser;

	if (SUCCEEDED(CoCreateInstance(CLSID_ShellBrowserWindow, nullptr, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&_browser)))) {
		struct guard
		{
			CComPtr<IWebBrowser2> _browser;

			guard(CComPtr<IWebBrowser2> & _browser) : _browser(_browser)
			{
			}
			~guard()
			{
				_browser->Stop();
				_browser->Quit();
			}
		} _guard(_browser);

		CComPtr<IServiceProvider> _provider;
		CComVariant _empty;
		CComVariant _target;

		_target = _path;

		if (SUCCEEDED(_browser->Navigate2(&_target, &_empty, &_empty, &_empty, &_empty))) {
			if (SUCCEEDED(_browser->QueryInterface(IID_PPV_ARGS(&_provider)))) {
				CComPtr<IShellBrowser> _shell_browser;

				if (SUCCEEDED(_provider->QueryService(SID_STopLevelBrowser, &_shell_browser))) {
					CComPtr<IShellView> _shell_view;

					if (SUCCEEDED(_shell_browser->QueryActiveShellView(&_shell_view))) {
						CComPtr<IFolderView> _view;

						if (SUCCEEDED(_shell_view->QueryInterface(IID_PPV_ARGS(&_view)))) {
							std::lock_guard<std::mutex> _lck(_mutex);

							_items.Release();

							if (SUCCEEDED(_view->Items(SVGIO_ALLVIEW | SVGIO_FLAG_VIEWORDER, IID_PPV_ARGS(&_items)))) {
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}

bool folder_view::valid() const
{
	return _items;
}

std::wstring folder_view::neighbor_item(bool _next, const std::wregex & _filter)
{
	std::lock_guard<std::mutex> _lck(_mutex);

	while (valid()) {
		CComPtr<IShellItem> _item;
		LPWSTR _name;
		SFGAOF _out = 0;

		if (FAILED(_items->GetItemAt(_current + (_next ? 1 : -1), &_item))) {
			break;
		}

		_current += _next ? 1 : -1;

		_item->GetAttributes(SFGAO_FOLDER, &_out);

		if (!_out && SUCCEEDED(_item->GetDisplayName(SIGDN_FILESYSPATH, &_name))) {
			// Filter by name
			if (std::regex_match(_name, _filter)) {
				std::wstring _str = _name;

				CoTaskMemFree(_name);

				return _str;
			}

			CoTaskMemFree(_name);
		}
	}

	return L"";
}

BOOL folder_view::enumerate_callback(HWND _hwnd, LPARAM _lparam)
{
	auto _windows = reinterpret_cast<std::vector<HWND>*>(_lparam);

	// Get class name
	char _classname[257];
	auto _count = GetClassNameA(_hwnd, _classname, 256);

	_classname[_count] = 0;

	if (_count == 13 && (!std::strcmp(_classname, "CabinetWClass") || !std::strcmp(_classname, "ExploreWClass"))) {
		_windows->push_back(_hwnd);
	}

	return TRUE;
}
