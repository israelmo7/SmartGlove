#pragma once
#include <iostream>
#include <vector>
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
	void orderPackets(string str);
	void runCommand(int i);
	void begin();
private:
	vector<Packet> _packetsList;
};