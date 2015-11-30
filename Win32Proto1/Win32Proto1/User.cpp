#include "User.h"

/*
Creates room in memory for userInfo.
*/
User::User()
{
	UI = new userInfo();
	AM = new AchievementManager();

}

User::User(string* info)
{
	setUserName(info[0]);
	setPassword(info[1]);
	setWins(stoi(info[2]));
	setLoses(stoi(info[3]));
	setMoney(stoi(info[4]));
	setAchievementManager(info[5]);
}

/*
Sets userInfo
param: all params in userInfo
*/
User::User(string userName, string password, int wins, int loses, int money, string *achievments[])
{
	UI = new userInfo();

	UI->userName = userName;
	UI->password = password;
	UI->wins = wins;
	UI->loses = loses;
	UI->money = money;

	// 
	// for (int i = 0; i < sizeof(achievments); i++)
	// {
	//	UI->achievments[i] = achievments[i];
	// }
}

User :: ~User()
{
	delete UI;
}

/*
Create new user sets everything to 0 except
Username and Password
@returns -1 fail or 0 successful
*/
int User::newUser(string userName, string pwd)
{
	struct userInfo NU = {
		userName,		//username
		pwd,			//password
		0,				//wins
		0,				//loses
		0				//money	
						// nullptr			//achievements
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
string User::toString()
{
	string temp;
	temp = UI->userName + ", "
		+ UI->password + ", "
		+ to_string(UI->wins) + ", "
		+ to_string(UI->loses) + ", "
		+ to_string(UI->money) + ", ";
	//temp += AM->toString() + "\n";

	return temp;
}

string User::getUsername() { return UI->userName; }

//string User::getPassword() { return UI->password; }

int User::getBalance() { return UI->money; }

void User::setBalance(int b) { UI->money = b; }

//================SETTERS=================//
void User::setUserName(string userName)
{
	UI->userName = userName;
}

void User::setPassword(string password)
{
	UI->password = password;
}

void User::setWins(int wins)
{
	UI->wins = wins;
}

void User::setLoses(int loses)
{
	UI->loses = loses;
}

void User::setMoney(int money)
{
	UI->money = money;
}

void User::setAchievementManager(string achievements)
{
	//AM = new AchievementManager(achievements);
}

//================GETTERS=================//
string User::getUserName()
{
	return UI->userName;
}
string User::getPassword()
{
	return UI->password;
}
int User::getWins()
{
	return UI->wins;
}
int User::getLoses()
{
	return UI->loses;
}
int User::getMoney()
{
	return UI->money;
}
string User::getAchievementManager()
{
	return AM->toString();
}

//==============Update and Check Achievement Methods ================//
void User::updateWins(int x)
{
	UI->wins = getWins() + x;
	AM->checkWinsAchievements(getWins());
}


void User::updateMoney(int x)
{
	UI->wins = x;
	AM->checkMoneyAchievements(getWins());
}

void User::updateBJC()
{
	BlackJackCount++;
	AM->checkCBJA(BlackJackCount);
}

void User::zeroBJC()
{
	BlackJackCount = 0;

}