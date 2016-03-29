#include "Pressure.h"
#include <sstream>

/*
	Ctor.
	Input:
		press - p value
	Output:
		none
*/
Pressure::Pressure(int press) :_value(press)
{

}

/*
	Dtor.
	Input:
		none
	Output:
		none
*/
Pressure::~Pressure()
{

}

/*
	get the value of the pressure.
	Input:
		none
	Output
		int - the value
*/
int Pressure::getValue()
{
	return this->_value;
}