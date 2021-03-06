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
Input:											 x         y        z
str - Contains the three values of the Gyro. [4 digits|4 digits|4 digits], eg "-012+098-000"
Output:
none
*/
void Gyro::setValues(string str)
{
	try
	{
		this->_x = atoi(str.substr(0, 3).c_str());
		this->_y = atoi(str.substr(3, 3).c_str());
		this->_z = atoi(str.substr(6, 3).c_str());
	}
	catch (exception& e)
	{
		cout << "Convert Gyro values from String to Int failed with error : " << e.what() << endl;
	}
}

/*
Set the three values from string.
Input:
none
Output:
string - Contains the three values "x - [x] \n .. "
*/
string Gyro::getValues() const
{
	ostringstream str;


	str << "X - " << this->_x << "\nY - " << this->_y << "\nZ - " << this->_z << "\n";

	return str.str();
}
/*
Get the three values in array.
Input:
int vals[3] - the values to set.
Output:
sets the values in the array.
*/
void Gyro::getVal(int vals[3]) const
{
	vals[0] = this->_x;
	vals[1] = this->_y;
	vals[2] = this->_z;
}

/*
Get the three values in array.
Input:
none
Output:
int*- x,y and z
*/
int* Gyro::getVal() const
{
	int* ret = new int[3];
	ret[0] = this->_x;
	ret[1] = this->_y;
	ret[2] = this->_z;
	return ret;
}

/*
Get single value of specific axis.
Input:
int axis - the axis.
Output:
int - the value of the axis.
*/
int Gyro::getVal(int axis) const
{
	switch (axis){
	case 0:
		return this->_x;
	case 1:
		return this->_y;
	case 2:
		return this->_z;
	default:
		return -1;
}
}