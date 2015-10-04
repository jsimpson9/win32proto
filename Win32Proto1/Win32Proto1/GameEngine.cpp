#include "GameEngine.h"
#include "Card.h"
#include <tchar.h>
#include <string>

#include "gdiplus.h"
#include "gdiplusgraphics.h"

using namespace Gdiplus;

//
// Game Engine constructor
//
GameEngine::GameEngine(HINSTANCE hInst)
{
	// Create a new Game Engine

	// Store the handle to our application instance hInst
	_hInst = hInst;
}

//
// Render game
//
void GameEngine::Paint(HDC hdc) {

	TCHAR buff[512];

	TextOutW(hdc, 200, 60, buff, wsprintf(buff, L"Eta Blackjack!"));
	
	Card* card1 = new Card(Card::ACE, Card::SPADES, true);
	card1->Paint(hdc, 30, 30);

	Card* card2 = new Card(Card::ACE, Card::SPADES);
	card2->Paint(hdc, 50, 50);

	Card* card3 = new Card(Card::TWO, Card::HEARTS);
	card3->Paint(hdc, 30, 200);

	Card* card4 = new Card(Card::TEN, Card::DIAMONDS);
	card4->Paint(hdc, 50, 220);

	Card* card5 = new Card(Card::TEN, Card::CLUBS);
	card5->Paint(hdc, 70, 240);

	//
	// Try some Gdiplus APIs...
	//
	
	// Graphics graphics(hdc);
	// Image image(L"club-icon.png");
	// Image image(L"diamond-icon.png");
	// Image image(L"heart-icon.png");
	// Image image(L"spade-icon.png");
	// Pen pen(Color(255, 255, 0, 0), 2);
	// 
	// Rect destRect(50+2, 70+2, 15, 15);
	// graphics.DrawRectangle(&pen, destRect);
	// graphics.DrawImage(&image, destRect);
	
	TextOut(hdc, 200, 160, buff, wsprintf(buff, L"Welcome!"));

	delete card1;
	delete card2;
	delete card3;
	delete card4;
	delete card5;

}



