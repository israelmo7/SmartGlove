#pragma once
#include <iostream>
#include "Gyro.h"
#include "Pressure.h"
#define NUM_FINGERS 5
using namespace std;

/*
InfoPacket:
this class is used for all the info of the packets.
you can show all the details of the packet, and get
specific details.
*/

class InfoPacket
{
public:
	InfoPacket(){};
	InfoPacket(string str);
	~InfoPacket();
	void showDetails();
	Gyro getGyro();
	Pressure getPress(int fingerNum = 0);

private:
	Pressure _pressFingers[NUM_FINGERS];
	Gyro _gyroFingers;
};