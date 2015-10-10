#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

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
GameEngine*	gameEngine;
ULONG_PTR	gdiplusToken;

#define BUTTON_HIT_ID		1001
#define BUTTON_STAND_ID		1002
#define BUTTON_BET_ID		1003
#define BUTTON_DEAL_ID		1004


//
// Function prototypes
//
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK DealButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HitButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK StandButtonProc(HWND, UINT, WPARAM, LPARAM);

WNDPROC oldDealButtonProc;
WNDPROC oldHitButtonProc;
WNDPROC oldStandButtonProc;


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

	//
	// Initialize the GameEngine
	//
	gameEngine = new GameEngine(hInst, hWnd);


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
	static HWND hHitButton;
	static HWND hStandButton;
	static HWND hDealButton;

	switch (message)
	{


	//
	// Handle window creation
	//
	case WM_CREATE:
		
		// See
		// http://www.cplusplus.com/forum/windows/11305/
		// https://msdn.microsoft.com/en-us/library/windows/desktop/ms644898%28v=vs.85%29.aspx

		hDealButton = CreateWindow(L"button", L"Deal",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			500, 370,
			50, 20,
			hWnd, (HMENU)BUTTON_HIT_ID,
			hInst, NULL);
		
		oldDealButtonProc = (WNDPROC)SetWindowLongPtr(
										hDealButton, 
										GWLP_WNDPROC, 
										(LONG_PTR)DealButtonProc);
		

		hHitButton = CreateWindow(L"button", L"Hit",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			500, 400,
			50, 20,
			hWnd, (HMENU)BUTTON_HIT_ID,
			hInst, NULL);

		oldHitButtonProc = (WNDPROC)SetWindowLongPtr(
										hHitButton,
										GWLP_WNDPROC,
										(LONG_PTR)HitButtonProc);

		hStandButton = CreateWindow(L"button", L"Stand",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			500, 430,
			50, 20,
			hWnd, (HMENU)BUTTON_STAND_ID,
			hInst, NULL);

		oldStandButtonProc = (WNDPROC)SetWindowLongPtr(
										hHitButton,
										GWLP_WNDPROC,
										(LONG_PTR)StandButtonProc);

		break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		//
		// Do application-specific layout
		//
		gameEngine->Paint(hdc);


		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:

		//
		// Shutdown GDI+
		//
		GdiplusShutdown(gdiplusToken);
		
		
		delete gameEngine;

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}



//
// Handle button clicks
//

LRESULT CALLBACK DealButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{

	switch (msg) {

		case WM_LBUTTONDOWN:

			Table* table = gameEngine->getTable();
			//
			// TODO don't allow this if we are already in a game.
			// TODO make this random
			//
			std::vector<Card*>* dealerCards = new std::vector<Card*>();
			std::vector<Card*>* playerCards = new std::vector<Card*>();

			dealerCards->push_back(new Card(Card::ACE, Card::SPADES, true));
			dealerCards->push_back(new Card(Card::JACK, Card::SPADES));

			playerCards->push_back(new Card(Card::TEN, Card::CLUBS));
			playerCards->push_back(new Card(Card::JACK, Card::DIAMONDS));

			Hand* dealerHand = new Hand(dealerCards);
			Hand* playerHand = new Hand(playerCards);

			table->setDealerHand(dealerHand);
			table->setPlayerHand(playerHand);
			
			gameEngine->setState(GameEngine::STATE_PLAYING);

			//
			// Force redraw of window, which should now render the new
			// card data. 
			//
			// https://msdn.microsoft.com/en-us/library/dd162911%28VS.85%29.aspx
			// http://stackoverflow.com/questions/2325894/difference-between-invalidaterect-and-redrawwindow
			//
			RedrawWindow(gameEngine->getHWnd(), NULL, NULL, 
							RDW_INVALIDATE | RDW_UPDATENOW);


			return 0;

	}

	return CallWindowProc(oldDealButtonProc, hwnd, msg, wp, lp);
}


LRESULT CALLBACK HitButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{

	return CallWindowProc(oldHitButtonProc, hwnd, msg, wp, lp);
}

LRESULT CALLBACK StandButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{

	return CallWindowProc(oldStandButtonProc, hwnd, msg, wp, lp);
}
