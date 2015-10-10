#include "GameEngine.h"
#include "Table.h"
#include "Card.h"
#include <tchar.h>
#include <string>

#include "gdiplus.h"
#include "gdiplusgraphics.h"

using namespace Gdiplus;

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
	// Clear window
	//
	HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	RECT rect;

	rect.left =		0;
	rect.top =		0;
	rect.right =	Table::TABLE_WIDTH;
	rect.bottom =	Table::TABLE_HEIGHT;

	FillRect(hdc, &rect, whiteBrush);

	//
	// Now draw stuff based on the game state
	//

	switch (_gameState) {

		case STATE_INITIAL:
			// Show introduction...
			TextOutW(hdc, 200, 60, buff, wsprintf(buff, L"Eta Blackjack!"));
			TextOut(hdc, 200, 160, buff, wsprintf(buff, L"Welcome!"));
			break;

		case STATE_PLAYING:
			//
			// render card playing table
			//
			_table->Paint(hdc);
			break;
	}


}



