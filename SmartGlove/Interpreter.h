#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "InfoPacket.h"

#define AXIS 3

using namespace std;

class Interpreter
{
public:
	Interpreter();
	Interpreter(InfoPacket p);
	~Interpreter();
	bool addInfoPacket(InfoPacket p);
	void InfoPacketsDetails();
	//void clearList(){ this->_InfoPacketsList.clear(); }
	bool InfoPacketsArrayToCharsArray(InfoPacket newPacket);
	void saveTheSymbol(string arr[NUM_FINGERS]);
	bool checkToEnd();
	void showSeq();
	void clearAll();

private:
	//vector<InfoPacket> _InfoPacketsList;
	InfoPacket _lastPacket;
	string _symbol[NUM_FINGERS];
	string* _gyroSymbol[AXIS];
	char _equalsSeq[NUM_FINGERS];
	bool _first;
};