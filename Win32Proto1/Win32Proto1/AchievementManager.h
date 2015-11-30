#pragma once
#include <string>
#include <array>
using namespace std;
class AchievementManager
{
private:
	const int size = 10;
	string *achievements;
	int *achieved;
	void loadAchievements(string);

public:
	AchievementManager();
	AchievementManager(string);
	~AchievementManager();
	string toString();
	string checkMoneyAchievements(int);
	string checkCBJA(int);					//consecutive black jack achievements
	string checkWinsAchievements(int);

};

