#include "cResizeWindow.h"
#define STEP 10

cResizeWindow::cResizeWindow(HWND window)
{
	if (window)
	{
		this->_window = window;
	}
	else
	{
		cout << "Error : " << GetLastError() << endl;
	}
}
cResizeWindow::~cResizeWindow()
{

}
bool cResizeWindow::changeWindowSize(Gesture g)
{
	POINT topL,
		bottomR;

	if (!this->getPosition(&topL, &bottomR))
	{
		cout << "getPosition Error: " << GetLastError() << endl;
		return false;
	}

	if (g._fingers[0] == "-" && g._fingers[1] == "-" && g._fingers[2] == "=") //מה זה ההארדקוד המגעיל הזה :O
	{
		if (!SetWindowPos(this->_window, 0, topL.x - STEP/2, topL.y - STEP/2, bottomR.x - topL.x + STEP, bottomR.y - topL.y + STEP, SWP_DRAWFRAME))
		{
			cout << "SetWindowPos Error: " << GetLastError() << endl;
			return false;
		}
	}
	else if (g._fingers[0] == "+" && g._fingers[1] == "+" && g._fingers[2] == "=")
	{
		if (!SetWindowPos(this->_window, 0, topL.x + STEP/2, topL.y + STEP/2, bottomR.x - topL.x - STEP, bottomR.y - topL.y - STEP, SWP_DRAWFRAME))
		{
			cout << "SetWindowPos Error: " << GetLastError() << endl;
			return false;
		}
	}
	return true;
}
bool cResizeWindow::getPosition(POINT* topL, POINT* bottomR)
{
	RECT r;

	if (GetWindowRect(this->_window, &r))
	{
		topL->x = r.left;
		topL->y = r.top;

		bottomR->x = r.right;
		bottomR->y = r.bottom;
		return true;
	}
	return false;
}