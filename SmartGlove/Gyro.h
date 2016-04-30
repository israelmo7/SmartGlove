#pragma once
#include <iostream>
using namespace std;

class Gyro
{
public:
	Gyro(int x = 0, int y = 0, int z = 0);
	~Gyro();
	void setValues(string str);
	string getValues();
	void getVal(int vals[3]);
	int* getVal();
private:
	int _x,
		_y,
		_z;

};