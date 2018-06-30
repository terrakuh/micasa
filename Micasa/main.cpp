#include "screen.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	screen main;

	main.initialize(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	main.show();
	main.main();
}

//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include <Windows.h>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
///*
//Mat hwnd2mat(HWND hwnd)
//{
//	HDC hwindowDC, hwindowCompatibleDC;
//
//	int height, width, srcheight, srcwidth;
//	HBITMAP hbwindow;
//	Mat src;
//	BITMAPINFOHEADER  bi;
//
//	hwindowDC = GetDC(hwnd);
//	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
//	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);
//
//	RECT windowsize;    // get the height and width of the screen
//	GetClientRect(hwnd, &windowsize);
//
//	srcheight = windowsize.bottom;
//	srcwidth = windowsize.right;
//	height = windowsize.bottom / 1;  //change this to whatever size you want to resize to
//	width = windowsize.right / 1;
//
//	src.create(height, width, CV_8UC4);
//
//	// create a bitmap
//	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
//	bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
//	bi.biWidth = width;
//	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
//	bi.biPlanes = 1;
//	bi.biBitCount = 32;
//	bi.biCompression = BI_RGB;
//	bi.biSizeImage = 0;
//	bi.biXPelsPerMeter = 0;
//	bi.biYPelsPerMeter = 0;
//	bi.biClrUsed = 0;
//	bi.biClrImportant = 0;
//
//	// use the previously created device context with the bitmap
//	SelectObject(hwindowCompatibleDC, hbwindow);
//	// copy from the window device context to the bitmap device context
//	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
//	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow
//
//	while (true) {
//		Sleep(250);
//
//		SetDIBitsToDevice(hwindowDC, 0, 0, 1920, 1080, 0, 0, 0, 1080, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);
//	}
//
//																									   // avoid memory leak
//	DeleteObject(hbwindow);
//	DeleteDC(hwindowCompatibleDC);
//	ReleaseDC(hwnd, hwindowDC);
//
//	return src;
//}
//
//int main(int argc, char **argv)
//{
//	HWND hwndDesktop = GetDesktopWindow();
//	//namedWindow("output", WINDOW_NORMAL);
//	int key = 0;
//
//	while (key != 27) {
//		Mat src = hwnd2mat(hwndDesktop);
//		// you can do some image processing here
//		imshow("output", src);
//		key = waitKey(60); // you can change wait time
//	}
//
//}*/
//
//const char g_szClassName[] = "myWindowClass";
//HDC hwindowDC;
//Mat src;
//BITMAPINFOHEADER  bi;
//FILE *output;
//RECT recta = { 30, 50, 100, 200 };
//HWND shwnd;
//// Step 4: the Window Procedure
//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	fprintf(output, "%u\n", msg);
//	switch (msg) {
//	case WM_PAINT:
//	{
//		PAINTSTRUCT ps;
//		auto hdc = BeginPaint(hwnd, &ps);
//		if (shwnd == hwnd)
//			SetDIBitsToDevice(hdc, 0, 0, 1920, 1080, 0, 0, 0, 1080, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);
//		else {
//			HBRUSH brush = CreateSolidBrush(RGB(50, 151, 151));
//
//			FillRect(hdc, &recta, brush);
//
//			DeleteObject(brush);
//		}
//		//TextOut(hdc, 0, 0, "Hello, Windows!", 15);
//		EndPaint(hwnd, &ps);
//		break;
//	}
//	case WM_CLOSE:
//		DestroyWindow(hwnd);
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hwnd, msg, wParam, lParam);
//	}
//	return 0;
//}
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow)
//{
//	WNDCLASSEX wc;
//	HWND hwnd;
//	MSG Msg;
//	fopen_s(&output, "P:/test", "wb");
//	//Step 1: Registering the Window Class
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.style = 0;
//	wc.lpfnWndProc = WndProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = hInstance;
//	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = g_szClassName;
//	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//
//	if (!RegisterClassEx(&wc)) {
//		MessageBox(NULL, "Window Registration Failed!", "Error!",
//			MB_ICONEXCLAMATION | MB_OK);
//		return 0;
//	}
//
//	// Step 2: Creating the Window
//	hwnd = CreateWindowExA(
//		WS_EX_LAYERED,
//		g_szClassName,
//		"The title of my window",
//		0,
//		0, 0, 1920, 1080,
//		NULL, NULL, hInstance, NULL);
//
//	shwnd = CreateWindowExA(
//		0,
//		g_szClassName,
//		nullptr,
//		WS_CHILD,
//		0, 0, 400, 400,
//		hwnd, NULL, hInstance, NULL);
//
//
//	if (shwnd == NULL) {
//		MessageBox(NULL, "Window Creation Failed!", ("Error!" + std::to_string(GetLastError())).c_str(),
//			MB_ICONEXCLAMATION | MB_OK);
//		return 0;
//	}
//	// clear all styles
//	SetWindowLong(hwnd, GWL_STYLE, 0);
//	//70% transparent
//	SetLayeredWindowAttributes(hwnd, 0, (255 * 70) / 100, LWA_ALPHA);
//	//SetLayeredWindowAttributes(hwnd, RGB(50,151,151), 255, LWA_COLORKEY);
//	HDC hwindowCompatibleDC;
//
//	int height, width, srcheight, srcwidth;
//	HBITMAP hbwindow;
//
//	hwindowDC = GetDC(0);
//	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
//	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);
//
//	RECT windowsize;    // get the height and width of the screen
//	GetClientRect(hwnd, &windowsize);
//
//	srcheight = windowsize.bottom;
//	srcwidth = windowsize.right;
//	height = windowsize.bottom / 1;  //change this to whatever size you want to resize to
//	width = windowsize.right / 1;
//	srcheight = 1080;
//	srcwidth = 1920;
//	width = 1920;
//	height = 1080;
//
//	src.create(height, width, CV_8UC4);
//
//	// create a bitmap
//	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
//	bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
//	bi.biWidth = width;
//	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
//	bi.biPlanes = 1;
//	bi.biBitCount = 32;
//	bi.biCompression = BI_RGB;
//	bi.biSizeImage = 0;
//	bi.biXPelsPerMeter = 0;
//	bi.biYPelsPerMeter = 0;
//	bi.biClrUsed = 0;
//	bi.biClrImportant = 0;
//
//	// use the previously created device context with the bitmap
//	SelectObject(hwindowCompatibleDC, hbwindow);
//	// copy from the window device context to the bitmap device context
//	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
//	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);
//
//	for (auto i = 0; i < width * height * 4; i += 4) {
//		src.data[i] *= 0.65;
//		src.data[i + 1] *= 0.65;
//		src.data[i + 2] *= 0.65;
//	}
//
//	SelectObject(GetDC(hwnd), hbwindow);
////	SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//	//SetWindowPos(shwnd, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
//	ShowWindow(hwnd, SW_MAXIMIZE);
//	ShowWindow(shwnd, SW_NORMAL);
//	UpdateWindow(hwnd);
//	//UpdateWindow(shwnd);
//
//	SetTimer(hwnd, 1, 5, [](HWND h, UINT, UINT_PTR id, DWORD) {
//		if (recta.right >= 500) {
//			KillTimer(h, id);
//		} else {
//			recta.right++;
//			InvalidateRect(h, nullptr, false);
//			//RedrawWindow(h, nullptr, nullptr, RDW_INTERNALPAINT);
//		}
//	});
//
//	// Step 3: The Message Loop
//	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
//		TranslateMessage(&Msg);
//		DispatchMessage(&Msg);
//	}
//	fclose(output);
//	return Msg.wParam;
//}
//
///*#include <Windows.h>
//#include <iostream>
//#include <math.h>
//#include <stdio.h>
//using namespace std;
//
//HBITMAP GetScreenBmp(HDC hdc)
//{
//	// Get screen dimensions
//	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
//	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
//	cout << "height" << nScreenHeight << "width" << nScreenWidth << endl;
//	// Create compatible DC, create a compatible bitmap and copy the screen using BitBlt()
//	HDC hCaptureDC = CreateCompatibleDC(hdc);
//	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, nScreenWidth, nScreenHeight);
//	HGDIOBJ hOld = SelectObject(hCaptureDC, hBitmap);
//	BOOL bOK = BitBlt(hCaptureDC, 0, 0, nScreenWidth, nScreenHeight, hdc, 0, 0, SRCCOPY | CAPTUREBLT);
//
//	SelectObject(hCaptureDC, hOld); // always select the previously selected object once done
//	DeleteDC(hCaptureDC);
//	return hBitmap;
//}
//
//int main()
//{
//	HDC hdc = GetDC(0);
//
//	HBITMAP hBitmap = GetScreenBmp(hdc);
//
//	BITMAPINFO MyBMInfo = { 0 };
//	MyBMInfo.bmiHeader.biSize = sizeof(MyBMInfo.bmiHeader);
//
//	// Get the BITMAPINFO structure from the bitmap
//	if (0 == GetDIBits(hdc, hBitmap, 0, 0, NULL, &MyBMInfo, DIB_RGB_COLORS)) {
//		cout << "error" << endl;
//	}
//
//	// create the bitmap buffer
//	BYTE* lpPixels = new BYTE[MyBMInfo.bmiHeader.biSizeImage/4*3]{};
//	cout << "size " << MyBMInfo.bmiHeader.biSizeImage << endl;
//	// Better do this here - the original bitmap might have BI_BITFILEDS, which makes it
//	// necessary to read the color table - you might not want this.
//	MyBMInfo.bmiHeader.biBitCount = 24;
//	MyBMInfo.bmiHeader.biCompression = BI_RGB;
//
//	// get the actual bitmap buffer
//	if (0 == GetDIBits(hdc, hBitmap, 0, MyBMInfo.bmiHeader.biHeight, (LPVOID)lpPixels, &MyBMInfo, DIB_RGB_COLORS)) {
//		cout << "error2" << endl;
//	}
//
//	for (int i = 0; i < 1920*1080*3/2; i++) {
//		//cout << hex << (int)lpPixels[i] << '\n';
//		lpPixels[i] = 255;
//	}
//
//	while (true) {
//		SetDIBitsToDevice(hdc, 0, 0, 1920, 1080, 0, 0, 0, 1080, lpPixels, &MyBMInfo, DIB_RGB_COLORS);
//		Sleep(50);
//	}
//	DeleteObject(hBitmap);
//	ReleaseDC(NULL, hdc);
//	delete[] lpPixels;
//
//	system("pause");
//
//	return 0;
//}*/