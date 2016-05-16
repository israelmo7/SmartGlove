#pragma once
#include <iostream>
#include "Gyro.h"
#include "Pressure.h"
#include "Gesture.h"
#define NUM_FINGERS 5
using namespace std;

class InfoPacket
{
public:
	InfoPacket(){};
	InfoPacket(string str);
	~InfoPacket();
	void showDetails() const;
	Gyro getGyro() const;
	Pressure getPress(int fingerNum = 0) const;
	Gesture operator-(InfoPacket other) const;
private:
	Pressure _pressFingers[NUM_FINGERS];
	Gyro _gyroFingers;
};