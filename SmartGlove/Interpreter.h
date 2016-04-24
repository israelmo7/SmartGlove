#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "InfoPacket.h"

#define PALM_TO_SKY      "+s"
#define NE_PALM_TO_SKY   "-s"
#define PALM_TO_LEFT     "+l"
#define NE_PALM_TO_LEFT  "-l"
#define PALM_TO_ME       "+m"
#define NE_PALM_TO_ME    "-m"
#define NONE             "null"

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
	void clearAll();
	void checkAccel(InfoPacket pack);
	void showAccel();
private:
	InfoPacket _lastPacket;			    // The last packet
	string _symbolF[NUM_FINGERS];      // f = flex
	string _stateA[3];				  // the Accel' state.
	char _equalsSeq[NUM_FINGERS];    // check for the end of the gesture.
	bool _first;                    // check if its the first packet

};