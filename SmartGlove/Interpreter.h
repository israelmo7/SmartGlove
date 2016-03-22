#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <string>
#include "Packet.h"
#include "Functions.h"

#define X			 1
#define Y			 2
#define Z			 3

using namespace std;

class Interpreter
{
public:
	Interpreter() {}
	Interpreter(Packet p);
	~Interpreter();
	void addPacket(Packet p);
	void packetsDetails();
	//void runCommand(int c);			
	//bool sendInput(WORD vk);
	//void fileLineToStringArray(string a[NUM_FINGERS + 1], string line);
	//bool sameChecks(string a[], string b[]);
	string* begin();
private:
	vector<Packet> _packetsList;
};