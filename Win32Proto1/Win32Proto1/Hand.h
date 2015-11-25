#pragma once

#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"

class Hand
{

private:
 
	int _betAmount;

	std::vector<Card*>* _cards;

public:

	Hand(std::vector<Card*>* cards);

	Hand();
	~Hand();

	void Paint(HDC hdc, int x, int y);

	std::vector<int>* GetValues();

	std::vector<Card*>* GetCards();

	bool isBusted();

	bool isBlackjack();

	void dealCard(bool isFacedown);

	int getBetAmount();
	void setBetAmount(int amount);

};

#endif