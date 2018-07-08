#pragma once

#include <memory>
#include <cmath>
#include <stdexcept>
#include <Windows.h>
#include <string>
#include <FreeImagePlus.h>
#include <chrono>

#define MAIN_WINDOW_CLASS "Micacas_main_window"
#define IMAGE_WINDOW_CLASS "Micacas_image_window"

class screen
{
public:
	static void initialize(HINSTANCE _instance, HINSTANCE _prev_instance, LPSTR _cmd, int _cmd_show);
	static void show();
	static void show_image(const wchar_t * _path);
	static void main();

private:
	static fipWinImage _im;
	static int _width;
	static int _height;
	static HWND _main_window;
	static HWND _image_window;
	static std::wstring _current_directory;


	static void reload_current_directory();
	static LRESULT CALLBACK main_window_callback(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);
	static LRESULT CALLBACK image_window_callback(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);
	static double image_scaling_function(long long _time);
};