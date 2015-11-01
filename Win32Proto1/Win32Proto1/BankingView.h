#pragma once

#ifndef BANKINGVIEW_H
#define BANKINGVIEW_H

#include <windows.h>
#include "AbstractViewComponent.h"

class BankingView : public AbstractViewComponent
{
private:


public:

	void Create(HWND hWnd, HINSTANCE hInst);
	void Paint(HDC hdc);
	void Hide();

};

#endif