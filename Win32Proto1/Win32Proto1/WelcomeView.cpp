#include <windows.h>
#include "WelcomeView.h"
#include "GameEngine.h"

#define BUTTON_CREATE_PROFILE_ID		1001
#define BUTTON_LOGIN_ID					1002


//
// Callbacks / function prototypes
//
LRESULT CALLBACK CreateProfileButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LoginButtonProc(HWND, UINT, WPARAM, LPARAM);

WNDPROC oldCreateProfileButtonProc;
WNDPROC oldLoginButtonProc;

//
// Static welcome text
//
static HWND hStaticTitleMsg		= NULL;
static HWND hStaticWelcomeMsg	= NULL;

//
// Buttons
//
static HWND hCreateProfileButton = NULL;
static HWND hLoginButton = NULL;

void WelcomeView::Create(HWND hWnd, HINSTANCE hInst) {

	//
	// Create labels
	//

	hStaticTitleMsg = CreateWindow(L"static", L"Team ETA Blackjack", WS_CHILD,
		200, 60, 200, 30,
		hWnd, NULL, NULL, NULL);
	hStaticWelcomeMsg = CreateWindow(L"static", L"Welcome!", WS_CHILD,
		200, 90, 200, 30,
		hWnd, NULL, NULL, NULL);

	//
	// Create buttons
	//

	hLoginButton = CreateWindow(L"button", L"Login",
		WS_CHILD | BS_DEFPUSHBUTTON,
		200, 120,
		60, 20,
		hWnd, (HMENU)BUTTON_LOGIN_ID,
		hInst, NULL);

	oldLoginButtonProc = (WNDPROC)SetWindowLongPtr(
		hLoginButton,
		GWLP_WNDPROC,
		(LONG_PTR)LoginButtonProc);

	hCreateProfileButton = CreateWindow(L"button", L"Create Profile",
		WS_CHILD | BS_DEFPUSHBUTTON,
		270, 120,
		130, 20,
		hWnd, (HMENU)BUTTON_CREATE_PROFILE_ID,
		hInst, NULL);

	oldCreateProfileButtonProc = (WNDPROC)SetWindowLongPtr(
		hCreateProfileButton,
		GWLP_WNDPROC,
		(LONG_PTR)CreateProfileButtonProc);



}

void WelcomeView::Paint(HDC hdc) {

	if (!_isHidden) {
		return;
	}

	ShowWindow(hStaticTitleMsg, SW_SHOW);
	ShowWindow(hStaticWelcomeMsg, SW_SHOW);

	ShowWindow(hLoginButton, SW_SHOW);
	ShowWindow(hCreateProfileButton, SW_SHOW);
	
	_isHidden = false;
}


void WelcomeView::Hide() {

	if (_isHidden) {
		return;
	}

	//
	// Clear and hide all widgets.
	//

	ShowWindow(hStaticTitleMsg, SW_HIDE);
	ShowWindow(hStaticWelcomeMsg, SW_HIDE);

	ShowWindow(hLoginButton, SW_HIDE);
	ShowWindow(hCreateProfileButton, SW_HIDE);

	_isHidden = true;

}


LRESULT CALLBACK CreateProfileButtonProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	if (msg == WM_LBUTTONDOWN) {

		GameEngine::getInstance()->setState(GameEngine::STATE_CREATE_PROFILE);

		RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
						RDW_INVALIDATE | RDW_UPDATENOW);

		return 0;
	}

	return CallWindowProc(oldCreateProfileButtonProc, hWnd, msg, wp, lp);
}


LRESULT CALLBACK LoginButtonProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	if (msg == WM_LBUTTONDOWN) {

		GameEngine::getInstance()->setState(GameEngine::STATE_LOGIN);

		RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);

		return 0;
	}

	return CallWindowProc(oldLoginButtonProc, hWnd, msg, wp, lp);
}
