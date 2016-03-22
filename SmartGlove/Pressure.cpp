#include "Pressure.h"
#include <sstream>


Pressure::Pressure(){}

/*
	Ctor.
	Input:
		stats - p value
	Output:
		none
*/
Pressure::Pressure(int* stats) : Hardware(stats)
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
//int Pressure::getValue()
//{
//	return this->_p;
//}