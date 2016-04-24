#include "Interpreter.h"
#include "Order.h"
#include <fstream>
#include <string>

#define GRAVITY 9
#define  ZERO    0

#define CHECK_ZERO(a, b) ((a || b)? false: true)
#define CHECK_GRAVITY(c) ((c == GRAVITY)? true: false)

/*
	Ctor.
	Input:
		none
	Output:
		none
*/
Interpreter::Interpreter()
{
	this->_stateA = "n";
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
	this->_stateA = "n";
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
		cout << i+1 << ") " << this->_symbolF[i] << endl;
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
		this->_symbolF[i].clear();
	}
	this->_stateA.clear();
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

			if (this->_symbolF[i].length())
			{
				if (this->_symbolF[i][this->_symbolF[i].length() - 1] != '-')
					this->_symbolF[i].push_back('-');
			}
			else
				this->_symbolF[i].push_back('-');
		}
		else if (sum < 0)
		{
			this->_equalsSeq[i] = '0';

			if (this->_symbolF[i].length())
			{
				if (this->_symbolF[i][this->_symbolF[i].length() - 1] != '+')
					this->_symbolF[i].push_back('+');
			}
			else
				this->_symbolF[i].push_back('+');
		}
		else
		{
			this->_equalsSeq[i] += 1;
			if (this->_symbolF[i].length())
			{
				if (this->_symbolF[i][this->_symbolF[i].length() - 1] != '=')
				{
					this->_symbolF[i].push_back('=');
				}
			}
		}
	}

	this->checkAccel(newPacket);
	
	if (this->checkToEnd())
	{
		for (int i = 0; i < NUM_FINGERS; i++)
		{
			if (this->_symbolF[i].length() > 1)
				this->_symbolF[i].pop_back();
		}
		return true;
	}
	return false;
}
void Interpreter::saveTheSymbol(string *arr)
{
	for (unsigned int i = 0; i < NUM_FINGERS; i++)
	{
		arr[i] = this->_symbolF[i];
	}
	arr[5] = this->_stateA;
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
		cout << i + 1 << ") " << this->_equalsSeq[i] << "\n";
	}

}
void Interpreter::checkAccel(InfoPacket pack)
{
	int val[3];
	pack.getGyro().getVal(val);

	if (CHECK_ZERO(val[1], val[2]) && CHECK_GRAVITY(val[0]))
	{
		this->_stateA = "";
	}
	else if (CHECK_ZERO(val[0], val[2]) && CHECK_GRAVITY(val[1]))
	{
		this->_stateA = "";
	}
	else if ((CHECK_ZERO(val[0], val[1]) && CHECK_GRAVITY(val[2])))
	{
		this->_stateA = "";
	}
	else
	{
		this->_stateA = "";
	}

}
