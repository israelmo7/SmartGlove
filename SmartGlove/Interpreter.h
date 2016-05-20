#pragma once
//#include <Windows.h>
#include "InfoPacket.h"

#define NUM_AXIS 3
//#define MAX_OFFSET 5 /*Properties*/


using namespace std;

class Interpreter
{
public:
	Interpreter();
	Interpreter(InfoPacket p);
	~Interpreter();
	bool addInfoPacket(InfoPacket p);
	void InfoPacketsDetails();
	bool InfoPacketsArrayToCharsArray(InfoPacket newPacket);
	void saveTheSymbol(string *arr);
	bool checkToEnd();
	void showSeq();
	void showSymbols();
	void clearAll();
private:
	InfoPacket _lastPacket;						 // The last packet
	string  _symbol[NUM_FINGERS + NUM_AXIS];   // the states.
	char _equalsSeq[NUM_FINGERS+NUM_AXIS];    // check for the end of the gesture.
	bool _first;							 // check if its the first packet
};