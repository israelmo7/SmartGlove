#include <Windows.h>
#include "InfoPacket.h"

//#define STEPMOVEWINDOW 15 /*Properties*/
//#define WIDTH_SCREEN  1366 /*Properties*/
//#define HEIGHT_SCREEN 768 /*Properties*/
#define DEFAULT_BUFLEN 19 // Size of The packet

using namespace std;

class cMoveWindow
{
public:

	cMoveWindow(SOCKET s);
	~cMoveWindow();

	bool changePosition(Gesture g);
	bool getPosition(POINT* topL, POINT* bottomR);
	bool setWindowPos(int values[4]);

private:

	void GetDesktopResolution();

	InfoPacket _lastPacket;
	bool _first;
	//Gesture _gesture;
};