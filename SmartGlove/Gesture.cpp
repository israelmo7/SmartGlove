#include "Gesture.h"
//#include <string>

/*
	Ctor.
	The function init the vars.
*/
Gesture::Gesture()
{
	for (int i = 0; i < NUM_FINGERS; i++)
	{
		this->_fingers.push_back("");
	}
	for (int i = 0; i < NUM_AXIS; i++)
	{
		this->_acceleration.push_back("");
	}
	this->_commandNumber = -1;
}

/*
	Ctor (create from parameters [1]).
*/
Gesture::Gesture(string fingers[NUM_FINGERS], int commandNumber, string acceleration[NUM_AXIS])
{
	this->_commandNumber = commandNumber;

	for (int i = 0; i < NUM_FINGERS; i++)
	{
		this->_fingers[i] = fingers[i];
	}
	for (int i = 0; i < NUM_AXIS; i++)
	{
		this->_acceleration[i] = _acceleration[i];
	}
}

/*
	Ctor (create from parameters [2]).
*/
Gesture::Gesture(string data[NUM_FINGERS + NUM_AXIS], int commandNumber)
{
	this->_commandNumber = commandNumber;

	if (this->_fingers.size() == 0){
		for (int i = 0; i < NUM_FINGERS; i++)
		{
			this->_fingers.push_back("");
		}
	}
	for (int i = 0; i < NUM_FINGERS; i++)
	{
		this->_fingers[i] = data[i];
	}

	if (this->_acceleration.size() == 0){
		for (int i = 0; i < NUM_AXIS; i++)
		{
			this->_acceleration.push_back("");
		}
	}
	for (int i = 0; i < NUM_AXIS; i++)
	{
		this->_acceleration[i] = data[i + NUM_FINGERS];
	}
}

/*
	Dtor.
*/
Gesture::~Gesture(){}

/*
	This function is used to print the Gesture info.
	Input:
		none.
	Output:
		prints the information.
*/
void Gesture::printGesture() const
{
	cout << "CommandNumber: " << this->_commandNumber << endl;

	for (int i = 0; i < NUM_FINGERS; i++)
	{
		cout << "finger(" << i+1 << ") - " << this->_fingers[i].c_str() << endl;
	}
	for (int i = 0; i < NUM_AXIS; i++)
	{
		cout << "axis(" << i + 1 << ") - " << this->_acceleration[i].c_str() << endl;
	}
}

/*
	This function is used to clear the Gesture.
	Input:
		none.
	Output
		none.
*/
void Gesture::clearAll()
{
	this->_acceleration.clear();
	this->_fingers.clear();
}