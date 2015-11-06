#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <ctime>

#include "Table.h"
#include "Hand.h"
#include "Card.h"

#include "gdiplus.h"
#include "gdiplusgraphics.h"

using namespace Gdiplus;

#include "GameEngine.h"

static TCHAR szWindowClass[] = _T("win32proto");
static TCHAR szTitle[] = _T("Eta Blackjack");

HINSTANCE	hInst;
ULONG_PTR	gdiplusToken;


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
	// Initialize GDI+
	// http://supercomputingblog.com/graphics/getting-started-with-gdi-in-visual-studio/
	//
	// Initialize this first, otherwise none of the GDI APIs work.
	//
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//
	// Init random number generator
	//
	srand(time(NULL));

	//
	// Initialize the GameEngine singleton. 
	//
	// GameEngine::init(hInst, hWnd);
	GameEngine::init();

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

	// static HWND hCreateProfileButton;



	switch (message)
	{


	//
	// Handle window creation
	//
	case WM_CREATE:
		
		// Create buttons
		// See
		// http://www.cplusplus.com/forum/windows/11305/
		// https://msdn.microsoft.com/en-us/library/windows/desktop/ms644898%28v=vs.85%29.aspx

		GameEngine::getInstance()->CreateAll(hWnd, hInst);
		
		break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		//
		// Do application-specific layout
		//		
		GameEngine::getInstance()->setHWnd(hWnd);
		GameEngine::getInstance()->Paint(hdc);


		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:

		//
		// Shutdown GDI+
		//
		GdiplusShutdown(gdiplusToken);
		
		delete GameEngine::getInstance();

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}




