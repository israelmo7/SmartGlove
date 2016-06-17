#include "InfoPacket.h"
#define SIZE_OF_VALUE 2
#define BIG_OR_NOT(a, b) ((a > b)? "+" : "-")
#define SAME_OR_NOT(a,b) ((a == b)? "": BIG_OR_NOT(a,b))

InfoPacket::InfoPacket()
{
	for (unsigned int i = 0; i < NUM_FINGERS; i++)
	{
		this->_pressFingers[i] = 0;
	}
	this->_gyroFingers.setValues("         ");
}
/*
Ctor.
Input:
str - containing all the values (gyro and pressure).
P = [4 digits] = "-001"
G = [12 digits] = [(4 digits)(4 digits)(4 digits)] = [(x)(Y)(z)] = "-001+123+856-987"
1 - 5 = five fingers.
4*5+12=32
Output:
none
*/
InfoPacket::InfoPacket(string str)
{
	//cout << str.substr(0, 4).c_str() << "\n";
	//cout << str.substr(4, 4).c_str() << "\n";
	//cout << str.substr(8, 4).c_str() << "\n";
	//cout << str.substr(12, 4).c_str() << "\n";
	//cout << str.substr(16, 4).c_str() << "\n";
	//cout << str.substr(20, 12).c_str() << "\n";

	try
	{
		//P(1-5)
		this->_pressFingers[0] = atoi(str.substr(0, SIZE_OF_VALUE).c_str());     // P1
		this->_pressFingers[1] = atoi(str.substr(2, SIZE_OF_VALUE).c_str());     // P2
		this->_pressFingers[2] = atoi(str.substr(4, SIZE_OF_VALUE).c_str());     // P3
		this->_pressFingers[3] = atoi(str.substr(6, SIZE_OF_VALUE).c_str());     // P4
		this->_pressFingers[4] = atoi(str.substr(8, SIZE_OF_VALUE).c_str());    // P5
	}
	catch (exception& e)
	{
		cout << "Convert pressure values from String to Int failed with error : " << e.what() << endl;
	}
	//G(1-5)
	this->_gyroFingers.setValues(str.substr(10 , 9).c_str());     // G1

}

/*
Dtor.
Input:
none
Output:
none
*/
InfoPacket::~InfoPacket()
{

}

/*
The functios prints the details about every finger.
Input:
none
Output:
none
*/
void InfoPacket::showDetails() const
{
	cout << "Accelerometer: \n" << _gyroFingers.getValues().c_str();
	cout << "Finger 1: \nPressure = " << _pressFingers[0].getValue() << "%\n";
	cout << "Finger 2: \nPressure = " << _pressFingers[1].getValue() << "%\n";
	cout << "Finger 3: \nPressure = " << _pressFingers[2].getValue() << "%\n";
	cout << "Finger 4: \nPressure = " << _pressFingers[3].getValue() << "%\n";
	cout << "Finger 5: \nPressure = " << _pressFingers[4].getValue() << "%\n";
}

Gyro InfoPacket::getGyro() const
{
	return this->_gyroFingers;
}

Pressure InfoPacket::getPress(int fingerNum) const
{
	Pressure pValue;

	if (fingerNum >= 0 && fingerNum < NUM_FINGERS)
	{
		pValue = this->_pressFingers[fingerNum];
	}
	else
	{
		pValue = NULL;
	}

	return pValue;
}
Gesture InfoPacket::operator-(InfoPacket other) const
{
	Gesture* g = new Gesture();
	char buff[5];
	for (int i = 0; i < NUM_AXIS; i++){
		 _itoa_s(this->_gyroFingers.getVal(i) - other._gyroFingers.getVal(i), buff, 10);
		 for (unsigned int j = 0; j < strlen(buff); j++){
			 g->_acceleration[i].push_back(buff[j]);
		 }
	}
	for (int i = 0; i < NUM_FINGERS; i++){
		_itoa_s(this->_pressFingers[i].getValue() - other._pressFingers[i].getValue(), buff, 10);
		for (unsigned int j = 0; j < strlen(buff); j++){
			g->_fingers[i].push_back(buff[j]);
		}
	}
	//delete buff;
	/*g._acceleration[0] = (SAME_OR_NOT(arrOne[0], arrTwo[0]));
	g._acceleration[1] = (SAME_OR_NOT(arrOne[1], arrTwo[1]));
	g._acceleration[2] = (SAME_OR_NOT(arrOne[2], arrTwo[2]));


	g._fingers[0] = (SAME_OR_NOT(this->getPress(0).getValue(), other.getPress(0).getValue()));
	g._fingers[1] = (SAME_OR_NOT(this->getPress(1).getValue(), other.getPress(1).getValue()));
	g._fingers[2] = (SAME_OR_NOT(this->getPress(2).getValue(), other.getPress(2).getValue()));
	g._fingers[3] = (SAME_OR_NOT(this->getPress(3).getValue(), other.getPress(3).getValue()));
	g._fingers[4] = (SAME_OR_NOT(this->getPress(4).getValue(), other.getPress(4).getValue()));*/


	return *g;
}