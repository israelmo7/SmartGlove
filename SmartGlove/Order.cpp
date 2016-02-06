#include <vector>
#include "Order.h"

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
	this->_commandNumber = 0;
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
The function return the smaller or the higher value in the array.
Input:
int finger - the number of the finger [0-4]
bool small - if True - it return the smallest value, else - the higher value.
Output:
bool - check if it True.
*/
int Order::getValueIndex(int finger, bool smaller)
{
	const int arrLen = this->_arr.size();
	int index = -1,
		m = (smaller) ? 100 : 0;

	for (int i = 0; i < arrLen; i++)
	{
		int a = (smaller) ? _arr[i].getPress(finger)->getValue() : m,
			b = (smaller) ? m : _arr[i].getPress(finger)->getValue();

		if (a < b)
		{
			m = _arr[i].getPress(finger)->getValue();
			index = i;
		}
	}
	return index;
}

vector<Packet> Order::getArr()
{
	return _arr;
}