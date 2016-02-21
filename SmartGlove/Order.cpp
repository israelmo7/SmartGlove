#include <vector>
#include "Order.h"

#define MINSPEEDMOVE 0
#define FINSPEEDMOVE 70
#define MAXSPEEDMOVE 100

/*
	Ctor.
	Input:
		arr - array of Packets.
	Output:
		none
*/
Order::Order(vector<Packet> arr)
{
	this->_arr = arr;
	this->_commandNumber = 9;
}

/*
	Dtor.
	Input:
		none
	Output:
		none
*/
Order::~Order()
{

}

/*
	The function Return the CommandNumber.
	Input:
		none
	Output:
		int - the comamndNumber
*/
int Order::getCommandNumber()
{
	return this->_commandNumber;
}

/*
	This Function change the packet array to char array.
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
void Order::packetsArrayToCharsArray(string a[NUM_FINGERS])
{
	for (int j = 0; j < NUM_FINGERS; j++)
	{
		int count = 0;
		for (unsigned int i = 0; i < this->_arr.size() - 1; i++)
		{
			int sum = this->_arr[i].getPress(j)->getValue() - this->_arr[i + 1].getPress(j)->getValue();

			if (sum > 0) // _arr[i] > _arr[i+1]
			{
				if (i)
				{
					if (a[j][i - 1] != '-')
						a[j].push_back('-');
				}
				else
					a[j].push_back('-');
			}
			else if (sum < 0) // _arr[i] < _arr[i+1]
			{
				if (i)
				{
					if (a[j][i - 1] != '+')
						a[j].push_back('+');
				}
				else
					a[j].push_back('+');
			}
			else // _arr[i] == _arr[i+1]
			{
				if (i)
				{
					if (a[j][i - 1] != '=')
						a[j].push_back('=');
				}
				else
					a[j].push_back('=');
			}
		}
	}
}
/*
	This Function set the command number
	Input:
		int c - the command number
	Output:
		none
*/
void Order::setCommandNumber(int c)
{
	this->_commandNumber = c;
}