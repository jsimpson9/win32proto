#include "GameEngine.h"
#include <tchar.h>
#include <string>

#include "gdiplus.h"
#include "gdiplusgraphics.h"

#include "WelcomeView.h"
#include "CreateProfileView.h"
#include "LoginView.h"
#include "Table.h"
#include "BankingView.h"
#include "User.h"


using namespace Gdiplus;


//
// Game Engine constructor
//
GameEngine::GameEngine(HINSTANCE hInst, HWND hWnd)
{
	// Create a new Game Engine

	// Set initial state
	_gameState		= STATE_INITIAL;
	_previousState	= -1;

	// Store the handle to our application instance hInst
	_hInst	= hInst;
	_hWnd	= hWnd;


	//
	// Create instances of all of our UI views
	//
	_welcomeView		= new WelcomeView();
	_createProfileView	= new CreateProfileView();
	_loginView			= new LoginView();
	_table				= new Table();
	_bankingView		= new BankingView();

}

Table* GameEngine::getTable() { return (Table*)_table; }

HWND GameEngine::getHWnd() { return _hWnd; }

void GameEngine::setHWnd(HWND hWnd) { _hWnd = hWnd; }

// HINSTANCE GameEngine::getHInst() { return _hInst; }


//
// Why C++ is this necessary when _gameEngine is ALREADY defined as 
// private static in the .h file ????????????????????????
//
GameEngine* GameEngine::_gameEngine = NULL;

void GameEngine::init(HINSTANCE hInst, HWND hWnd) {
	if (_gameEngine == NULL) {
		_gameEngine = new GameEngine(hInst, hWnd);
	}
}

void GameEngine::init() {
	if (_gameEngine == NULL) {
		_gameEngine = new GameEngine(NULL, NULL);
	}
}

GameEngine*	GameEngine::getInstance() { return _gameEngine; }

void		GameEngine::setInstance(GameEngine* eng) { _gameEngine = eng; }


void GameEngine::setState(int state) { 
	if (_gameState != state) {
		_previousState = _gameState;
		_gameState = state;
	}
}

void GameEngine::CreateAll(HWND hWnd, HINSTANCE hInst) {

	_welcomeView->Create(hWnd, hInst);
	_createProfileView->Create(hWnd, hInst);
	_loginView->Create(hWnd, hInst);
	_table->Create(hWnd, hInst);
	_bankingView->Create(hWnd, hInst);

}


//
// Render game
//
void GameEngine::Paint(HDC hdc) {


	//
	// Clear window of all graphics
	//
	HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	RECT rect;

	rect.left =		0;
	rect.top =		0;
	rect.right =	Table::TABLE_WIDTH;
	rect.bottom =	Table::TABLE_HEIGHT;

	//
	// TODO this FillRect might not even be necessary 
	// given that the previoud view should now be hiding itself. 
	//
	// TODO create an abstract base class for all View
	// objects, and move this FillRect into that.
	//
	// Erase anything we drew with graphics calls.
	//
	FillRect(hdc, &rect, whiteBrush);

	//
	// Ensure all views are hidden.
	// This should hide all child widgets which do not 
	// get overwritten by the above FillRect().
	//
	// Then later reveal one of them based
	// on game engine state.
	//
	switch (_previousState) {

		case STATE_INITIAL:
			// hide introduction...
			_welcomeView->Hide();
			break;

		case STATE_CREATE_PROFILE:
			_createProfileView->Hide();
			break;

		case STATE_LOGIN:
			_loginView->Hide();
			break;

		case STATE_PLAYING:

			_table->Hide();
			break;

		case STATE_BANKING:

			_bankingView->Hide();
			break;
	}

	//
	// Now draw a view based on the game state
	//

	switch (_gameState) {

		case STATE_INITIAL:

			// Show introduction...
			_welcomeView->Paint(hdc);
			break;

		case STATE_CREATE_PROFILE:

			_createProfileView->Paint(hdc);
			break;

		case STATE_LOGIN:

			_loginView->Paint(hdc);
			break;

		case STATE_PLAYING:
			//
			// render card playing table
			//
			_table->Paint(hdc);
			break;

		case STATE_BANKING:
			//
			// render bank view
			//
			_bankingView->Paint(hdc);
			break;
	}


}


User*	GameEngine::getUser()			{ return _user; }
void	GameEngine::setUser(User* user)	{ _user = user; }




