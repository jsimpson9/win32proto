#pragma once

#ifndef ABSTRACTVIEWCOMPONENT_H
#define ABSTRACTVIEWCOMPONENT_H

class AbstractViewComponent {

protected:

	boolean _isHidden = true;

public:

	virtual void Create(HWND hWnd, HINSTANCE hInst) = 0;
	virtual void Paint(HDC hdc)	= 0;
	virtual void Hide()	= 0;
};

#endif
