#include "cResizeWindow.h"
#include "Properties.h"

#define STR(x) #x

int STEPRESIZEWINDOW = 0;

cResizeWindow::cResizeWindow(HWND window)
{
	Properties p = Properties();
	STEPRESIZEWINDOW = p.getValueByName(STR(STEPRESIZEWINDOW));

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

	if (g._fingers[0] == "-" && g._fingers[1] == "-" && g._fingers[2] == "=")
	{
		if (!SetWindowPos(this->_window, 0, topL.x - STEPRESIZEWINDOW / 2, topL.y - STEPRESIZEWINDOW / 2, bottomR.x - topL.x + STEPRESIZEWINDOW, bottomR.y - topL.y + STEPRESIZEWINDOW, SWP_DRAWFRAME))
		{
			cout << "SetWindowPos Error: " << GetLastError() << endl;
			return false;
		}
	}
	else if (g._fingers[0] == "+" && g._fingers[1] == "+" && g._fingers[2] == "=")
	{
		if (!SetWindowPos(this->_window, 0, topL.x + STEPRESIZEWINDOW / 2, topL.y + STEPRESIZEWINDOW / 2, bottomR.x - topL.x - STEPRESIZEWINDOW, bottomR.y - topL.y - STEPRESIZEWINDOW, SWP_DRAWFRAME))
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