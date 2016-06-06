#include "cResizeWindow.h"
#include "Properties.h"
#define STR(x)#x

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
	if (g._fingers[0] != "")
	{
		int tempX;
		if (atoi(g._fingers[0].c_str()) > 0)
		{
			tempX = -this->getResizeStep(fingerState[0],true,true) / 2;
		}
		else if (atoi(g._fingers[0].c_str()) < 0)
		{
			tempX = this->getResizeStep(fingerState[0], false, true) / 2;
		}
		values[0] = values[0] + tempX;
		values[2] = values[2] - tempX;
	}
	if (g._fingers[1] != "")
	{
		int tempY;
		if (atoi(g._fingers[1].c_str()) > 0)
		{
			tempY = -this->getResizeStep(fingerState[0], true, false) / 2;
		}
		else if (atoi(g._fingers[1].c_str()) < 0)
		{
			tempY = this->getResizeStep(fingerState[0], false, false) / 2;
		}
		values[1] = values[1] + tempY;
		values[3] = values[3] - tempY;
	}
}

int cResizeWindow::valueRange(int value)
{
	Properties p = Properties();
	int offset = p.getValueByName(STR(MAX_OFFSET));
	if (value > 0){
		for (int i = 0; i < offset; i++){
			if (value >= i*offset && value <= i*offset + 9){
				return i + 1;
			}
		}
	}
	else if (value < 0){
		for (int i = 0; i > -offset; i--){
			if (value >= i*offset && value <= i*offset + 9){
				return i - 1;
			}
		}
	}
	return 0;
}