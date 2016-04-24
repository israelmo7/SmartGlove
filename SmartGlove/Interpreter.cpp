#include "Interpreter.h"
#include "Order.h"
#include <fstream>
#include <string>

#define MIN_GRAVITY			7
#define  MAX_NON_GRAVITY    2

#define X val[0]
#define Y val[1]
#define Z val[2]

#define ABS(a) ((a < 0)? a*-1: a)

#define A_BIGGER_THAN_B(a,b) ((ABS(a) > ABS(b))? true: false)
#define A_BIGGER_THAN_B_AND_C(a,b,c) ((A_BIGGER_THAN_B(a,b) && A_BIGGER_THAN_B(a,c))?true:false)


#define CHECK_NON_GRAVITY(a) ((a > MAX_NON_GRAVITY)? false: true)
#define CHECK_ZERO(a, b) ((CHECK_NON_GRAVITY(ABS(a)) && CHECK_NON_GRAVITY(ABS(b)))? true: false)
#define CHECK_GRAVITY(c) ((ABS(c) > MIN_GRAVITY)? true: false)
#define IS_POSITIVE(a) ((a > 0)? true: false)

/*
	Ctor.
	Input:
		none
	Output:
		none
*/
Interpreter::Interpreter()
{
	this->_stateA = NONE;
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
	this->_stateA = NONE;
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
	//val[0] = x
	//val[1] = y
	//val[2] = z

	int val[3];
	pack.getGyro().getVal(val);

	if (A_BIGGER_THAN_B_AND_C(X,Y,Z))								//(CHECK_ZERO(Y, Z) && CHECK_GRAVITY(X))
	{
		if (IS_POSITIVE(X))
		{
			this->_stateA = PALM_TO_ME;
		}
		else
		{
			this->_stateA = NE_PALM_TO_ME;
		}
	}
	else if (A_BIGGER_THAN_B_AND_C(Y, X, Z))						//(CHECK_ZERO(X, Z) && CHECK_GRAVITY(Y))
	{
		if (IS_POSITIVE(Y))
		{
			this->_stateA = NE_PALM_TO_LEFT;
		}
		else
		{
			this->_stateA = PALM_TO_LEFT;
		}
	}
	else if (A_BIGGER_THAN_B_AND_C(Z, Y, X))						//((CHECK_ZERO(X, Y) && CHECK_GRAVITY(Z)))
	{
		if (IS_POSITIVE(Z))
		{
			this->_stateA = NE_PALM_TO_SKY;
		}
		else
		{
			this->_stateA = PALM_TO_SKY;
		}
	}
}
void Interpreter::showAccel()
{
	switch (this->_stateA[1])
	{
	case 's':
	{
		if (_stateA[0] == '+')
		{
			cout << "Palm to Sky. \n";
		}
		else
		{
			cout << "Palm to Ground. \n";
		}
		break;
	}

	case 'l':
	{
		if (_stateA[0] == '+')
		{
			cout << "Palm to Left. \n";
		}
		else
		{
			cout << "Palm to Right. \n";
		}
		break;
	}

	case 'm':
	{
		if (_stateA[0] == '+')
		{
			cout << "Palm to Me. \n";
		}
		else
		{
			cout << "Palm not to Me. \n";
		}
		break;
	}

	default:
		cout << "None\n";
		break;
	}
}