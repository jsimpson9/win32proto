#pragma once

#ifndef CREATEPROFILEVIEW_H
#define CREATEPROFILEVIEW_H

#include <windows.h>
#include "AbstractViewComponent.h"

class CreateProfileView : public AbstractViewComponent
{
private:


public:

	void Create(HWND hWnd, HINSTANCE hInst);
	void Paint(HDC hdc);
	void Hide();

};

#endif
