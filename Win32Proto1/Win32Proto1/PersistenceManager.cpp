#include "PersistenceManager.h"
#include "User.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


PersistenceManager::PersistenceManager()
{
	numUsers = 10;
	fileName = "Database.txt";
}


PersistenceManager::~PersistenceManager()
{

}

void PersistenceManager::saveUser(string UserInfo)
{
	ofstream myfile;
	//Opens file if doesn't exists creates file. 
	//Appends file
	myfile.open(fileName, ios::out | ios::app);

	//check if file open
	if (!myfile)
	{
		cout << "Could not open file";
		return;
	}

	myfile << UserInfo;
	myfile.close();
}

void PersistenceManager::updateUser(string username, string UserInfo)
{
	string line;
	vector<string> info(numUsers);
	ifstream readFile;
	ofstream writeFile;

	
	//STEP 1 Read line by line and place it into vector but when username matches the one to update,
	//the line is replaced with new update.
	
	//open file to read
	readFile.open(fileName, ios::in);
	//checks if file opened
	if (!readFile)
	{
		cout << "Couldn't open file!";
		return;
	}

	//places info of usernames into vector put changes the user info that we want to update.
	for (int i = 0; !readFile.eof(); i++)
	{
		getline(readFile, line);
		//if the line contains the username we want to update then place it into variable.
		if (strstr(line.c_str(), username.c_str()))
		{
			info[i] = UserInfo;	//updates info
		}
		else
			info[i] = line;		//line remains the same
	}

	readFile.close();


	
	//STEP 2 Loops through vector and overwrites existing file with the update.
	
	//open file
	writeFile.open(fileName, ios::out);
	//checks if file opened
	if (!writeFile)
	{
		cout << "Couldn't open file!";
		return;
	}

	//overwrites file with the update.
	for (int i = 0; i < numUsers; i++)
		writeFile << info[i];

	//close file
	writeFile.close();

}


//Loads info

int PersistenceManager::loadUser(string username, string password)
{
	string line;
	//char info;
	//string temp[6];
	ifstream readFile;

	//open file to read
	readFile.open(fileName, ios::in);
	//checks if file opened
	if (!readFile)
	{
		cout << "Couldn't open file!";
		return -1;
	}

	//places info of usernames into vector put changes the user info that we want to update.
	for (int i = 0; !readFile.eof(); i++)
	{
		getline(readFile, line);
		//if the line contains the username we want to update then place it into variable.
		if (strstr(line.c_str(), username.c_str()))
		{
			//checks password
			if (strstr(line.c_str(), password.c_str()))
			{
				readFile.close();
				User(tokenize(line));
				return 0;
			}
		}

	}
	return -1;
}

string* PersistenceManager::tokenize(string info)
{
	//tokenize
	int i = 0;
	string temp[6];
	stringstream ssin(info);
	while (ssin.good() && i < 6)
	{
		ssin >> temp[i];
		i++;
	}

	return temp;
}

