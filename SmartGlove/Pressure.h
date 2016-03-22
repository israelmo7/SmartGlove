#pragma once
#include "Hardware.h"
using namespace std;

class Pressure : public Hardware
{
public:
	Pressure();
	Pressure(int* stats);
	~Pressure();
	//int getValue();
//private:
	//int _p;

};