#pragma once
#include <iostream>
#include <vector>
#define NUM_FINGERS 5
#define NUM_AXIS 3
using namespace std;

class Gesture
{
public:
	Gesture();
	Gesture(string fingers[NUM_FINGERS], int commandNumber, string acceleration[NUM_AXIS]);
	Gesture(string data[NUM_FINGERS + NUM_AXIS], int commandNumber);
	~Gesture();
	void printGesture() const;
	
//private:
	//string* _fingers = new string[NUM_FINGERS];
	vector<string> _fingers;
	int _commandNumber;
	//string* _acceleration = new string[NUM_AXIS];
	vector<string> _acceleration;

};