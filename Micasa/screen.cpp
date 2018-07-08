#include "screen.hpp"

fipWinImage screen::_im;
int screen::_width = 0;
int screen::_height = 0;
HWND screen::_main_window = nullptr;
HWND screen::_image_window = nullptr;
std::wstring screen::_current_directory;

void screen::initialize(HINSTANCE _instance, HINSTANCE _prev_instance, LPSTR _cmd, int _cmd_show)
{
	_width = 1920;
	_height = 1080;

	// Register main class
	WNDCLASSEX _class;

	_class.cbSize = sizeof(WNDCLASSEX);
	_class.style = 0;
	_class.lpfnWndProc = &main_window_callback;
	_class.cbClsExtra = 0;
	_class.cbWndExtra = 0;
	_class.hInstance = _instance;
	_class.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
	_class.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	_class.lpszMenuName = nullptr;
	_class.lpszClassName = MAIN_WINDOW_CLASS;
	_class.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	if (!RegisterClassEx(&_class)) {
		throw std::runtime_error("Could not register class:" MAIN_WINDOW_CLASS);
	}

	// Create main window
	_main_window = CreateWindowExA(
		WS_EX_LAYERED,
		MAIN_WINDOW_CLASS,
		"Micasa",
		0,
		0, 0,
		_width, _height,
		nullptr,
		nullptr,
		_instance,
		nullptr);

	if (_main_window == nullptr) {
		throw std::runtime_error("Window creation failed.");
	}

	// Clear all styles and make transparent
	SetWindowLong(_main_window, GWL_STYLE, 0);
	SetLayeredWindowAttributes(_main_window, 0, (255 * 45) / 100, LWA_ALPHA);

	// Register image class
	_class.cbSize = sizeof(WNDCLASSEX);
	_class.style = 0;
	_class.lpfnWndProc = &image_window_callback;
	_class.cbClsExtra = 0;
	_class.cbWndExtra = 0;
	_class.hInstance = _instance;
	_class.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
	_class.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	_class.lpszMenuName = nullptr;
	_class.lpszClassName = IMAGE_WINDOW_CLASS;
	_class.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	if (!RegisterClassEx(&_class)) {
		throw std::runtime_error("Could not register class:" IMAGE_WINDOW_CLASS);
	}

	// Create image window
	_image_window = CreateWindowExA(
		0,
		IMAGE_WINDOW_CLASS,
		nullptr,
		0,
		0, 0,
		0, 0,
		_main_window,
		nullptr,
		_instance,
		nullptr);

	if (_image_window == nullptr) {
		throw std::runtime_error("Window creation failed.");
	}

	// Clear all styles
	SetWindowLong(_image_window, GWL_STYLE, 0);
	SetWindowPos(_image_window, 0, 0, 0, 0, 0, 0);
}

void screen::show()
{
	ShowWindow(_main_window, SW_MAXIMIZE);
	ShowWindow(_image_window, SW_NORMAL);
}

auto start = std::chrono::steady_clock::now();
void screen::show_image(const wchar_t * _path)
{
	if (_im.loadU(_path)) {
		int _w = _im.getWidth();
		int _h = _im.getHeight();
		int _x = _width / 2 - _w / 2;
		int _y = _height / 2 - _h / 2;

		//MoveWindow(_image_window, _x, _y, _w, _h, FALSE);
		MoveWindow(_image_window, 0, 0, 0, 0, FALSE);
		RedrawWindow(_image_window, nullptr, nullptr, RDW_INTERNALPAINT | RDW_INVALIDATE);
		SetTimer(_image_window, 1, 10, nullptr);
		start = std::chrono::steady_clock::now();

		// Get directory
		std::wstring _dir(_path); 
		auto _pos = _dir.find_last_of(L"\\");

		if (_pos != std::wstring::npos) {
			_dir = _dir.substr(0, _pos);

			// Different directory
			if (_current_directory != _dir) {
				_current_directory = _dir;
			}
		}
	}
}

void screen::main()
{
	MSG _msg;

	while (GetMessage(&_msg, nullptr, 0, 0) > 0) {
		if (_msg.message == WM_KEYUP && _msg.wParam == VK_ESCAPE) {
			PostQuitMessage(0);
		} else if (_msg.message == WM_KEYUP && _msg.wParam == VK_SPACE) {
			//SetTimer(_image_window, 1, 10, nullptr);
			screen::show_image(L"P:/test0.jpg");
		}

		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}
}

LRESULT screen::main_window_callback(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg) {
	case WM_CLOSE:
		DestroyWindow(_hwnd);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);

		break;
	default:
		return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
	}

	return 0;
}

LRESULT screen::image_window_callback(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	
	switch (_msg) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		RECT rct;
		auto hdc = BeginPaint(_hwnd, &ps);
		GetWindowRect(_hwnd, &rct);
		//printf("(%i/%i) (%i/%i)\n", rct.left, rct.top, rct.right, rct.bottom);
		rct.bottom -= rct.top;
		rct.right -= rct.left;
		rct.left = rct.top = 0;
		_im.draw(hdc, rct);
		//printf("%i, %i\n", rct.right, rct.bottom);
		EndPaint(_hwnd, &ps);
		break;
	}
	case WM_TIMER:
	{
		double rating = image_scaling_function(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count());
		
		if (rating >= 1) {
			KillTimer(_hwnd, _wparam);
			rating = 1;
		}
		int _w = _im.getWidth()*rating;
		int _h = _im.getHeight()*rating;

		/*_w |= 1;
		_h |= 1;*/

		int _x = _width / 2 - _w / 2;
		int _y = _height / 2 - _h / 2;
		_y &= 0xfffffffe;
		_x &= 0xfffffffe;
		//_x = _y = 100;
		MoveWindow(_hwnd, _x, _y, _w, _h, FALSE);
		RedrawWindow(_hwnd, 0, 0, RDW_INTERNALPAINT | RDW_INVALIDATE);

		break;
	}
	default:
		return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
	}

	return 0;
}

double screen::image_scaling_function(long long _time)
{
//	return std::log(_time / 200000. + 1);
	//auto w = -std::exp(-(_time + _time - _last) / 200000.f) + 1.05f;
	//_last = _time;
	auto r = -std::exp(-_time / 100000.) + 1.05;
	//r = (r + w) / 2.f;
	//auto r = _time / 1000000.f;
	printf("%lli %f\n", _time, r);

	return r;
}
