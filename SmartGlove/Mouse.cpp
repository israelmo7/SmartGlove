#include "Mouse.h"

void Mouse::changePosition(Gesture g)
{
	if (g._fingers[1].find('+') != string::npos && g._fingers[1].find('-') == string::npos)
	{
		click();
	}
}
void Mouse::click(bool leftClick)
{
	INPUT i;
	i.type = INPUT_MOUSE;
	i.mi.dx = this->_position.getX();
	i.mi.dy = this->_position.getY();
	i.mi.time = 1000;

	i.mi.dwFlags = (leftClick) ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &i, sizeof(INPUT));

	i.mi.dwFlags = (leftClick) ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
	SendInput(1, &i, sizeof(INPUT));
}