#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "AchievementManager.h"
#ifndef USER_H
#define USER_H

using namespace std;

/*
	Purpose: Create User info. Sets info and creates formatted string to send to Persistence Manager
*/
class User
{
private:
	int size;
	int BlackJackCount;
	struct userInfo
	{
		string userName;
		string password;
		int wins;
		int loses;
		int money;

		//
		// This isn't building... fix me
		//
		// string *achievments[];

	}*UI;
	AchievementManager *AM;
	//==================SETTERS===================//
	void setUserName(string);
	void setPassword(string);
	void setWins(int);
	void setLoses(int);
	void setMoney(int);
	void setAchievementManager(string);
	
public:
	User();
	User(string* info);
	User(string, string, int, int, int, string*[]);
	~User();
	int newUser(string,string);
	string toString();

	string getUsername();
	//string getPassword();
	int getBalance();
	void setBalance(int b);

	//================GETTERS=================//
	string getUserName();
	string getPassword();
	int getWins();
	int getLoses();
	int getMoney();
	string getAchievementManager();
	
	//==============Update and Check Achievement Methods ================//
	void updateWins(int x);
	void updateMoney(int x);
	void updateBJC();
	void zeroBJC();

};


#endif
