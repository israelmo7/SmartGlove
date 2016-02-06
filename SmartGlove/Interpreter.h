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
	void begin();
private:
	vector<Packet> _packetsList;
};