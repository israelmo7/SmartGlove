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
	void setCommandNumber(int c);
	vector<Packet> getArr();
	void packetsArrayToCharsArray(string a[NUM_FINGERS]);
	~Order();

private:


	vector<Packet> _arr;
	int _commandNumber;
};