#include "AchievementManager.h"
#include <string>
#include <cstring>

using namespace std;

AchievementManager::AchievementManager()
{
	achievements = new string[size];
	achievements[0] = "0) Achieved $1,000";
	achievements[1] = "1) Achieved $5,000";
	achievements[2] = "2) Achieved $10,000";
	achievements[3] = "3) Achieved $25,000";
	achievements[4] = "4) Achieved $50,000";
	achievements[5] = "5) Achieved $100,000";
	achievements[6] = "6) 2 Black Jacks in a Row";
	achievements[7] = "7) 3 Black Jacks in a Row";
	achievements[8] = "8) Total of 10 Wins";
	achievements[9] = "9) Total of 20 Wins";


	achieved = new int[sizeof(achievements)];
	//sets everything to zero.
	//0 represents not achieved
	//1 represents  achieved
	//parallel arrays corresponding with one another. 
	//string Achievements[] and int achieved[]
	for (int i = 0; i < sizeof(achievements); i++)
	{
		achieved[i] = 0;
	}


}

AchievementManager::AchievementManager(string achievements)
{
	loadAchievements(achievements);
}

AchievementManager::~AchievementManager()
{
	delete achieved;
}

void AchievementManager::loadAchievements(string achievements)
{
	char * cstr = new char[achievements.length() + 1];
	strcpy_s(cstr, sizeof(cstr), achievements.c_str());

	//STEP 1 PARSED

	char * p = strtok_s(cstr, ",", NULL);
	while (p != 0)
	{
		p = strtok_s(NULL, ",", NULL);
	}

	//STEP 2 SET ACHIEVEMENTS
	char buffer[33];
	for (int i = 0; i < sizeof(achievements); i++)
	{
		_itoa_s(i, buffer, 10);
		if (strstr(p, buffer))
		{
			achieved[i] = 1;
		}
	}
}


string AchievementManager::toString()
{
	string temp = "(";
	char buffer[33];
	for (int i = 0; i < sizeof(achieved); i++)
	{
		if (achieved[i] == 1)
		{
			_itoa_s(i, buffer, 10);
			temp += buffer;
		}
	}
	temp += ")";
	return temp;
}

string AchievementManager::checkMoneyAchievements(int x)
{
	const int check[] = { 1000,			//achieved[0]
		5000,			//achieved[1]
		10000,			//achieved[2]
		25000,			//achieved[3]
		50000,			//achieved[4]
		100000 };		//achieved[5]


	for (int i = 0; i < sizeof(check); i++)
	{
		if (check[i] < x && x < check[i + 1])
		{
			//checks if not set
			if (achieved[i] == 0)
			{
				achieved[i] = 1;
				return achievements[i];
			}
		}
	}
	return "NO NEW ACHIEVEMENTS";
}

string AchievementManager::checkCBJA(int x)
{
	switch (x)
	{
	case 2:
		if (achieved[6] == 0)
		{
			achieved[6] = 1;
			return achievements[6];
		}
		break;
	case 3:
		if (achieved[7] == 0)
		{
			achieved[7] = 1;
			return achievements[7];
		}
		break;
	default:
		break;
	}
	return "NO NEW ACHIEVEMENTS";
}

string AchievementManager::checkWinsAchievements(int x)
{
	switch (x)
	{
	case 10:
		if (achieved[8] == 0)
		{
			achieved[8] = 1;
			return achievements[8];
		}
		break;
	case 20:
		if (achieved[9] == 0)
		{
			achieved[9] = 1;
			return achievements[9];
		}
		break;
	default:
		break;
	}
	return "NO NEW ACHIEVEMENTS";
}