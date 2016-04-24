#include "Interpreter.h"
#include "Order.h"
#include <fstream>
#include <string>



/*
	Ctor.
	Input:
		none
	Output:
		none
*/
Interpreter::Interpreter()
{
	this->_first = true;
	for (short int i = 0; i < NUM_FINGERS; i++)
		this->_equalsSeq[i] = '0';
}
/*
	Ctor.
	Input:
		p - The first InfoPacket in the InfoPacket list.
	Output:
		none
*/
Interpreter::Interpreter(InfoPacket p)
{
	this->_first = true;
	this->_lastPacket = p;

	for (short int i = 0; i < NUM_FINGERS; i++)
		this->_equalsSeq[i] = '0';

}

/*
	Dtor.
	Input:
		none
	Output:
		none
*/
Interpreter::~Interpreter()
{
	//
}

/*
	The function adds p(InfoPacket) to the InfoPacket list.
	Input:
		p - InfoPacket.
	Output:
		none
*/
bool Interpreter::addInfoPacket(InfoPacket p)
{
	bool retValue = this->InfoPacketsArrayToCharsArray(p);
	this->_lastPacket = p;

	return retValue;
}

/*
	The function prints the InfoPackets.
	Input:
		none
	Output:
		none
*/
void Interpreter::InfoPacketsDetails()
{
	for (unsigned int i = 0; i < NUM_FINGERS; i++)
	{
		cout << i+1 << ") " << this->_symbol[i] << endl;
	}
}

/*
	The function clear the interpreter
	Input:
		none
	Output:
		none
*/
void Interpreter::clearAll()
{
	for (int i = 0; i < NUM_FINGERS; i++)
	{
		this->_equalsSeq[i] = '0';
		this->_symbol[i].clear();
	}
	this->_first = true;
	//this->_lastPacket = 
}

/*
	This Function change the InfoPacket array to char array.
	*	if the values in some finger is 90 , 80 , 70 , 60.
		then i see "jump" of negative and i write in the char array, - - -
	*	if the values in some finger is 60, 75, 83, 92
		then i see "jump" of postivie and i write in the char array, + + +
	*	if the values in some finger is 90 , 90 , 90 , 90.
		then i see "jump" of 0 and i write in the char array, = = =
	*	if the values in some finger is 60, 75, 75, 50
		then i see several positive jump, zero jump and negative jump and i write in the char array, + = -
	*	if the value of a certain axis (x/y/z) is increasing/decreasing
		then for each axis, if it increasing/decreasing it will change for example:
		if in X axis the values are 30, 40, 70, 100 then the char for this axis would be 'f' [forward]

	Input:
		string a[NUM_FINGERS] - Save here the chars array.
	Output:
		none
*/

bool Interpreter::InfoPacketsArrayToCharsArray(InfoPacket newPacket)
{
	if (this->_first)
	{
		this->_first = false;
		return false;
	}
	for (unsigned int i = 0; i < NUM_FINGERS; i++)
	{
		//if (this->_equalsSeq[i] > '3')
		//{
		//	this->_equalsSeq[i] = '3';
		//}
		int sum = this->_lastPacket.getPress(i).getValue() - newPacket.getPress(i).getValue();

		if (sum > 0)
		{
			this->_equalsSeq[i] = '0';

			if (this->_symbol[i].length())
			{
				if (this->_symbol[i][this->_symbol[i].length() - 1] != '-')
					this->_symbol[i].push_back('-');
			}
			else
				this->_symbol[i].push_back('-');
		}
		else if (sum < 0)
		{
			this->_equalsSeq[i] = '0';

			if (this->_symbol[i].length())
			{
				if (this->_symbol[i][this->_symbol[i].length() - 1] != '+')
					this->_symbol[i].push_back('+');
			}
			else
				this->_symbol[i].push_back('+');
		}
		else
		{
			this->_equalsSeq[i] += 1;
			if (this->_symbol[i].length())
			{
				if (this->_symbol[i][this->_symbol[i].length() - 1] != '=')
				{
					this->_symbol[i].push_back('=');
				}
			}
		}
	}
	
	int axis[AXIS], newAxis[AXIS];
	this->_lastPacket.getGyro().getVal(axis);
	newPacket.getGyro().getVal(newAxis);
	int axisSum[AXIS] = { axis[0] - newAxis[0], axis[1] - newAxis[1], axis[2] - newAxis[2] };
	//Check for X axis:
	if (axisSum[0] > 0){
		_gyroSymbol[0]->push_back('f');
	}
	else if(axisSum[0] < 0){
		_gyroSymbol[0]->push_back('b');
	}
	else{
		_gyroSymbol[0]->push_back(' ');
	}
	//Check for Y axis:
	if (axisSum[1] > 0){
		_gyroSymbol[1]->push_back('l');
	}
	else if (axisSum[1] < 0){
		_gyroSymbol[1]->push_back('r');
	}
	else{
		_gyroSymbol[1]->push_back(' ');
	}
	//Check for Z axis:
	if (axisSum[2] > 0){
		_gyroSymbol[2]->push_back('u');
	}
	else if (axisSum[2] < 0){
		_gyroSymbol[2]->push_back('d');
	}
	else{
		_gyroSymbol[2]->push_back(' ');
	}

	if(this->checkToEnd())
	{
		for (int i = 0; i < NUM_FINGERS; i++)
		{
			if (this->_symbol[i].length() > 1)
				this->_symbol[i].pop_back();
		}
		for (int i = 0; i < AXIS; i++){
			if (_gyroSymbol[i]->length() > 1){
				_gyroSymbol[i]->pop_back();
			}
		}
		return true;
	}
	return false;
}
void Interpreter::saveTheSymbol(string arr[NUM_FINGERS])
{
	for (unsigned int i = 0; i < NUM_FINGERS; i++)
	{
		arr[i] = this->_symbol[i];
	}
}
bool Interpreter::checkToEnd()
{
	for (unsigned int i = 0; i < NUM_FINGERS; i++)
	{
		if (this->_equalsSeq[i] < '3')
			return false;
	}
	return true;
}
void Interpreter::showSeq()
{
	for (int i = 0; i < NUM_FINGERS; i++)
	{
		cout << i+1 << ") " << this->_equalsSeq[i] << "\n";
	}
}