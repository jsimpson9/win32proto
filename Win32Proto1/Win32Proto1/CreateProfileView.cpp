#include "CreateProfileView.h"
#include "GameEngine.h"

#define BUTTON_SAVE_PROFILE_ID			2001
#define BUTTON_CANCEL_PROFILE_ID		2002

//
// Buttons
//
static HWND hSaveProfileButton		= NULL;
static HWND hCancelProfileButton	= NULL;

//
// Button event handler callbacks
//
LRESULT CALLBACK SaveProfileButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CancelProfileButtonProc(HWND, UINT, WPARAM, LPARAM);

WNDPROC oldSaveProfileButtonProc;
WNDPROC oldCancelProfileButtonProc;

//
// Form widgets for creating user profile.
//
static HWND hTextboxUsername			= NULL;
static HWND hTextboxPassword			= NULL;
static HWND hTextboxConfirmPassword		= NULL;

static HWND hStaticUsername				= NULL;
static HWND hStaticPassword				= NULL;
static HWND hStaticConfirmPassword		= NULL;


void CreateProfileView::Create(HWND hWnd, HINSTANCE hInst) {

	//
	// Create labels
	//

	hStaticUsername = CreateWindow(L"static", L"Username:", WS_CHILD,
		50, 40, 200, 30,
		hWnd, NULL, NULL, NULL);
	hStaticPassword = CreateWindow(L"static", L"Password:", WS_CHILD | ES_PASSWORD,
		50, 80, 200, 30,
		hWnd, NULL, NULL, NULL);
	hStaticConfirmPassword = CreateWindow(L"static", L"Confirm password:", WS_CHILD | ES_PASSWORD,
		50, 120, 200, 30,
		hWnd, NULL, NULL, NULL);

	//
	// Create text input widgets
	//

	hTextboxUsername = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_BORDER,
		260, 40, 140, 30,
		hWnd, NULL, NULL, NULL);
	hTextboxPassword = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_BORDER | ES_PASSWORD,
		260, 80, 140, 30,
		hWnd, NULL, NULL, NULL);
	hTextboxConfirmPassword = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_BORDER | ES_PASSWORD,
		260, 120, 140, 30,
		hWnd, NULL, NULL, NULL);

	//
	// Create buttons...
	//

	hSaveProfileButton = CreateWindow(L"button", L"Save",
		WS_CHILD | BS_DEFPUSHBUTTON,
		500, 500,
		70, 20,
		hWnd, (HMENU)BUTTON_SAVE_PROFILE_ID,
		hInst, NULL);

	oldSaveProfileButtonProc = (WNDPROC)SetWindowLongPtr(
		hSaveProfileButton,
		GWLP_WNDPROC,
		(LONG_PTR)SaveProfileButtonProc);

	hCancelProfileButton = CreateWindow(L"button", L"Cancel",
		WS_CHILD | BS_DEFPUSHBUTTON,
		500, 530,
		70, 20,
		hWnd, (HMENU)BUTTON_CANCEL_PROFILE_ID,
		hInst, NULL);

	oldCancelProfileButtonProc = (WNDPROC)SetWindowLongPtr(
		hCancelProfileButton,
		GWLP_WNDPROC,
		(LONG_PTR)CancelProfileButtonProc);

}


void CreateProfileView::Paint(HDC hdc) {

	if (!_isHidden) {
		return;
	}


	//
	// We already have created widgets. Display them.
	//

	ShowWindow(hStaticUsername, SW_SHOW);
	ShowWindow(hStaticPassword, SW_SHOW);
	ShowWindow(hStaticConfirmPassword, SW_SHOW);

	ShowWindow(hTextboxUsername,SW_SHOW);
	ShowWindow(hTextboxPassword, SW_SHOW);
	ShowWindow(hTextboxConfirmPassword, SW_SHOW);

	ShowWindow(hSaveProfileButton, SW_SHOW);
	ShowWindow(hCancelProfileButton, SW_SHOW);

	_isHidden = false;
}

//
// Clear and hide all widgets.
//
void CreateProfileView::Hide() {

	if (_isHidden) {
		return;
	}

	//
	// Hide labels 
	//

	ShowWindow(hStaticUsername, SW_HIDE);
	ShowWindow(hStaticPassword, SW_HIDE);
	ShowWindow(hStaticConfirmPassword, SW_HIDE);

	//
	// Clear values and hide text input widgets
	//

	SetWindowText(hTextboxUsername, L"");
	ShowWindow(hTextboxUsername, SW_HIDE);
	
	SetWindowText(hTextboxPassword, L"");
	ShowWindow(hTextboxPassword, SW_HIDE);
	
	SetWindowText(hTextboxConfirmPassword, L"");
	ShowWindow(hTextboxConfirmPassword, SW_HIDE);

	//
	// Save and Cancel buttons
	//

	ShowWindow(hSaveProfileButton, SW_HIDE);
	ShowWindow(hCancelProfileButton, SW_HIDE);
	
	_isHidden = true;

}


LRESULT CALLBACK SaveProfileButtonProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	if (msg == WM_LBUTTONDOWN) {

		//
		// TODO actually save game data here. 
		//

		GameEngine::getInstance()->setState(GameEngine::STATE_INITIAL);

		RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);
		

		return 0;
	}

	return CallWindowProc(oldSaveProfileButtonProc, hWnd, msg, wp, lp);
}


LRESULT CALLBACK CancelProfileButtonProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	if (msg == WM_LBUTTONDOWN) {

		GameEngine::getInstance()->setState(GameEngine::STATE_INITIAL);

		RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);
	
		return 0;
	}

	return CallWindowProc(oldCancelProfileButtonProc, hWnd, msg, wp, lp);
}

