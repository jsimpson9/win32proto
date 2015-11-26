#include <windows.h>
#include <tchar.h>

#include "Table.h"
#include "GameEngine.h"
#include "Hand.h"
#include "User.h"
#include "Utils.h"

#define BUTTON_HIT_ID					3001
#define BUTTON_STAND_ID					3002
#define BUTTON_BET_ID					3003
#define BUTTON_DEAL_ID					3004
#define BUTTON_BANK_ID					3005
#define BUTTON_PROFILE_ID				3006
#define BUTTON_LOGOUT_ID				3007


LRESULT CALLBACK BankButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ProfileButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LogoutButtonProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK DealButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HitButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK StandButtonProc(HWND, UINT, WPARAM, LPARAM);

WNDPROC oldBankButtonProc;
WNDPROC oldProfileButtonProc;
WNDPROC oldLogoutButtonProc;

WNDPROC oldDealButtonProc;
WNDPROC oldHitButtonProc;
WNDPROC oldStandButtonProc;

static HWND hTextboxBetAmount	= NULL;
static HWND hStaticBetAmount	= NULL;

static HWND hStaticTableUsername		= NULL;
static HWND hStaticTableUserBalance		= NULL;

static HWND hStaticTableDealerMessage = NULL;
static HWND hStaticTablePlayerMessage = NULL;
static HWND hStaticTableMiddleMessage = NULL;


static HWND hBankButton;
static HWND hProfileButton;
static HWND hLogoutButton;
static HWND hDealButton;
static HWND hHitButton;
static HWND hStandButton;

static constexpr int TABLE_STATE_READY		= 0;
static constexpr int TABLE_STATE_PLAYING	= 1;
static constexpr int TABLE_STATE_STANDING	= 2;
static constexpr int TABLE_STATE_DEALER		= 3;
static constexpr int TABLE_STATE_FINISHED	= 4;


Table::Table() {

	_dealerHand = new Hand(new std::vector<Card*>());
	_playerHand = new Hand(new std::vector<Card*>());
	
	_tableState = TABLE_STATE_READY;
}

void Table::setState(int state) { _tableState = state; }

int Table::getState() { return _tableState; }

void Table::Create(HWND hWnd, HINSTANCE hInst) { 

	//
	// Static text dealer message area.
	//
	hStaticTableDealerMessage = CreateWindow(L"static", L"", WS_CHILD,
		10, 10,
		260, 20,
		hWnd, NULL, NULL, NULL);

	//
	// Static text middle message area.
	//
	hStaticTableMiddleMessage = CreateWindow(L"static", L"", WS_CHILD,
		10, 270,
		260, 20,
		hWnd, NULL, NULL, NULL);

	//
	// Static text player message area.
	//
	hStaticTablePlayerMessage = CreateWindow(L"static", L"", WS_CHILD,
		10, 300,
		260, 20,
		hWnd, NULL, NULL, NULL);

	//
	// Static text Username
	//
	hStaticTableUsername = CreateWindow(L"static", L"User: ", WS_CHILD,
		400, 40, 
		160, 20,
		hWnd, NULL, NULL, NULL);

	//
	// Static text user balance
	//
	hStaticTableUserBalance = CreateWindow(L"static", L"Balance: ", WS_CHILD,
		400, 70,
		160, 20,
		hWnd, NULL, NULL, NULL);

	//
	// Bank button and bank callback func
	//
	hBankButton = CreateWindow(L"button", L"Bank",
		WS_CHILD | BS_DEFPUSHBUTTON,
		500, 100,
		60, 20,
		hWnd, (HMENU)BUTTON_BANK_ID,
		hInst, NULL);

	oldBankButtonProc = (WNDPROC)SetWindowLongPtr(
		hBankButton,
		GWLP_WNDPROC,
		(LONG_PTR)BankButtonProc);

	//
	// View profile button and callback function
	//
	hProfileButton = CreateWindow(L"button", L"Profile",
		WS_CHILD | BS_DEFPUSHBUTTON,
		500, 130,
		60, 20,
		hWnd, (HMENU)BUTTON_PROFILE_ID,
		hInst, NULL);

	oldProfileButtonProc = (WNDPROC)SetWindowLongPtr(
		hProfileButton,
		GWLP_WNDPROC,
		(LONG_PTR)ProfileButtonProc);

	//
	// Logout button
	//
	hLogoutButton = CreateWindow(L"button", L"Logout",
		WS_CHILD | BS_DEFPUSHBUTTON,
		500, 160,
		60, 20,
		hWnd, (HMENU)BUTTON_LOGOUT_ID,
		hInst, NULL);

	oldLogoutButtonProc = (WNDPROC)SetWindowLongPtr(
		hLogoutButton,
		GWLP_WNDPROC,
		(LONG_PTR)LogoutButtonProc);

	//
	// Static text "Bet:"
	//
	hStaticBetAmount = CreateWindow(L"static", L"Bet:", WS_CHILD,
		455, 340, 40, 28,
		hWnd, NULL, NULL, NULL);

	//
	// Textbox for bet amount
	//
	hTextboxBetAmount = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_BORDER,
		500, 340, 60, 30,
		hWnd, NULL, NULL, NULL);

	//
	// Set default bet value
	//
	SetWindowText(hTextboxBetAmount, L"10");

	hDealButton = CreateWindow(L"button", L"Deal",
		WS_CHILD | BS_DEFPUSHBUTTON,
		500, 370,
		60, 20,
		hWnd, (HMENU)BUTTON_HIT_ID,
		hInst, NULL);

	oldDealButtonProc = (WNDPROC)SetWindowLongPtr(
		hDealButton,
		GWLP_WNDPROC,
		(LONG_PTR)DealButtonProc);


	hHitButton = CreateWindow(L"button", L"Hit",
		WS_CHILD | BS_DEFPUSHBUTTON,
		500, 400,
		60, 20,
		hWnd, (HMENU)BUTTON_HIT_ID,
		hInst, NULL);

	oldHitButtonProc = (WNDPROC)SetWindowLongPtr(
		hHitButton,
		GWLP_WNDPROC,
		(LONG_PTR)HitButtonProc);

	hStandButton = CreateWindow(L"button", L"Stand",
		WS_CHILD | BS_DEFPUSHBUTTON,
		500, 430,
		60, 20,
		hWnd, (HMENU)BUTTON_STAND_ID,
		hInst, NULL);

	oldStandButtonProc = (WNDPROC)SetWindowLongPtr(
		hStandButton,
		GWLP_WNDPROC,
		(LONG_PTR)StandButtonProc);

}

void Table::Paint(HDC hdc) {

	GameEngine* gameEngine = GameEngine::getInstance();


	//
	// Used for the various string conversion calls ugh
	//
	size_t convertedChars = 0;

	if (_dealerHand != NULL) {
		_dealerHand->Paint(hdc, 10, 40);

		updateHandMessage(hStaticTableDealerMessage,
							"Dealer",
							_dealerHand);
	}

	if (_playerHand != NULL) {
		_playerHand->Paint(hdc, 10, 330);

		updateHandMessage(hStaticTablePlayerMessage,
							"Player",
							_playerHand);
	}

	/*
	if(_tableState == TABLE_STATE_FINISHED) {
		updateTextare(hStaticTableDealerMessage,
			"Dealer",
			_dealerHand);
	}
	*/

	User* user = gameEngine->getUser();

	std::string sUsername = user->getUsername();

	// std::wstring wUsername = std::wstring(sUsername.begin(), sUsername.end());
	// LPCWSTR lpcwUsername = wUsername.c_str();

	//
	// 20 lines of code just to format some text.
	// Thanks C++ !!!
	//


	char usernameText[30];
	snprintf(usernameText, 30, "User: %s", sUsername.c_str());
	wchar_t usernameWtext[30];
	mbstowcs_s(
				&convertedChars, usernameWtext, 
				(size_t)30, usernameText, 
				strlen(usernameText) + 1);

	char userBalText[30];
	snprintf(userBalText, 30, "Balance: $%d", user->getBalance());
	wchar_t userBalWtext[30];
	mbstowcs_s(
				&convertedChars, userBalWtext, 
				(size_t)30, userBalText, 
				strlen(userBalText) + 1);

	//
	// Set table username and user balance
	//
	SetWindowText(hStaticTableUsername, usernameWtext);
	SetWindowText(hStaticTableUserBalance, userBalWtext);

	ShowWindow(hStaticTableUsername, SW_SHOW);
	ShowWindow(hStaticTableUserBalance, SW_SHOW);

	ShowWindow(hBankButton, SW_SHOW);
	ShowWindow(hProfileButton, SW_SHOW);
	ShowWindow(hLogoutButton, SW_SHOW);

	ShowWindow(hStaticBetAmount, SW_SHOW);
	ShowWindow(hTextboxBetAmount, SW_SHOW);

	ShowWindow(hDealButton, SW_SHOW);
	ShowWindow(hHitButton, SW_SHOW);
	ShowWindow(hStandButton, SW_SHOW);

	//
	// Enable / disable buttons based on table state.
	//
	// If we are in "ready" state where no game has been played,
	// or we are in a "finished" state, enable messages and buttons
	// accordingly.
	//
	if (_tableState == TABLE_STATE_READY ||
		_tableState == TABLE_STATE_FINISHED) {

		if (_tableState == TABLE_STATE_FINISHED) {
			ShowWindow(hStaticTableDealerMessage, SW_SHOW);
			ShowWindow(hStaticTablePlayerMessage, SW_SHOW);
			ShowWindow(hStaticTableMiddleMessage, SW_SHOW);
		} else {
			//
			// Inital state. No messages.
			//
			ShowWindow(hStaticTableDealerMessage, SW_HIDE);
			ShowWindow(hStaticTablePlayerMessage, SW_HIDE);
			ShowWindow(hStaticTableMiddleMessage, SW_HIDE);
		}

		EnableWindow(hBankButton, true);
		EnableWindow(hProfileButton, true);
		EnableWindow(hLogoutButton, true);

		EnableWindow(hDealButton, true);
		EnableWindow(hTextboxBetAmount, true);

		EnableWindow(hHitButton, false);
		EnableWindow(hStandButton, false);

	}
	else if (_tableState == TABLE_STATE_PLAYING) {

		ShowWindow(hStaticTableDealerMessage, SW_SHOW);
		ShowWindow(hStaticTablePlayerMessage, SW_SHOW);
		ShowWindow(hStaticTableMiddleMessage, SW_HIDE);

		EnableWindow(hBankButton, false);
		EnableWindow(hProfileButton, false);
		EnableWindow(hLogoutButton, false);

		EnableWindow(hDealButton, false);
		EnableWindow(hTextboxBetAmount, false);

		EnableWindow(hHitButton, true);
		EnableWindow(hStandButton, true);
	}
}

void Table::Hide() { 

	ShowWindow(hStaticTableDealerMessage, SW_HIDE);
	ShowWindow(hStaticTablePlayerMessage, SW_HIDE);
	ShowWindow(hStaticTableMiddleMessage, SW_HIDE);

	ShowWindow(hStaticTableUsername, SW_HIDE);
	ShowWindow(hStaticTableUserBalance, SW_HIDE);

	ShowWindow(hBankButton, SW_HIDE);
	ShowWindow(hProfileButton, SW_HIDE);
	ShowWindow(hLogoutButton, SW_HIDE);

	ShowWindow(hStaticBetAmount, SW_HIDE);
	ShowWindow(hTextboxBetAmount, SW_HIDE);

	ShowWindow(hDealButton, SW_HIDE);
	ShowWindow(hHitButton, SW_HIDE);
	ShowWindow(hStandButton, SW_HIDE);

}



/**
 *
 * Update the text area above the rendered Hand of Cards
 * to reflect the overall value of the hand. 
 *
 */
void Table::updateHandMessage(
								HWND textarea,
								char* name,
								Hand* hand) {

	size_t convertedChars = 0;

	if (hand == NULL) { return; }

	std::vector<int>* vals = hand->GetValues();

	int val1 = vals->at(0);
	int val2 = 0;

	if (vals->size() > 1) {
		val2 = vals->at(1);
	}

	char messageText[50];
	if (val2 == 0) {
		snprintf(messageText, 50, "%s %d",
			name,
			val1);
	}
	else {
		snprintf(messageText, 50, "%s %d (or %d)",
			name,
			val2,
			val1);
	}
	wchar_t messageWtext[30];
	mbstowcs_s(
		&convertedChars, messageWtext,
		(size_t)30, messageText,
		strlen(messageText) + 1);

	SetWindowText(textarea, messageWtext);

}


Hand* Table::getDealerHand() { return _dealerHand; }

Hand* Table::getPlayerHand() { return _playerHand; }

void Table::setDealerHand(Hand* hand) { _dealerHand = hand; }

void Table::setPlayerHand(Hand* hand) { _playerHand = hand; }

LRESULT CALLBACK DealButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{

	if (msg == WM_LBUTTONDOWN) {

		TCHAR buff[64];
		GetWindowText(hTextboxBetAmount, buff, 20);

		int bet = _ttoi(buff);

		/*
		for (int i = 0; buff[i] != NULL; i++) {
			if (! std::isdigit(buff[i]) ) {
				MessageBox(
					GameEngine::getInstance()->getHWnd(),
					L"Invalid bet amount.",
					L"Error",
					NULL);

				return 0;
			}
		}
		*/

		// int bet = atoi(buff);

		Table* table = GameEngine::getInstance()->getTable();
		User* user = GameEngine::getInstance()->getUser();

		// Can player bet this much?
		if (bet > user->getBalance()) {
			MessageBox(
				GameEngine::getInstance()->getHWnd(),
				L"Insufficient funds available to place this bet.",
				L"Error",
				NULL);
			return 0;
		}

		if (bet == 0) {
			MessageBox(
				GameEngine::getInstance()->getHWnd(),
				L"Must bet more than $0.",
				L"Error",
				NULL);
			return 0;
		}

		Hand* dealerHand = new Hand();
		Hand* playerHand = new Hand();

		playerHand->setBetAmount(bet);
		user->setBalance(user->getBalance() - bet);

		dealerHand->dealCard(true);
		dealerHand->dealCard(false);

		playerHand->dealCard(false);
		playerHand->dealCard(false);

		table->setDealerHand(dealerHand);
		table->setPlayerHand(playerHand);

		GameEngine::getInstance()->setState(GameEngine::STATE_PLAYING);

		PlaySound(L"sound-chips.wav", NULL, SND_FILENAME | SND_ASYNC);

		//
		// Check if we have blackjack, if so player
		// wins right away. Otherwise move to substate 
		// "playing"
		//
		if (playerHand->isBlackjack()) {
			table->setState(TABLE_STATE_FINISHED);
			updateTextarea(hStaticTableMiddleMessage, "Blackjack! Player Wins.");
			
			// Play YAY sound
			PlaySound(L"sound-yay.wav", NULL, SND_FILENAME | SND_ASYNC);

			// Update user balance.
			user->setBalance(user->getBalance() + (bet*2));

		} else {
			table->setState(TABLE_STATE_PLAYING);
		}	

		//
		// Force redraw of window, which should now render the new
		// card data. 
		//
		// https://msdn.microsoft.com/en-us/library/dd162911%28VS.85%29.aspx
		// http://stackoverflow.com/questions/2325894/difference-between-invalidaterect-and-redrawwindow
		//
		RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);


		return 0;

	}

	return CallWindowProc(oldDealButtonProc, hwnd, msg, wp, lp);
}


LRESULT CALLBACK HitButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (msg == WM_LBUTTONDOWN) {

		PlaySound(L"sound-flipcard.wav", NULL, SND_FILENAME | SND_ASYNC);

		GameEngine* gameEngine = GameEngine::getInstance();
		Table* table = gameEngine->getTable();
		Hand* playerHand = table->getPlayerHand();
		playerHand->dealCard(false);

		// Check for bust. 
		if (playerHand->isBusted()) {
			table->setState(TABLE_STATE_FINISHED);
			updateTextarea(hStaticTableMiddleMessage, "Busted. Dealer Wins.");

		}

		RedrawWindow(gameEngine->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);

	}

	return CallWindowProc(oldHitButtonProc, hwnd, msg, wp, lp);
}

LRESULT CALLBACK StandButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (msg == WM_LBUTTONDOWN) {

		GameEngine* gameEngine = GameEngine::getInstance();
		
		User* user = gameEngine->getUser();
		Table* table = gameEngine->getTable();

		table->setState(TABLE_STATE_STANDING);
		Hand* dealerHand = table->getDealerHand();
		Hand* playerHand = table->getPlayerHand();

		//
		// Flip over the first card. 
		//
		dealerHand->GetCards()->at(0)->setFacedown(false);
		PlaySound(L"sound-flipcard.wav", NULL, SND_FILENAME | SND_ASYNC);

		RedrawWindow(gameEngine->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);

		Sleep(500);

		//
		// See if we need additional cards.
		//
		while (true) {
			std::vector<int>* vals = dealerHand->GetValues();

			bool done = false;

			for (int i = 0; i < vals->size(); i++) {
				// Dealer must stop taking cards
				// if he has a value of 17 or higher.
				if (vals->at(i) >= 17) {
					done = true;
					break;
				}
			}

			if (done) {
				break;
			}

			PlaySound(L"sound-flipcard.wav", NULL, SND_FILENAME | SND_ASYNC);

			dealerHand->dealCard(false);

			RedrawWindow(gameEngine->getHWnd(), NULL, NULL,
				RDW_INVALIDATE | RDW_UPDATENOW);
			
			Sleep(500);
		}

		//
		// Determine winner. Update balance amounts.
		//

		// table->setState(TABLE_STATE_READY);

		std::vector<int>* dealerValues = dealerHand->GetValues();
		std::vector<int>* playerValues = playerHand->GetValues();
		int dealerFinal = 0;
		int playerFinal = 0;

		for (int i = 0; i < dealerValues->size(); i++) {
			if (dealerValues->at(i) > dealerFinal &&
				dealerValues->at(i) < 22) {
				dealerFinal = dealerValues->at(i);
			}
		}

		for (int i = 0; i < playerValues->size(); i++) {
			if (playerValues->at(i) > playerFinal &&
				playerValues->at(i) < 22) {
				playerFinal = playerValues->at(i);
			}
		}

		table->setState(TABLE_STATE_FINISHED);

		// If values are same, this is a push. 
		if (dealerFinal == playerFinal) {

			updateTextarea(hStaticTableMiddleMessage, "Push");

			// Return player's bet money.
			int bet = playerHand->getBetAmount();

			user->setBalance(user->getBalance() + bet);

		} else if (dealerFinal < playerFinal) {

			// Player wins, return bet and winning.

			updateTextarea(hStaticTableMiddleMessage, "Player Wins!");

			int bet = playerHand->getBetAmount();

			user->setBalance(user->getBalance() + (bet*2) );

		}
		else if (dealerFinal > playerFinal) {

			// No need to update cash. Has already been deducted
			// at time of bet. Update the middle message area.
			updateTextarea(hStaticTableMiddleMessage, "Dealer Wins.");

		}

		RedrawWindow(gameEngine->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);

	}

	return CallWindowProc(oldStandButtonProc, hwnd, msg, wp, lp);
}

LRESULT CALLBACK BankButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (msg == WM_LBUTTONDOWN) {

		GameEngine::getInstance()->setState(GameEngine::STATE_BANKING);

		RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);

	}

	return CallWindowProc(oldBankButtonProc, hwnd, msg, wp, lp);
}

LRESULT CALLBACK ProfileButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (msg == WM_LBUTTONDOWN) {

		//
		// For DEMO purpose, disable this button.
		// There is no view here available at this time. 
		//
		// GameEngine::getInstance()->setState(GameEngine::STATE_VIEW_PROFILE);

		// RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
		//	RDW_INVALIDATE | RDW_UPDATENOW);

	}

	return CallWindowProc(oldProfileButtonProc, hwnd, msg, wp, lp);
}


LRESULT CALLBACK LogoutButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (msg == WM_LBUTTONDOWN) {

		GameEngine* gameEngine = GameEngine::getInstance();

		//
		// TODO save user with PersistenceManager
		//

		gameEngine->setUser(NULL);

		//
		// Set game state back to initial. 
		//
		gameEngine->setState(GameEngine::STATE_INITIAL);

		//
		// Reset table state
		//
		Table* table = GameEngine::getInstance()->getTable();
		table->setState(TABLE_STATE_READY);
		delete table->getDealerHand();
		delete table->getPlayerHand();
		table->setDealerHand(NULL);
		table->setPlayerHand(NULL);

		RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);

	}

	return CallWindowProc(oldLogoutButtonProc, hwnd, msg, wp, lp);
}