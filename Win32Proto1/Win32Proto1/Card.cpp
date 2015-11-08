#include "Hand.h"
#include <windows.h>
#include "tchar.h"

#include "gdiplus.h"
#include "gdiplusgraphics.h"

using namespace Gdiplus;


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

void Card::setFacedown(bool b) {
	_isFacedown = b;
}


//
// More notes on Handle to Device Context (HDC) and implementing
// a Paint() method
// http://www.codeproject.com/Articles/1988/Guide-to-WIN-Paint-for-Beginners
//
void Card::Paint(HDC hdc, int x, int y) {

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

	//
	// Display face value
	//

	TCHAR buff[10];
	char valueChar[10];

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
			//
			// It must be a digit between 2 and 9, so print it to a 
			// buffer TextOutW() can take as a parameter.
			//
			TextOutW(hdc, x+3, y+3, buff, wsprintf(buff, L"%d", _face));
	}

	//
	// Now display the graphic representing the suit. 
	//

	Graphics graphics(hdc);

	Image imageClub(	L"image-club-icon.png"	);
	Image imageDiamond(	L"image-diamond-icon.png"	);
	Image imageHeart(	L"image-heart-icon.png"	);
	Image imageSpade(	L"image-spade-icon.png"	);

	// Pen pen(Color(255, 255, 0, 0), 2);

	Rect destRect(x + 2, y+20 + 2, 15, 15);

	switch (_suit) {
		case CLUBS:
			graphics.DrawImage(&imageClub, destRect);
			break;
		case DIAMONDS:
			graphics.DrawImage(&imageDiamond, destRect);
			break;
		case HEARTS:
			graphics.DrawImage(&imageHeart, destRect);
			break;
		case SPADES:
			graphics.DrawImage(&imageSpade, destRect);
			break;
	}

}


