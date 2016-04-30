#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "InfoPacket.h"

#define NUM_AXIS 3
//#define PALM_TO_SKY      "+s"
//#define NE_PALM_TO_SKY   "-s"
//#define PALM_TO_LEFT     "+l"
//#define NE_PALM_TO_LEFT  "-l"
//#define PALM_TO_ME       "+m"
//#define NE_PALM_TO_ME    "-m"
//#define NONE             "null"

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
	//void checkAccel(InfoPacket pack);
	//void showAccel();
private:
	InfoPacket _lastPacket;						 // The last packet
	//string _symbolF[NUM_FINGERS];				// f = flex
	//string _symbolA[NUM_AXIS];		       // the Accel' state.
	string  _symbol[NUM_FINGERS + NUM_AXIS];   // the states.
	char _equalsSeq[NUM_FINGERS+NUM_AXIS];    // check for the end of the gesture.
	bool _first;							 // check if its the first packet

};