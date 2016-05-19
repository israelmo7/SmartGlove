#pragma once
<<<<<<< HEAD
#include <iostream>
#include "SmartGloveDll.h"
using namespace std;
=======
>>>>>>> origin/israel

_declspec(dllexport) class /*SMARTGLOVE_API*/ Pressure
{
public:
	Pressure(int press = 0);
	~Pressure();
	int getValue() const;
private:
	int _value;

};