#pragma once

#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <windows.h>
#include "AbstractViewComponent.h"

class WelcomeView : public AbstractViewComponent
{
private:

public:

	void Create(HWND hWnd, HINSTANCE hInst);
	void Paint(HDC hdc);
	void Hide();

};

#endif

