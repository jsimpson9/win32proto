#pragma once

#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"

class Hand
{

private:
 
	std::vector<Card*>* _cards;

public:

	Hand(std::vector<Card*>* cards);

	std::vector<int>* GetValues();

	std::vector<Card*>* GetCards();

	bool isBusted();

	bool isBlackjack();

};

#endif