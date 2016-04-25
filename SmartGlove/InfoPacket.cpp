#include "InfoPacket.h"
#define SIZE_OF_VALUE 2
#define SIZE_OF_GYRO_VALUE 9
/*
Ctor.
Input:
str - containing all the values (gyro and pressure).
P = [4 digits] = "-001"
G = [12 digits] = [(4 digits)(4 digits)(4 digits)] = [(x)(Y)(z)] = "-001+123+856-987"
1 - 5 = five fingers.
4*5+12=32
Output:
none
*/
InfoPacket::InfoPacket(string str)
{
	//cout << str.substr(0, 4).c_str() << "\n";
	//cout << str.substr(4, 4).c_str() << "\n";
	//cout << str.substr(8, 4).c_str() << "\n";
	//cout << str.substr(12, 4).c_str() << "\n";
	//cout << str.substr(16, 4).c_str() << "\n";
	//cout << str.substr(20, 12).c_str() << "\n";

	//P(1-5)
	this->_pressFingers[0] = atoi(str.substr(0, SIZE_OF_VALUE).c_str());     // P1
	this->_pressFingers[1] = atoi(str.substr(2, SIZE_OF_VALUE).c_str());     // P2
	this->_pressFingers[2] = atoi(str.substr(4, SIZE_OF_VALUE).c_str());     // P3
	this->_pressFingers[3] = atoi(str.substr(6, SIZE_OF_VALUE).c_str());     // P4
	this->_pressFingers[4] = atoi(str.substr(8, SIZE_OF_VALUE).c_str());    // P5

	//G(1-5)
	this->_gyroFingers.setValues(str.substr(10, SIZE_OF_GYRO_VALUE).c_str());     // G1

}

/*
Dtor.
Input:
none
Output:
none
*/
InfoPacket::~InfoPacket()
{

}

/*
The functios prints the details about every finger.
Input:
none
Output:
none
*/
void InfoPacket::showDetails()
{
	cout << "Accelerometer: \n" << _gyroFingers.getValues().c_str();
	cout << "Finger 1: \nPressure = " << _pressFingers[0].getValue() << "%\n";
	cout << "Finger 2: \nPressure = " << _pressFingers[1].getValue() << "%\n";
	cout << "Finger 3: \nPressure = " << _pressFingers[2].getValue() << "%\n";
	cout << "Finger 4: \nPressure = " << _pressFingers[3].getValue() << "%\n";
	cout << "Finger 5: \nPressure = " << _pressFingers[4].getValue() << "%\n";
}

Gyro InfoPacket::getGyro()
{
	return this->_gyroFingers;
}

Pressure InfoPacket::getPress(int fingerNum)
{
	Pressure pValue;

	if (fingerNum >= 0 && fingerNum < NUM_FINGERS)
	{
		pValue = this->_pressFingers[fingerNum];
	}
	else
	{
		pValue = NULL;
	}

	return pValue;
}
/*
The functios returns the pressure of some finger.
Input:
finger - the finger number.
Output:
int - if finger exist return the finger pressure, otherwise return -1
*/
//int InfoPacket::getPressure(int finger)
//{
//	return ((finger >= 0 && finger < NUM_FINGERS) ? this->_pressFingers[finger] : -1);
//}