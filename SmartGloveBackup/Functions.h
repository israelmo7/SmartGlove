#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include "InfoPacket.h"

#define NONE        -1
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

using namespace std;

/*
Functions:
למה החזרת את זה? ועדיין לא הבנתי את הקטע של השם..
arranges the packets, and can do some commands with the
packets and with the computer.
*/

class Functions
{
public:
	Functions();
	void Comparation(string infoPackets[NUM_FINGERS]);
	void RunCommand(int c);
	bool sendInput(WORD vk);
	int FileLineToStringArray(string a[NUM_FINGERS + 1], string line);
	bool SameChecks(string a[NUM_FINGERS], string b[NUM_FINGERS]);
	~Functions();

private:

	vector<string*> _fileLines;
	vector<int> _fileCommands;
};