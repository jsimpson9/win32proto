#pragma once
/*
PURPOSE: Handles Money Transfers
*/
#include "PersistenceManager.h"
#include "User.h"
using namespace std;
class BankManager
{
private:
	PersistenceManager *PM;
	User *U;
public:
	BankManager();
	~BankManager();
	void transferMoney(string, string, int);
	//borrowMoney
};

