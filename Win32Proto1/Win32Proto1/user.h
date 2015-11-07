#pragma once
#include <iostream>
#include <fstream>
#include <string>

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
	
public:
	User();
	User(string, string, int, int, int, string*[]);
	~User();
	int newUser(string,string);
	string toString();

	string getUsername();
	string getPassword();
	int getBalance();
	void setBalance(int b);

};


#endif
