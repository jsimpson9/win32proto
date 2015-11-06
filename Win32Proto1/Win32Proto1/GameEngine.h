#pragma once

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <windows.h>

#include "Table.h"

#include "AbstractViewComponent.h"
#include "WelcomeView.h"
#include "CreateProfileView.h"
#include "User.h"

class GameEngine
{

private:

	//
	// Private constructor and static instance
	// for singleton pattern.
	//
	GameEngine(HINSTANCE hInst, HWND hWnd);
	static GameEngine* _gameEngine;

	//
	// A handle to the application instance and handle to the window.
	//
	HINSTANCE	_hInst;
	HWND		_hWnd;

	int			_gameState;
	int			_previousState;

	//
	// All of our views. 
	//
	AbstractViewComponent*			_welcomeView;
	AbstractViewComponent*			_createProfileView;
	AbstractViewComponent*			_loginView;
	AbstractViewComponent*			_table;
	AbstractViewComponent*			_bankingView;

	//
	// The current logged in user, or null if no session
	// is currently available
	//
	User* _user;

public:



	//
	// Constants representing game state
	//
	static constexpr int STATE_INITIAL			= 1;
	static constexpr int STATE_CREATE_PROFILE	= 2;
	static constexpr int STATE_LOGIN			= 3;
	static constexpr int STATE_PLAYING			= 4;
	static constexpr int STATE_FINISHED			= 5;
	static constexpr int STATE_BANKING			= 6;
	static constexpr int STATE_VIEW_PROFILE		= 7;

	void		Paint(HDC hdc);
	void		CreateAll(HWND hWnd, HINSTANCE hInst);

	HWND		getHWnd(); 
	void		setHWnd(HWND hWnd);

	// HINSTANCE	getHInst();
	
	Table*		getTable();

	void		setState(int state);

	User*		getUser();
	void		setUser(User* user);

	static void			init(HINSTANCE hInst, HWND hWnd);
	static void			init();

	static GameEngine*	getInstance();
	static void			setInstance(GameEngine* gameEngine);

};


#endif