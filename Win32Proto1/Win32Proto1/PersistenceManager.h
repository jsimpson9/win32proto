#pragma once
#include <string>
using namespace std;
class PersistenceManager
{
private:
	int numUsers;
	string fileName;
public:
	PersistenceManager();
	~PersistenceManager();
	void saveUser(string);
	void updateUser(string, string);
	int loadUser(string, string);
	string* tokenize(string info);

};

