#include "cResizeWindow.h"


cResizeWindow::cResizeWindow(HWND window)
{

}
cResizeWindow::~cResizeWindow()
{

}
int cResizeWindow::getResizeStep(int p, bool bigger, bool width)
{
	int temp;
	const RECT X = this->GetDesktopResolution();
	const RECT x = this->GetDesktopResolution(false);


	temp = (width) ? ((bigger) ? X.right - x.right : X.right + x.right) : ((bigger) ? X.top - x.top : X.top + x.top);

	return (bigger) ? temp*p / 100 : -temp*p / 100;
}
RECT cResizeWindow::GetDesktopResolution(bool isDesktop)
{
	RECT desktop;

	const HWND hDesktop = (isDesktop) ? GetDesktopWindow() : GetForegroundWindow();

	GetWindowRect(hDesktop, &desktop);

	return desktop;
}
void cResizeWindow::reSizeForMoveWindowClass(Gesture g, int values[4], int fingerState[NUM_FINGERS])
{
	//[0] - TL.x
	//[1] - TL.y
	//[2] - Width
	//[3] - Height
	
	if (g._fingers[0] != "")
	{
		int tempX;
		if (g._fingers[0] == "+")
		{
			tempX = -this->getResizeStep(fingerState[0],true,true) / 2;
		}
		else
		{
			tempX = this->getResizeStep(fingerState[0], false, true) / 2;
		}
		values[0] = values[0] + tempX;
		values[2] = values[2] - tempX;
	}
	if (g._fingers[1] != "")
	{
		int tempY;
		if (g._fingers[1] == "+")
		{
			tempY = -this->getResizeStep(fingerState[0], true, false) / 2;
		}
		else
		{
			tempY = this->getResizeStep(fingerState[0], false, false) / 2;
		}
		values[1] = values[1] + tempY;
		values[3] = values[3] - tempY;
	}
}