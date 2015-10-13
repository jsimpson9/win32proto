#pragma once

#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <windows.h>
#include "AbstractViewComponent.h"

class LoginView : public AbstractViewComponent
{
private:

public:

	void Create(HWND hWnd, HINSTANCE hInst);
	void Paint(HDC hdc);
	void Hide();

};

#endif