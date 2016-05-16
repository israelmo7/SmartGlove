#include <Windows.h>
#include <iostream>
#include "InfoPacket.h"

#define STEP 15
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
	InfoPacket _lastPacket;
	bool _first;
	//Gesture _gesture;
};