#include <Windows.h>
#include "Gesture.h"

//#define STEPRESIZEWINDOW 10  /*Properties*/

class cResizeWindow
{
public:
	cResizeWindow(HWND window);
	~cResizeWindow();
	int getResizeStep(int p, bool bigger = true, bool width = true);
	void reSizeForMoveWindowClass(Gesture g, int values[4], int fingerState[NUM_FINGERS]);
private:
	RECT GetDesktopResolution(bool isDesktop = true);

};