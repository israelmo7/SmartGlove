#pragma once
#include <iostream>
#include "Gyro.h"
#define NUM_FINGERS 5
using namespace std;

class Packet
{
public:
	Packet(){};
	Packet(string str);
	~Packet();
	void showDetails();
	int getPressure(int finger);
private:
	int _pressFingers[NUM_FINGERS];
	Gyro _gyroFingers[NUM_FINGERS];
};