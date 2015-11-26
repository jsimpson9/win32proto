#include <windows.h>
#include <stdio.h>

#include "Utils.h"

void updateTextarea(
					HWND textarea,
					char* message) {

	size_t convertedChars = 0;


	char messageText[50];

	snprintf(messageText, 50, message);

	wchar_t messageWtext[30];
	mbstowcs_s(
		&convertedChars, messageWtext,
		(size_t)30, messageText,
		strlen(messageText) + 1);

	SetWindowText(textarea, messageWtext);

}
