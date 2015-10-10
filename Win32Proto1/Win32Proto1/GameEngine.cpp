#include "GameEngine.h"
#include "Table.h"
#include "Card.h"
#include <tchar.h>
#include <string>

#include "gdiplus.h"
#include "gdiplusgraphics.h"

using namespace Gdiplus;

//
// Form widgets for creating user profile.
//
static HWND hTextboxUsername = NULL;
static HWND hTextboxPassword = NULL;
static HWND hTextboxConfirmPassword = NULL;

//
// Game Engine constructor
//
GameEngine::GameEngine(HINSTANCE hInst, HWND hWnd)
{
	// Create a new Game Engine
	_gameState = STATE_INITIAL;

	// Store the handle to our application instance hInst
	_hInst = hInst;
	_hWnd = hWnd;

	_table = new Table();

}

Table* GameEngine::getTable() { return _table; }

HWND GameEngine::getHWnd() { return _hWnd; }

void GameEngine::setState(int state) { _gameState = state; }

//
// Render game
//
void GameEngine::Paint(HDC hdc) {

	TCHAR buff[512];

	//
	// Clear window of all graphics
	//
	HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	RECT rect;

	rect.left =		0;
	rect.top =		0;
	rect.right =	Table::TABLE_WIDTH;
	rect.bottom =	Table::TABLE_HEIGHT;

	FillRect(hdc, &rect, whiteBrush);

	//
	// Clear and hide all widgets.
	//
	if (hTextboxUsername != NULL) {
		SetWindowText(hTextboxUsername, L"");
		ShowWindow(hTextboxUsername, SW_HIDE);
	}
	if (hTextboxPassword != NULL) {
		SetWindowText(hTextboxPassword, L"");
		ShowWindow(hTextboxPassword, SW_HIDE);
	}
	if (hTextboxConfirmPassword != NULL) {
		SetWindowText(hTextboxConfirmPassword, L"");
		ShowWindow(hTextboxConfirmPassword, SW_HIDE);
	}

	//
	// Now draw stuff based on the game state
	//

	switch (_gameState) {

		case STATE_INITIAL:
			// Show introduction...
			TextOutW(hdc, 200, 60, buff, wsprintf(buff, L"Team Eta Blackjack!"));
			TextOut(hdc, 200, 90, buff, wsprintf(buff, L"Welcome!"));
			break;

		case STATE_CREATE_PROFILE:
			//
			// Show profile creation...
			//
			// Input boxes
			// http://stackoverflow.com/questions/7598067/how-to-create-a-windows-style-textbox-in-a-c-win32-application
			//
			TextOutW(hdc, 50, 40, buff, wsprintf(buff, L"Username:"));
			TextOutW(hdc, 50, 80, buff, wsprintf(buff, L"Password:"));
			TextOutW(hdc, 50, 120, buff, wsprintf(buff, L"Confirm Password:"));
	
			if (hTextboxUsername == NULL) {
				hTextboxUsername = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 210, 40, 140, 30, _hWnd, NULL, NULL, NULL);
				hTextboxPassword = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD, 210, 80, 140, 30, _hWnd, NULL, NULL, NULL);
				hTextboxConfirmPassword = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD, 210, 120, 140, 30, _hWnd, NULL, NULL, NULL);
			} else {
				ShowWindow(hTextboxUsername, SW_SHOW);
				ShowWindow(hTextboxPassword, SW_SHOW);
				ShowWindow(hTextboxConfirmPassword, SW_SHOW);
			}
			break;


		case STATE_PLAYING:
			//
			// render card playing table
			//
			_table->Paint(hdc);
			break;
	}


}



