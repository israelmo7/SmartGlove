#include <Windows.h>
#include "Gesture.h"

//#define STEPRESIZEWINDOW 10  /*Properties*/

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