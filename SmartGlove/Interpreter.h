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
	void saveTheRanges(string *arr);
	bool checkToEnd();
	void showSeq();
	void clearAll();
	void calculateRanges(InfoPacket newPacket);
	int valueRange(int value, bool accel = 0);
	//void calculateranges(int sumAxis[NUM_AXIS]);
private:
	InfoPacket _lastPacket; // The last packet			
	//Gesture _rangess;
	string  _ranges[NUM_FINGERS + NUM_AXIS];   // the ranges between packets.
	string  _symbols[NUM_FINGERS + NUM_AXIS]; // The sign of the ranges
	int _equalsSeq[NUM_FINGERS];    // check for the end of the gesture.
};