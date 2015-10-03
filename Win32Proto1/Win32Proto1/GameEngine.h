#include <windows.h>

#pragma once

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class GameEngine
{

private:

	// A handle to the application instance.
	HINSTANCE _hInst;

public:

	GameEngine(HINSTANCE hInst);

	void Paint(HDC hdc);

};

#endif