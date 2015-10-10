#include <windows.h>
#include "Hand.h"
#include "Card.h"

Hand::Hand(std::vector<Card*>* cards) {
	_cards = cards;
}

//
// Get the value of the hand. This returns a vector because
// a hand can have multiple values when aces are present in the hand. 
// But note only one ace can ever be 11.
//
std::vector<int>* Hand::GetValues() {
	
	std::vector<int>* ret = new std::vector<int>();

	if (_cards == NULL) {
		return ret;
	}

	bool foundAce = false;

	int value = 0;
	for (unsigned int i = 0; i < _cards->size(); i++) {
		Card* card = _cards->at(i);
		value += card->GetValue();
		if (card->GetValue() == 1) {
			//
			// Found an ace
			//
			foundAce = true;
		}
	}
	ret->push_back(value);

	if (foundAce) {
		// Consider the case where one of the aces is used as 11.
		value += 10;
		ret->push_back(value);
	}

	return ret;
}

bool Hand::isBusted() {
	std::vector<int>* values = GetValues();
	for (unsigned int i = 0; i < values->size(); i++) {
		int val = values->at(i);
		if (val > 21) {
			return true;
		}
	}
	return false;
}

bool Hand::isBlackjack() {

	if (!isBusted()) {
		std::vector<int>* values = GetValues();
		for (int i = 0; i < values->size(); i++) {
			int val = values->at(i);
			if (val == 21) {
				return true;
			}
		}
	}

	return false;
}

std::vector<Card*>* Hand::GetCards() {
	return _cards;
}

void Hand::Paint(HDC hdc, int x, int y) {

	int xOffset = 0;
	int yOffset = 0;

	for (unsigned int i = 0; i < _cards->size(); i++) {
		Card* card = _cards->at(i);
		card->Paint(hdc, x + xOffset, y + yOffset);
		xOffset += 20;
		yOffset += 20;
	}

}

