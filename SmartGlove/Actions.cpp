#include "Actions.h"

/*
	Ctor.
	Input:
		vector<Packet> arr - the packets
	Output:
		none
*/
Actions::Actions(vector<Packet> arr)
{
	this->_order = new Order(arr);
}

/*
	Dtor.
	Input:
		none
	Outpt:
		none
*/
Actions::~Actions()
{
}

void Actions::Action(/*Packet pckt, */int action, int finger, int begin, int end, bool open, bool firstOpen)
{
	switch (action){
	case 1:
		opencloseFinger(finger, begin, end, open);
		break;
	case 2:
		openAndClose(finger, firstOpen);
		break;

	//....More Actions To Come...//

	default:
		break;
	}
}


/*
	The function Checks if the finger open or close.
	Input:
		int finger - the number of the finger [0-4]
		int begin - Where the Check begins
		int end -  the end place check
		bool open - if True - it checks if the finger opend, else - close.
	Output:
		bool - check if it True.
*/
bool Actions::opencloseFinger(int finger, int begin, int end, bool open)
{
	bool flag;
	const int arrLen = (end) ? end : _order->getArr().size();

	if (arrLen > 1)
	{
		int i;

		for (i = begin; i < arrLen - 1; i++)
		{
			int a = (open) ? i : i + 1,
				b = (open) ? i + 1 : i;

			if ((_order->getArr()[a].getPress()->getValue() > _order->getArr()[b].getPress(finger)->getValue()))
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

/*
	The function Checks if the finger (open And close) or (close And open).
	Input:
		int finger - the number of the finger [0-4]
		bool firstOpen - if True - it checks if the finger opendAndClose, else - closeAndOpen.
	Output:
		bool - check if it True.
*/
bool Actions::openAndClose(int finger, bool firstOpen)
{
	bool flag;
	int arrLen = _order->getArr().size();

	if (arrLen > 2)
	{
		arrLen = _order->getValueIndex(finger, firstOpen);

		flag = (this->opencloseFinger(finger, 0, arrLen + 1, firstOpen) && this->opencloseFinger(finger, arrLen, 0, firstOpen));
	}
	else
		flag = false;


	return flag;
}
