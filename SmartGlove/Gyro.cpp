#include "Gyro.h"
#include <sstream>

/*
Ctor.
Input:
x - x value
y - y value
z - z value
Output:
none
*/
Gyro::Gyro(int x, int y, int z) :_x(x), _y(y), _z(z)
{

}

/*
Dtor.
Input:
none
Output:
none
*/
Gyro::~Gyro()
{

}

/*
Set the three values from string.
Input:												 x         y        z
str - Contains the three values of the Gyro. [3 digits|3 digits|3 digits], eg "012098000"
Output:
none
*/
void Gyro::setValues(string str)
{
	this->_x = atoi(str.substr(0, 3).c_str());
	this->_y = atoi(str.substr(3, 3).c_str());
	this->_z = atoi(str.substr(6, 3).c_str());

}

/*
Set the three values from string.
Input:
none
Output:
string - Contains the three values "x - [x] \n .. "
*/
string Gyro::getValues()
{
	ostringstream str;


	str << "x - " << this->_x << "\ny - " << this->_y << "\nz - " << this->_z << "\n";

	return str.str();
}
/*
Get the three values in array.
Input:
none
Output:
int*- x,y and z
*/
int* Gyro::getVal()
{
	int vals[3] = { this->_x, this->_y, this->_z };
	return vals;
}