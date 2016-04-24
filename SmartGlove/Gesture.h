#include <iostream>
#define NUM_FINGERS 5
using namespace std;

class Gesture
{
public:
	Gesture();
	Gesture(string fingers[NUM_FINGERS], int commandNumber, string acceleration);
	~Gesture();
	void printGesture();

	//private:
	string* _fingers = new string[NUM_FINGERS];
	int _commandNumber;
	string _acceleration;

};
