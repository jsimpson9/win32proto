#pragma once

#ifndef TABLE_H
#define TABLE_H

#include <windows.h>
#include "Hand.h"

class Table
{

private:

	Hand* _dealerHand;
	Hand* _playerHand;

public:
	
	static constexpr int TABLE_WIDTH	= 600;
	static constexpr int TABLE_HEIGHT	= 600;

	Table();

	void Create(HWND hWnd, HINSTANCE hInst);
	void Paint(HDC hdc);
	void Hide();

	Hand* getDealerHand();

	Hand* getPlayerHand(); 

	void setDealerHand(Hand* hand);

	void setPlayerHand(Hand* hand);

};

#endif
