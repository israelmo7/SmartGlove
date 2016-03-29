#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "InfoPacket.h"


using namespace std;

class Interpreter
{
public:
	Interpreter() {}
	Interpreter(InfoPacket p);
	~Interpreter();
	void addInfoPacket(InfoPacket p);
	void InfoPacketsDetails();

	void InfoPacketsArrayToCharsArray(string a[NUM_FINGERS]);
	void begin();
private:
	vector<InfoPacket> _InfoPacketsList;
};