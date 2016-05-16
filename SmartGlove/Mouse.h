#include <Windows.h>
#include <iostream>
#include "Gesture.h"
#include "InfoPacket.h"

class Mouse
{
public:
	//Mouse(){}
	Mouse(SOCKET s);
	Mouse(POINT position) :_position(position){};
	~Mouse(){}
	
	bool changePosition(Gesture g);
	void click(bool leftClick = true);
	void release(bool leftClick = true);
private:
	POINT _position;
	InfoPacket _lastPacket;
	bool _first;
	//Gesture _gesture;
};