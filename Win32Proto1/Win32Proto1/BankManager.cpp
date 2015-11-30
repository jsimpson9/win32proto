#include "BankManager.h"

#include <string>
using namespace std;

BankManager::BankManager()
{
	PM = new PersistenceManager();
	U = new User();
}


BankManager::~BankManager()
{
}

void BankManager::transferMoney(string fromUser, string toUser, int amount)
{

	int temp;

	//The User that is Transfering Money
	PM->loadUser(fromUser, fromUser);	//loophole in method.
	temp = U->getMoney();
	temp -= amount;
	U->updateMoney(temp);
	PM->updateUser(fromUser, U->toString());

	//The User that is getting Money
	PM->loadUser(toUser, toUser);
	temp = U->getMoney();
	temp += amount;
	U->updateMoney(temp);
	PM->updateUser(toUser, U->toString());

}
