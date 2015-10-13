#pragma once

#ifndef CREATEPROFILEVIEW_H
#define CREATEPROFILEVIEW_H

#include <windows.h>

class CreateProfileView
{
private:

	boolean _isHidden = true;

public:

	void Create(HWND hWnd, HINSTANCE hInst);
	void Paint(HDC hdc);
	void Hide();

};

#endif
