#include <Windows.h>
#include "InfoPacket.h"


#define DEFAULT_BUFLEN 19 // Size of The packet

using namespace std;

class cMoveWindow
{
public:

	cMoveWindow(SOCKET s, string lastRecv);
	~cMoveWindow();

	bool changePosition(Gesture g, int fingerState[NUM_FINGERS], InfoPacket packet);
	bool getPosition(POINT* topL, POINT* bottomR);
	bool setWindowPos(int values[4]);
	bool replaceWindows();
	int valueRange(int value);
private:

	void GetDesktopResolution();

	InfoPacket _lastPacket;
};