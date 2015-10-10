#include <windows.h>
#include "Table.h"
#include "Hand.h"

Table::Table() {
	_dealerHand = new Hand(new std::vector<Card*>());
	_playerHand = new Hand(new std::vector<Card*>());
}

Hand* Table::getDealerHand() { return _dealerHand; }

Hand* Table::getPlayerHand() { return _playerHand; }

void Table::setDealerHand(Hand* hand) { _dealerHand = hand; }

void Table::setPlayerHand(Hand* hand) { _playerHand = hand; }

void Table::Paint(HDC hdc) {
	if (_dealerHand != NULL) {
		_dealerHand->Paint(hdc, 10, 10);
	}
	if (_playerHand != NULL) {
		_playerHand->Paint(hdc, 10, 300);
	}
}
