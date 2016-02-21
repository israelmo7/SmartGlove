#pragma once
#include <iostream>
#include "Packet.h"
#include "Order.h"
class Actions
{
public:
	Actions(vector<Packet> arr);
	void Action(/*Packet pckt, */int action, int finger = 0, int begin = 0, int end = 0, bool open = 0, bool firstOpen = 0);
	~Actions();
private:
	Order* _order;
	bool opencloseFinger(int finger, int begin, int end, bool open);
	bool openAndClose(int finger, bool firstOpen);
	//TO-DO: ADD MORE ACTIONS.
};

