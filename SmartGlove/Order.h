#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include "InfoPacket.h"
#include "Gesture.h"

#define PAGE_UP      1
#define PAGE_DOWN    2
#define REFRESH		 3
#define SNAPSHOT	 4
#define PSMUSIC		 5
#define PSONG		 6
#define NSONG		 7
#define BPAGE		 8
#define FPAGE		 9
#define VOLUMEM		 10
#define VOLUMEU		 11
#define VOLUMED		 12

using namespace std;

class Order
{
public:
	Order();
	void TheComparetion(string *infoPackets);
	void runCommand(int c);
	bool sendInput(WORD vk);
	void printLines();
	int fileLineToStringArray (string line, string* save);
	bool sameChecks(string a[NUM_FINGERS], string b[NUM_FINGERS]);
	~Order();

private:

	vector<Gesture*> _lines; // The file lines.
};