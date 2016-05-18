#pragma once
#include <iostream>
#include "SmartGloveDll.h"
using namespace std;

_declspec(dllexport) class /*SMARTGLOVE_API*/ Pressure
{
public:
	Pressure(int press = 0);
	~Pressure();
	int getValue() const;
private:
	int _value;

};