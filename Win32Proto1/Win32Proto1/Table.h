#pragma once

#ifndef TABLE_H
#define TABLE_H

#include <windows.h>
#include "AbstractViewComponent.h"
#include "Hand.h"

class Table : public AbstractViewComponent 
{

private:

	Hand* _dealerHand;
	Hand* _playerHand;

	int _tableState;

	void updateHandMessage(
							HWND textarea,
							char* name,
							Hand* hand);



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

	void setState(int state);

	int getState(); 

	void updateTextarea(
						HWND textarea,
						char* message);


};

#endif
