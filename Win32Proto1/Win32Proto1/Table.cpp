#include <windows.h>
#include "Table.h"
#include "GameEngine.h"
#include "Hand.h"

#define BUTTON_HIT_ID					3001
#define BUTTON_STAND_ID					3002
#define BUTTON_BET_ID					3003
#define BUTTON_DEAL_ID					3004
#define BUTTON_BANK_ID					3005

LRESULT CALLBACK BankButtonProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK DealButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HitButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK StandButtonProc(HWND, UINT, WPARAM, LPARAM);

WNDPROC oldBankButtonProc;
WNDPROC oldDealButtonProc;
WNDPROC oldHitButtonProc;
WNDPROC oldStandButtonProc;

static HWND hTextboxBetAmount = NULL;
static HWND hStaticBetAmount = NULL;

static HWND hBankButton;
static HWND hDealButton;
static HWND hHitButton;
static HWND hStandButton;

static constexpr int TABLE_STATE_READY		= 0;
static constexpr int TABLE_STATE_PLAYING	= 1;
static constexpr int TABLE_STATE_STANDING	= 2;
static constexpr int TABLE_STATE_DEALER		= 3;


Table::Table() {
	_dealerHand = new Hand(new std::vector<Card*>());
	_playerHand = new Hand(new std::vector<Card*>());
	
	_tableState = TABLE_STATE_READY;
}

void Table::setState(int state) { _tableState = state; }

int Table::getState() { return _tableState; }

void Table::Create(HWND hWnd, HINSTANCE hInst) { 


	hBankButton = CreateWindow(L"button", L"Bank",
		WS_CHILD | BS_DEFPUSHBUTTON,
		500, 50,
		60, 20,
		hWnd, (HMENU)BUTTON_BANK_ID,
		hInst, NULL);

	oldBankButtonProc = (WNDPROC)SetWindowLongPtr(
		hBankButton,
		GWLP_WNDPROC,
		(LONG_PTR)BankButtonProc);

	hStaticBetAmount = CreateWindow(L"static", L"Bet:", WS_CHILD,
		455, 340, 40, 28,
		hWnd, NULL, NULL, NULL);

	hTextboxBetAmount = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_BORDER,
		500, 340, 60, 30,
		hWnd, NULL, NULL, NULL);

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

	if (_dealerHand != NULL) {
		_dealerHand->Paint(hdc, 10, 10);
	}
	if (_playerHand != NULL) {
		_playerHand->Paint(hdc, 10, 300);
	}

	ShowWindow(hBankButton, SW_SHOW);

	ShowWindow(hStaticBetAmount, SW_SHOW);
	ShowWindow(hTextboxBetAmount, SW_SHOW);

	ShowWindow(hDealButton, SW_SHOW);
	ShowWindow(hHitButton, SW_SHOW);
	ShowWindow(hStandButton, SW_SHOW);

	//
	// Enable / disable buttons based on table state.
	//
	if (_tableState == TABLE_STATE_READY) {

		EnableWindow(hBankButton, true);
		EnableWindow(hDealButton, true);
		EnableWindow(hTextboxBetAmount, true);

		EnableWindow(hHitButton, false);
		EnableWindow(hStandButton, false);

	}
	else if (_tableState == TABLE_STATE_PLAYING) {
		EnableWindow(hBankButton, false);
		EnableWindow(hDealButton, false);
		EnableWindow(hTextboxBetAmount, false);

		EnableWindow(hHitButton, true);
		EnableWindow(hStandButton, true);
	}
}

void Table::Hide() { 

	ShowWindow(hBankButton, SW_HIDE);

	ShowWindow(hStaticBetAmount, SW_HIDE);
	ShowWindow(hTextboxBetAmount, SW_HIDE);

	ShowWindow(hDealButton, SW_HIDE);
	ShowWindow(hHitButton, SW_HIDE);
	ShowWindow(hStandButton, SW_HIDE);

}

Hand* Table::getDealerHand() { return _dealerHand; }

Hand* Table::getPlayerHand() { return _playerHand; }

void Table::setDealerHand(Hand* hand) { _dealerHand = hand; }

void Table::setPlayerHand(Hand* hand) { _playerHand = hand; }

LRESULT CALLBACK DealButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{

	switch (msg) {

	case WM_LBUTTONDOWN:

		Table* table = GameEngine::getInstance()->getTable();
		//
		// TODO don't allow this if we are already in a game.
		// TODO make this random
		//
		std::vector<Card*>* dealerCards = new std::vector<Card*>();
		std::vector<Card*>* playerCards = new std::vector<Card*>();

		dealerCards->push_back(new Card(Card::ACE, Card::SPADES, true));
		dealerCards->push_back(new Card(Card::JACK, Card::SPADES));

		playerCards->push_back(new Card(Card::TEN, Card::CLUBS));
		playerCards->push_back(new Card(Card::JACK, Card::DIAMONDS));

		Hand* dealerHand = new Hand(dealerCards);
		Hand* playerHand = new Hand(playerCards);

		table->setDealerHand(dealerHand);
		table->setPlayerHand(playerHand);

		GameEngine::getInstance()->setState(GameEngine::STATE_PLAYING);

		PlaySound(L"sound-chips.wav", NULL, SND_FILENAME | SND_ASYNC);

		table->setState(TABLE_STATE_PLAYING);

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

	}

	return CallWindowProc(oldHitButtonProc, hwnd, msg, wp, lp);
}

LRESULT CALLBACK StandButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{

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

