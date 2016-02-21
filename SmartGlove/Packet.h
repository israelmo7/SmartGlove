#pragma once
#include <iostream>
#include "Gyro.h"
#include "Pressure.h"
#define NUM_FINGERS 5
using namespace std;

class Packet
{
public:
	Packet(){};
	Packet(string str);
	~Packet();
	void showDetails();
	Gyro getGyro();
	Pressure* getPress(int finger = 0);
	//int getPressure(int finger);
private:
	Pressure _pressFingers[NUM_FINGERS];
	Gyro _gyroFingers;
};