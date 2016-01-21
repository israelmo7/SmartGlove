#pragma once
#include <iostream>
#include <vector>
#include "Packet.h"

using namespace std;

class Order
{
public:
	Order(vector<Packet> arr);
	int getCommandNumber();

	bool opencloseFinger(int finger, int begin = 0, int end = 0, bool open = true);
	bool openAndClose(int finger, bool firstOpen = true);


	~Order();

private:

	int getValueIndex(int finger, bool small = true);

	vector<Packet> _arr;
	int _commandNumber;
};