#include <Windows.h>
#include <iostream>
#include "Gesture.h"
using namespace std;

class cResizeWindow
{
public:
	cResizeWindow(HWND window);
	~cResizeWindow();
	bool changeWindowSize(Gesture g);
	bool getPosition(POINT* topL, POINT* bottomR);

private:
	HWND _window;

};