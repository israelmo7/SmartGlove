#include <vector>
#include "Order.h"


Order::Order(vector<Packet> arr)
{
	this->_arr = arr;
}
Order::~Order()
{

}
int Order::getCommandNumber()
{
	return this->_commandNumber;
}
bool Order::opencloseFinger(int finger, int begin, int end, bool open)
{
	bool flag;
	const int arrLen = (end) ? end : this->_arr.size();

	if (arrLen > 1)
	{
		int i;

		for (i = begin; i < arrLen - 1; i++)
		{
			int a = (open) ? i : i + 1,
				b = (open) ? i + 1 : i;

			if ((_arr[a].getPressure(finger) > _arr[b].getPressure(finger)))
				i = arrLen;

		}
		if (i == arrLen)
			flag = false;
		else
			flag = true;

	}
	else
		flag = false;

	return flag;
}
bool Order::openAndClose(int finger, bool firstOpen)
{
	bool flag;
	int arrLen = this->_arr.size();

	if (arrLen > 2)
	{
		arrLen = this->getValueIndex(finger,firstOpen);

		flag = (this->opencloseFinger(finger, 0, arrLen + 1, firstOpen) && this->opencloseFinger(finger, arrLen, 0, firstOpen));
	}
	else
		flag = false;

	
	return flag;
}
int Order::getValueIndex(int finger, bool small)
{
	const int arrLen = this->_arr.size();
	int index = -1,
		m = (small) ? 100 : 0;

	for (int i = 0; i < arrLen; i++)
	{
		int a = (small) ? _arr[i].getPressure(finger) : m,
			b = (small) ? m : _arr[i].getPressure(finger);

		if (a < b)
		{
			m = _arr[i].getPressure(finger);
			index = i;
		}
	}
	return index;
}