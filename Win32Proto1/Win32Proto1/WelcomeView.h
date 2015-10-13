#pragma once

#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <windows.h>

class WelcomeView
{
private:

	boolean _isHidden = true;

public:

	void Create(HWND hWnd, HINSTANCE hInst);
	void Paint(HDC hdc);
	void Hide();

};

#endif

