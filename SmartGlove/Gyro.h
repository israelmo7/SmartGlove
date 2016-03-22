#pragma once
#include "Hardware.h"
using namespace std;

class Gyro : public Hardware
{
public:
	Gyro();
	Gyro(int* xyz);
	~Gyro();
	void setValues(string str);
	string PrintValues();
	//void getVal(int vals[3]);
private:
	int _x,
		_y,
		_z;

};