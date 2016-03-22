#pragma once
#include <iostream>
#include <vector>
//#include <string>
//#include <fstream>
#include <Windows.h>
#include "Packet.h"

#define PAGE_UP      0
#define PAGE_DOWN    1
#define REFRESH		 2
#define SNAPSHOT	 3
#define PSMUSIC		 4
#define PSONG		 5
#define NSONG		 6
#define BPAGE		 7
#define FPAGE		 8
#define VOLUMEM		 9
#define VOLUMEU		 10
#define VOLUMED		 11
#define MINSPEEDMOVE 0
#define FINSPEEDMOVE 70
#define MAXSPEEDMOVE 100

using namespace std;

class Functions
{
public:
	Functions(vector<Packet> arr);
	int getCommandNumber();
	void setCommandNumber(int c);
	vector<Packet> getArr();
	void packetsArrayToCharsArray(string a[NUM_FINGERS]);
	void fileLineToStringArray(string a[NUM_FINGERS + 1], string line);
	bool sameChecks(string a[], string b[]);
	bool sendInput(WORD vk);
	void runCommand(int c);
	char gyroToChar(int what);
	~Functions();

private:


	vector<Packet> _arr;
	int _commandNumber;
};