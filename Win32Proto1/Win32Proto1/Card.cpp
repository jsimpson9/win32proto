#include "Hand.h"
#include <windows.h>
#include "tchar.h"

// #include <atlconv.h>

// static TCHAR CLUB_TCHAR[]		= _T("?");
// static TCHAR DIAMOND_TCHAR[]	= _T("?");
// static TCHAR HEART_TCHAR[]		= _T("?");
// static TCHAR SPADE_TCHAR[]		= _T("?");


Card::Card(int face, int suit) {
	_face = face;
	_suit = suit;
	_isFacedown = false;
}

Card::Card(int face, int suit, bool isFacedown) {
	_face		= face;
	_suit		= suit;
	_isFacedown = isFacedown;
}


int Card::GetFace() {
	return _face;
}

int Card::GetSuit() {
	return _suit;
}

int Card::GetValue() {
	if (_face < 10) { 
		return _face; 
	}
	return 10;
}

bool Card::isFacedown() {
	return _isFacedown;
}

//
// More notes on Handle to Devcie Context (HDC) and implementing
// a Paint() method
// http://www.codeproject.com/Articles/1988/Guide-to-WIN-Paint-for-Beginners
//
void Card::Paint(HDC hdc, int x, int y) {


	char valueChar[10];
	
	/*
	switch (_suit) {
		case CLUB:
			break;
		case DIAMOND:
			strcpy(suitChar,"?");
			break;
		case HEART:
			strcpy(suitChar,"?");
			break;
		case SPADE:
			strcpy(suitChar,"?");
			break;
	}
	*/


	HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	
	RECT rect;

	rect.left	= x;
	rect.top	= y;
	rect.right	= x+CARD_WIDTH;
	rect.bottom = y+CARD_HEIGHT;

	FillRect(hdc, &rect, blackBrush);

	//
	// If this card is face down, then we are done here.
	//
	if (_isFacedown) {
		return;
	}

	rect.left	+= 1;
	rect.top	+= 1;
	rect.right	-= 1; 
	rect.bottom -= 1;

	FillRect(hdc, &rect, whiteBrush);

	TCHAR buff[10];
	// TextOutW(hdc, x+3, y+3, buff, wsprintf(buff, L"%c", valueChar));

	switch (_face) {
		case ACE:
			TextOutW(hdc, x + 3, y + 3, L"A", 1);
			break;
		case JACK:
			TextOutW(hdc, x + 3, y + 3, L"J", 1);
			strcpy_s(valueChar, "J");
			break;
		case QUEEN:
			TextOutW(hdc, x + 3, y + 3, L"Q", 1);
			strcpy_s(valueChar, "Q");
			break;
		case KING:
			TextOutW(hdc, x + 3, y + 3, L"K", 1);
			strcpy_s(valueChar, "K");
			break;
		case TEN:
			TextOutW(hdc, x + 3, y + 3, L"10", 2);
			break;
		default:
			TextOutW(hdc, x + 3, y + 3, L"A", 1);
			TextOutW(hdc, x+3, y+3, buff, wsprintf(buff, L"%d", _face));
	}


}


