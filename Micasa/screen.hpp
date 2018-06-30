#pragma once

#include <memory>
#include <Windows.h>
#include <stdexcept>

#define MAIN_WINDOW_CLASS "Micacas_main_window"
#define IMAGE_WINDOW_CLASS "Micacas_image_window"

class screen
{
public:
	void initialize(HINSTANCE _instance, HINSTANCE _prev_instance, LPSTR _cmd, int _cmd_show);
	void show();
	void main();

private:
	int _width;
	int _height;
	HWND _main_window;
	HWND _image_window;

	static LRESULT CALLBACK main_window_callback(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);
	static LRESULT CALLBACK image_window_callback(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);
};