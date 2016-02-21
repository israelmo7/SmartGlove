#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "Packet.h"

using namespace std;

class Interpreter
{
public:
	Interpreter() {}
	Interpreter(Packet p);
	~Interpreter();
	void addPacket(Packet p);
	void packetsDetails();
	void runCommand(int c);
	bool sendInput(WORD vk);
	void fileLineToStringArray(string a[NUM_FINGERS + 1], string line);
	bool sameChecks(string a[NUM_FINGERS], string b[NUM_FINGERS]);
	void begin();
private:
	vector<Packet> _packetsList;
};