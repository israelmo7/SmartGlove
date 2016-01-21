#include "Gyro.h"
#include <sstream>

Gyro::Gyro(int x, int y, int z) :_x(x), _y(y), _z(z)
{

}
Gyro::~Gyro()
{

}
void Gyro::setValues(string str)
{
	this->_x = atoi(str.substr(0, 3).c_str());
	this->_y = atoi(str.substr(3, 3).c_str());
	this->_z = atoi(str.substr(6, 3).c_str());

}
string Gyro::getValues()
{
	ostringstream str;


	str << "x - " << this->_x << "\ny - " << this->_y << "\nz - " << this->_z << "\n";
	
	return str.str();
}
