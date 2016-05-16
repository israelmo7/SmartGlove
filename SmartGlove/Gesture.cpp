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
		this->_fingers.push_back("");
	}
	for (int i = 0; i < NUM_AXIS; i++)
	{
		this->_acceleration.push_back("");
	}
	this->_commandNumber = -1;
}
/*
Gesture::Gesture(InfoPacket i)
{
	int temp[3];
	char buff[4];

	i.getGyro().getVal(temp);

	itoa(temp[0], buff, 10);
	this->_acceleration.push_back(buff);

	itoa(temp[1], buff, 10);
	this->_acceleration.push_back(buff);

	itoa(temp[2], buff, 10);
	this->_acceleration.push_back(buff);

	for (int j = 0; j < 5; j++)
	{
		itoa(i.getPress(j).getValue(), buff, 10);
		this->_fingers.push_back(buff);
	}
}
*/
Gesture::Gesture(string fingers[NUM_FINGERS], int commandNumber, string acceleration[NUM_AXIS])
{
	//this->_fingers = new string[NUM_FINGERS];
	//this->_acceleration = new string[NUM_AXIS];
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
Gesture::Gesture(string data[NUM_FINGERS + NUM_AXIS], int commandNumber)
{
	//this->_fingers = new string[NUM_FINGERS];
	//this->_acceleration = new string[NUM_AXIS];
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

Gesture::~Gesture()
{
	//delete this->_fingers;
}
void Gesture::printGesture() const
{
	//cout << "Acceleration: " << this->_acceleration << endl;
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