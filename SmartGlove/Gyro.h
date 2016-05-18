#pragma once
#include <iostream>
#include "SmartGloveDll.h"
using namespace std;

_declspec(dllexport) class /*SMARTGLOVE_API*/ Gyro
{
public:
	Gyro(int x = 0, int y = 0, int z = 0);
	~Gyro();
	void setValues(string str);
	string getValues() const;

	void getVal(int vals[3]) const;
	int* getVal() const;
private:
	int _x,
		_y,
		_z;

};