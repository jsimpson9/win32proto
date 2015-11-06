#include <windows.h>
#include <tchar.h>

#include "LoginView.h"
#include "GameEngine.h"
#include "User.h"

#define BUTTON_PERFORM_LOGIN_ID					4001
#define BUTTON_CANCEL_LOGIN_ID					4002


//
// Callbacks / function prototypes
//
LRESULT CALLBACK PerformLoginButtonProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CancelLoginButtonProc(HWND, UINT, WPARAM, LPARAM);

WNDPROC oldPerformLoginButtonProc;
WNDPROC oldCancelLoginButtonProc;


//
// Static welcome text
//
static HWND hStaticLoginUserMsg = NULL;
static HWND hStaticLoginPassMsg = NULL;

//
// Input widgets
//
static HWND hLoginViewUsernameTextbox = NULL;
static HWND hLoginViewPasswordTextbox = NULL;

//
// Buttons
//
static HWND hPerformLoginButton = NULL;
static HWND hCancelLoginButton = NULL;


void LoginView::Create(HWND hWnd, HINSTANCE hInst) {

	//
	// Create labels
	//

	hStaticLoginUserMsg = CreateWindow(L"static", L"Username:", WS_CHILD,
		200, 60, 90, 30,
		hWnd, NULL, NULL, NULL);
	hStaticLoginPassMsg = CreateWindow(L"static", L"Password:", WS_CHILD,
		200, 90, 90, 30,
		hWnd, NULL, NULL, NULL);

	//
	// Create input widgets
	//
	hLoginViewUsernameTextbox = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_BORDER,
		300, 60, 140, 30,
		hWnd, NULL, NULL, NULL);
	hLoginViewPasswordTextbox = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_BORDER | ES_PASSWORD,
		300, 90, 140, 30,
		hWnd, NULL, NULL, NULL);

	//
	// Create buttons
	//

	hPerformLoginButton = CreateWindow(L"button", L"Login",
		WS_CHILD | BS_DEFPUSHBUTTON,
		200, 125,
		60, 20,
		hWnd, (HMENU)BUTTON_PERFORM_LOGIN_ID,
		hInst, NULL);

	oldPerformLoginButtonProc = (WNDPROC)SetWindowLongPtr(
		hPerformLoginButton,
		GWLP_WNDPROC,
		(LONG_PTR)PerformLoginButtonProc);

	hCancelLoginButton = CreateWindow(L"button", L"Cancel",
		WS_CHILD | BS_DEFPUSHBUTTON,
		270, 125,
		60, 20,
		hWnd, (HMENU)BUTTON_CANCEL_LOGIN_ID,
		hInst, NULL);

	oldCancelLoginButtonProc = (WNDPROC)SetWindowLongPtr(
		hCancelLoginButton,
		GWLP_WNDPROC,
		(LONG_PTR)CancelLoginButtonProc);



}

void LoginView::Paint(HDC hdc) {

	if (!_isHidden) {
		return;
	}

	ShowWindow(hStaticLoginUserMsg, SW_SHOW);
	ShowWindow(hStaticLoginPassMsg, SW_SHOW);

	ShowWindow(hLoginViewUsernameTextbox, SW_SHOW);
	ShowWindow(hLoginViewPasswordTextbox, SW_SHOW);

	ShowWindow(hPerformLoginButton, SW_SHOW);
	ShowWindow(hCancelLoginButton, SW_SHOW);

	_isHidden = false;
}


void LoginView::Hide() {

	if (_isHidden) {
		return;
	}

	//
	// Clear and hide all widgets.
	//

	ShowWindow(hStaticLoginUserMsg, SW_HIDE);
	ShowWindow(hStaticLoginPassMsg, SW_HIDE);

	ShowWindow(hLoginViewUsernameTextbox, SW_HIDE);
	ShowWindow(hLoginViewPasswordTextbox, SW_HIDE);
	SetWindowText(hLoginViewUsernameTextbox, L"");
	SetWindowText(hLoginViewPasswordTextbox, L"");

	ShowWindow(hPerformLoginButton, SW_HIDE);
	ShowWindow(hCancelLoginButton, SW_HIDE);

	_isHidden = true;

}


LRESULT CALLBACK PerformLoginButtonProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	if (msg == WM_LBUTTONDOWN) {

		//
		// TODO authenticate user here...
		//

		//
		// NOTE hard code user for now to test 
		// for bad login, modal popup, etc.
		//
		TCHAR buff[64];
		GetWindowText(hLoginViewUsernameTextbox, buff, 20);

		if (_tcscmp(L"etauser", buff) != 0)
		{
			MessageBox(
				GameEngine::getInstance()->getHWnd(),
				L"Incorrect username or password.",
				L"Login Failed",
				NULL);

			//
			// Do not update game engine state. Return.
			//
			return 0;
		}

		GameEngine* gameEngine = GameEngine::getInstance();

		User* user = new User("etauser", "123", 0, 0, 100, NULL);
		
		gameEngine->setUser(user);
		gameEngine->setState(GameEngine::STATE_PLAYING);

		RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);

		return 0;
	}

	return CallWindowProc(oldPerformLoginButtonProc, hWnd, msg, wp, lp);
}


LRESULT CALLBACK CancelLoginButtonProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	if (msg == WM_LBUTTONDOWN) {

		GameEngine::getInstance()->setState(GameEngine::STATE_INITIAL);

		RedrawWindow(GameEngine::getInstance()->getHWnd(), NULL, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW);

		return 0;
	}

	return CallWindowProc(oldCancelLoginButtonProc, hWnd, msg, wp, lp);
}
