#include "BankingView.h"
#include "GameEngine.h"
#include "Utils.h"

#define BUTTON_TRANSFER_ID				6001
#define BUTTON_CANCEL_BANKING_ID		6002

//
// Buttons
//
static HWND hTransferButton = NULL;
static HWND hCancelBankingButton = NULL;

//
// Button event handler callbacks
//
LRESULT CALLBACK TransferButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CancelBankingButtonProc(HWND, UINT, WPARAM, LPARAM);

WNDPROC oldTransferButtonProc;
WNDPROC oldCancelBankingButtonProc;

//
// Form widgets for creating user profile.
//
static HWND hTextboxAmount = NULL;
static HWND hTextboxToUser = NULL;

static HWND hStaticBalance = NULL;

static HWND hStaticAmount = NULL;
static HWND hStaticToUser = NULL;

void BankingView::Create(HWND hWnd, HINSTANCE hInst) {

	//
	// Create labels
	//

	//
	// TODO get current balance from User object
	//
	hStaticBalance = CreateWindow(L"static", L"Current Balance: ", WS_CHILD,
		50, 40, 300, 30,
		hWnd, NULL, NULL, NULL);

	hStaticAmount = CreateWindow(L"static", L"Transfer Amount:", WS_CHILD,
		50, 140, 200, 30,
		hWnd, NULL, NULL, NULL);
	hStaticToUser = CreateWindow(L"static", L"To User:", WS_CHILD | ES_PASSWORD,
		50, 180, 200, 30,
		hWnd, NULL, NULL, NULL);

	//
	// Create text input widgets
	//

	hTextboxAmount = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_BORDER,
		260, 140, 140, 30,
		hWnd, NULL, NULL, NULL);
	hTextboxToUser = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_BORDER,
		260, 180, 140, 30,
		hWnd, NULL, NULL, NULL);

	//
	// Create buttons...
	//

	hTransferButton = CreateWindow(L"button", L"Transfer",
		WS_CHILD | BS_DEFPUSHBUTTON,
		405, 185,
		70, 20,
		hWnd, (HMENU)BUTTON_TRANSFER_ID,
		hInst, NULL);

	oldTransferButtonProc = (WNDPROC)SetWindowLongPtr(
		hTransferButton,
		GWLP_WNDPROC,
		(LONG_PTR)TransferButtonProc);

	hCancelBankingButton = CreateWindow(L"button", L"Cancel",
		WS_CHILD | BS_DEFPUSHBUTTON,
		500, 530,
		70, 20,
		hWnd, (HMENU)BUTTON_CANCEL_BANKING_ID,
		hInst, NULL);

	oldCancelBankingButtonProc = (WNDPROC)SetWindowLongPtr(
		hCancelBankingButton,
		GWLP_WNDPROC,
		(LONG_PTR)CancelBankingButtonProc);

}


void BankingView::Paint(HDC hdc) {

	if (!_isHidden) {
		return;
	}

	User* user = GameEngine::getInstance()->getUser();

	char buff[50];
	snprintf(buff, 50, "Current Balance: $%d", user->getBalance());
	updateTextarea(hStaticBalance, buff);


	//
	// We already have created widgets. Display them.
	//

	ShowWindow(hStaticBalance, SW_SHOW);

	ShowWindow(hStaticAmount, SW_SHOW);
	ShowWindow(hStaticToUser, SW_SHOW);

	ShowWindow(hTextboxAmount, SW_SHOW);
	ShowWindow(hTextboxToUser, SW_SHOW);

	ShowWindow(hTransferButton, SW_SHOW);
	ShowWindow(hCancelBankingButton, SW_SHOW);

	_isHidden = false;
}

//
// Clear and hide all widgets.
//
void BankingView::Hide() {

	if (_isHidden) {
		return;
	}

	//
	// Hide labels 
	//

	ShowWindow(hStaticBalance, SW_HIDE);

	ShowWindow(hStaticAmount, SW_HIDE);
	ShowWindow(hStaticToUser, SW_HIDE);

	//
	// Clear values and hide text input widgets
	//

	SetWindowText(hTextboxAmount, L"");
	ShowWindow(hTextboxAmount, SW_HIDE);

	SetWindowText(hTextboxToUser, L"");
	ShowWindow(hTextboxToUser, SW_HIDE);


	//
	// Transfer and Cancel buttons
	//

	ShowWindow(hTransferButton, SW_HIDE);
	ShowWindow(hCancelBankingButton, SW_HIDE);

	_isHidden = true;

}


LRESULT CALLBACK TransferButtonProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	if (msg == WM_LBUTTONDOWN) {

		//
		// TODO actually transfer amount here. 
		//

		// GameEngine::getInstance()->setState(GameEngine::STATE_INITIAL);

		RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);


		return 0;
	}

	return CallWindowProc(oldTransferButtonProc, hWnd, msg, wp, lp);
}


LRESULT CALLBACK CancelBankingButtonProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	if (msg == WM_LBUTTONDOWN) {

		GameEngine::getInstance()->setState(GameEngine::STATE_PLAYING);

		RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);

		return 0;
	}

	return CallWindowProc(oldCancelBankingButtonProc, hWnd, msg, wp, lp);
}

