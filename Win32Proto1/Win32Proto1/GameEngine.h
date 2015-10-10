#pragma once

#include <windows.h>
#include "Table.h"

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class GameEngine
{

private:

	// A handle to the application instance.
	HINSTANCE _hInst;
	HWND _hWnd;
	Table* _table;

	int _gameState;

public:

	static constexpr int STATE_INITIAL			= 0;
	static constexpr int STATE_CREATE_PROFILE	= 1;
	static constexpr int STATE_PLAYING			= 2;
	static constexpr int STATE_FINISHED			= 3;

	GameEngine(HINSTANCE hInst, HWND hWnd);

	void Paint(HDC hdc);

	HWND getHWnd(); 

	Table* getTable();

	void setState(int state);
};

#endif