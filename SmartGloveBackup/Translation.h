#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "InfoPacket.h"

using namespace std;

/*
Translation:
ישראל תן הסבר טוב
advanced use of the packets, used for translation.
*/

class Translation
{
public:
	Translation() {}
	Translation(InfoPacket p);
	~Translation();
	void Add(InfoPacket p);
	void Details();

	void TransPackets(string a[NUM_FINGERS]);
	void BeginTrans();
private:
	vector<InfoPacket> _InfoPacketsList;
};