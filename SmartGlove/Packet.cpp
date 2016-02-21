#include "Packet.h"

/*
Ctor.
Input:
str - containing all the values (gyro and pressure).
P = [3 digits] = "001"
G = [9 digits] = [(3 digits)(3 digits)(3 digits)] = [(x)(Y)(z)] = "001123856987"
1 - 5 = five fingers.

Output:
none
*/
Packet::Packet(string str)
{
	//P(1-5)
	this->_pressFingers[0] = atoi(str.substr(0, 3).c_str());     // P1
	this->_pressFingers[1] = atoi(str.substr(3, 3).c_str());     // P2
	this->_pressFingers[2] = atoi(str.substr(6, 3).c_str());     // P3
	this->_pressFingers[3] = atoi(str.substr(9, 3).c_str());     // P4
	this->_pressFingers[4] = atoi(str.substr(12, 3).c_str());    // P5

	//G(1-5)
	this->_gyroFingers.setValues(str.substr(15, 9).c_str());     // G1

}

/*
Dtor.
Input:
none
Output:
none
*/
Packet::~Packet()
{

}

/*
The functios prints the details about every finger.
Input:
none
Output:
none
*/
void Packet::showDetails()
{
	cout << "Accelerometer: \n" << _gyroFingers.getValues().c_str();
	cout << "Finger 1: \nPressure = " << _pressFingers[0].getValue() << "%\n";
	cout << "Finger 2: \nPressure = " << _pressFingers[1].getValue() << "%\n";
	cout << "Finger 3: \nPressure = " << _pressFingers[2].getValue() << "%\n";
	cout << "Finger 4: \nPressure = " << _pressFingers[3].getValue() << "%\n";
	cout << "Finger 5: \nPressure = " << _pressFingers[4].getValue() << "%\n";
}

Gyro Packet::getGyro()
{
	return this->_gyroFingers;
}

Pressure* Packet::getPress(int finger)
{
	if (finger){
		return &(this->_pressFingers[finger]);
	}
	return this->_pressFingers;
}
/*
The functios returns the pressure of some finger.
Input:
finger - the finger number.
Output:
int - if finger exist return the finger pressure, otherwise return -1
*/
//int Packet::getPressure(int finger)
//{
//	return ((finger >= 0 && finger < NUM_FINGERS) ? this->_pressFingers[finger] : -1);
//}