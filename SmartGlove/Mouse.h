#include <Windows.h>
#include <iostream>
#include "Gesture.h"
#include "InfoPacket.h"
#include "SmartGloveDll.h"

_declspec(dllexport) class /*SMARTGLOVE_API*/ Mouse
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