#pragma once

#ifndef CARD_H
#define CARD_H

#include <windows.h>

class Card
{

private:

	int _face;
	int _suit;
	bool _isFacedown;

	static constexpr int CARD_WIDTH		= 50;
	static constexpr int CARD_HEIGHT	= 100;


public:

	Card(int face, int suit);
	Card(int face, int suit, bool isFacedown);

	void Paint(HDC hdc, int x, int y);

	int GetFace();

	int GetSuit();
	
	int GetValue();

	bool isFacedown();

	static constexpr int CLUBS		= 1;
	static constexpr int DIAMONDS	= 2;
	static constexpr int HEARTS		= 3;
	static constexpr int SPADES		= 4;

	static constexpr int ACE	= 1;
	static constexpr int TWO	= 2;
	static constexpr int THREE	= 3;
	static constexpr int FOUR	= 4;
	static constexpr int FIVE	= 5;
	static constexpr int SIX	= 6;
	static constexpr int SEVEN	= 7;
	static constexpr int EIGHT	= 8;
	static constexpr int NINE	= 9;
	static constexpr int TEN	= 10;
	static constexpr int JACK	= 11;
	static constexpr int QUEEN	= 12;
	static constexpr int KING	= 13;



};

#endif