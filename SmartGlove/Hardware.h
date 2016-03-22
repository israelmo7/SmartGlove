#pragma once
#include <iostream>
class Hardware
{
public:
	 Hardware(int* stats);			//3 Stats- Gyro, 1 Stat- Pressure//
	 Hardware();
	 virtual int* getValues();
	 virtual void setValues(int* newStats);
	~Hardware();
protected:
	int* stats;
};

