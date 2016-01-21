#include "Packet.h"

Packet::Packet(string str)
{
	//P(1-5)
	this->_pressFingers[0] = atoi(str.substr(5, 3).c_str());     // P1
	this->_pressFingers[1] = atoi(str.substr(8, 3).c_str());     // P2
	this->_pressFingers[2] = atoi(str.substr(11, 3).c_str());    // P3
	this->_pressFingers[3] = atoi(str.substr(14, 3).c_str());    // P4
	this->_pressFingers[4] = atoi(str.substr(17, 3).c_str());    // P5

	//G(1-5)
	this->_gyroFingers[0].setValues(str.substr(20, 9).c_str());  // G1
	this->_gyroFingers[1].setValues(str.substr(29, 9).c_str());  // G2
	this->_gyroFingers[2].setValues(str.substr(38, 9).c_str());  // G3
	this->_gyroFingers[3].setValues(str.substr(47, 9).c_str());  // G4
	this->_gyroFingers[4].setValues(str.substr(56, 9).c_str());  // G5

}
Packet::~Packet()
{

}
void Packet::showDetails()
{
	cout << "Finger 1: \nPressure = " << _pressFingers[0] << "%\n" << _gyroFingers[0].getValues().c_str() << "\n";
	cout << "Finger 2: \nPressure = " << _pressFingers[1] << "%\n" << _gyroFingers[1].getValues().c_str() << "\n";
	cout << "Finger 3: \nPressure = " << _pressFingers[2] << "%\n" << _gyroFingers[2].getValues().c_str() << "\n";
	cout << "Finger 4: \nPressure = " << _pressFingers[3] << "%\n" << _gyroFingers[3].getValues().c_str() << "\n";
	cout << "Finger 5: \nPressure = " << _pressFingers[4] << "%\n" << _gyroFingers[4].getValues().c_str() << "\n";

}
int Packet::getPressure(int finger)
{
	return ((finger >= 0 && finger < NUM_FINGERS) ? this->_pressFingers[finger] : -1);
}