#include "Gesture.h"
#include <string>

/*
	Ctor.
	The function init the vars.
*/
Gesture::Gesture()
{
	for (int i = 0; i < NUM_FINGERS; i++)
	{
		this->_fingers[i] = "";
	}
	this->_acceleration = "n";
	this->_commandNumber = -1;
}
Gesture::Gesture(string fingers[NUM_FINGERS], int commandNumber, string acceleration)
{
	this->_fingers = new string[NUM_FINGERS];
	this->_acceleration = acceleration;
	this->_commandNumber = commandNumber;

	for (int i = 0; i < NUM_FINGERS; i++)
	{
		this->_fingers[i] = fingers[i];
	}
}
Gesture::~Gesture()
{
	delete this->_fingers;
}
void Gesture::printGesture()
{
	cout << "Acceleration: " << this->_acceleration << endl;
	cout << "CommandNumber: " << this->_commandNumber << endl;

	for (int i = 0; i < NUM_FINGERS; i++)
	{
		cout << "finger(" << i+1 << ") - " << this->_fingers[i].c_str() << endl;
	}
}