#include "screen.hpp"

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
	_class.hbrBackground = CreateSolidBrush(RGB(255,255,255));
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
		100, 100,
		_main_window,
		nullptr,
		_instance,
		nullptr);

	if (_image_window == nullptr) {
		throw std::runtime_error("Window creation failed.");
	}

}

void screen::show()
{
	ShowWindow(_main_window, SW_MAXIMIZE);
	ShowWindow(_image_window, SW_NORMAL);
}

void screen::main()
{
	MSG _msg;

	while (GetMessage(&_msg, nullptr, 0, 0) > 0) {
		if (_msg.message == WM_KEYUP && _msg.wParam == VK_ESCAPE) {
			PostQuitMessage(0);
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
	default:
		return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
	}

	return 0;
}
