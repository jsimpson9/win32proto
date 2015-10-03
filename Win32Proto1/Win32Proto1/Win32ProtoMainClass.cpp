#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "GameEngine.h"

static TCHAR szWindowClass[] = _T("win32proto");
static TCHAR szTitle[] = _T("Eta Blackjack");

HINSTANCE hInst;
GameEngine* gameEngine;

//
// Function prototypes
//
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//
// WINAPI WinMain adapted from microsoft tutorial
//
// https://msdn.microsoft.com/en-us/library/bb384843.aspx
//
int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{

	//
	// The WNDCLASSEX structure holdinfo about the 
	// window class, like like icon, small icon, cursor style, etc. 
	//
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;

	wcex.hIcon =	LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hIconSm =	LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor =	LoadCursor(NULL, IDC_ARROW);

	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Error RegisterClassEx() failed!"),
			_T("Eta lackjack"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable

					   // The parameters to CreateWindow explained:
					   // szWindowClass: the name of the application
					   // szTitle: the text that appears in the title bar
					   // WS_OVERLAPPEDWINDOW: the type of window to create
					   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
					   // 600, 100: initial size (width, length)
					   // NULL: the parent of this window
					   // NULL: this application does not have a menu bar
					   // hInstance: the first parameter from WinMain
					   // NULL: not used in this application
	HWND hWnd = CreateWindowW(
					szWindowClass,
					szTitle,
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT, CW_USEDEFAULT,
					600, 600,
					NULL,
					NULL,
					hInstance,
					NULL
		);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//
	// Initialize the GameEngine
	//
	gameEngine = new GameEngine(hInst);

	return (int)msg.wParam;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		//
		// Do application-specific layout
		//
		gameEngine->Paint(hdc);


		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:

		delete gameEngine;

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}