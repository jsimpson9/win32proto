#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
	Purpose: Create User info. Sets info and creates formatted string to send to Persistence Manager
*/
class user
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
		string *achievments[];
	}*UI;
	
public:
	user();
	user(string, string, int, int, int, string*[]);
	~user();
	int newUser(string,string);
	string toString();
};

/*
	Creates room in memory for userInfo.
*/
user :: user()
{
	UI = new userInfo();
}

/*
	Sets userInfo
	param: all params in userInfo
*/
user :: user(string userName, string password, int wins, int loses, int money, string *achievments[])
{
	UI->userName = userName;
	UI->password = password;
	UI->wins = wins;
	UI->loses = loses;
	UI->money = money;
	
	for (int i = 0; i < sizeof(achievments); i++)
	{
		UI->achievments[i] = achievments[i];
	}
}

user :: ~user()
{
	delete UI;
}

/*
	Create new user sets everything to 0 except
	Username and Password
	@returns -1 fail or 0 successful
*/
int user :: newUser(string userName, string pwd)
{
	struct userInfo NU = {
		userName,		//username
		pwd,			//password
		0,				//wins
		0,				//loses
		0,				//money	
		nullptr			//achievements
	};
	
	UI = &NU;
	if (!UI)
		return -1;

	return 0;
}

/*
	Convert formatted string to be pushed onto the 
	file by the Persistence Manager
*/
string user::toString()
{

}



