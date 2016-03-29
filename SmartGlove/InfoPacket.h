#pragma once
#include <iostream>
#include "Gyro.h"
#include "Pressure.h"
#define NUM_FINGERS 5
using namespace std;

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