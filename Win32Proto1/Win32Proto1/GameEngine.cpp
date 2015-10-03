#include "GameEngine.h"
#include "Card.h"
#include <tchar.h>
#include <string>

// #include "gdiplus.h"
// #include "gdiplusgraphics.h"


// Game Engine constructor
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

	// TextOut(hdc, 25, 25, greeting, _tcslen(greeting));
	// TextOut(hdc, 200, 60, buff, wsprintf(buff, L"Game engine! ? %c ...", '?'));
	TextOutW(hdc, 200, 60, buff, wsprintf(buff, L"Eta Blackjack! ?"));
	
	// wchar_t mStr[] = { 9658,0,0 };
	// HFONT hfont = CreateFontW(48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial Unicode MS");
	// SelectObject(hdc, hfont);
	// TextOutW(hdc, 10, 10, L"?", 2);
	// DeleteObject(hfont);
	// std::wstring spade = L"?";
	// const wchar_t* szName = spade.c_str();
	// TextOutW(hdc, 200, 80, szName, 1);

	Card* card1 = new Card(Card::ACE, Card::SPADES, true);
	card1->Paint(hdc, 30, 30);

	Card* card2 = new Card(Card::ACE, Card::SPADES);
	card2->Paint(hdc, 50, 50);

	Card* card3 = new Card(Card::JACK, Card::HEARTS);
	card3->Paint(hdc, 30, 200);

	Card* card4 = new Card(Card::TEN, Card::SPADES);
	card4->Paint(hdc, 50, 220);

	TextOut(hdc, 200, 160, buff, wsprintf(buff, L"Welcome!"));

	delete card1;
	delete card2;
	delete card3;
	delete card4;

}



