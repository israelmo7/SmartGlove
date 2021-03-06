#include "Interpreter.h"
#include "Properties.h"
#define STR(x) #x
#define CHECK_FIRST_PRESS _lastPacket.getPress(0).getValue()==0 && _lastPacket.getPress(1).getValue()== 0 && _lastPacket.getPress(2).getValue()==0 && _lastPacket.getPress(3).getValue()==0 && _lastPacket.getPress(4).getValue()==0

int EQUAL_NUM = 15;
int MAX_OFFSET = 0;
int MAX_ACCEL_OFFSET = 0;
/*
	Ctor.
	Input:
		none
	Output:
		none
*/
Interpreter::Interpreter()
{
	Properties p = Properties();
	MAX_OFFSET = p.getValueByName(STR(MAX_OFFSET));
	MAX_ACCEL_OFFSET = p.getValueByName(STR(MAX_ACCEL_OFFSET));
	EQUAL_NUM = p.getValueByName(STR(EQUAL_NUM));

	//this->_stateA = NONE;
	this->_lastPacket = InfoPacket();
	for (short int i = 0; i < NUM_FINGERS; i++)
		this->_equalsSeq[i] = 0;
}
/*
	Ctor.
	Input:
		p - The first InfoPacket in the InfoPacket list.
	Output:
		none
*/
Interpreter::Interpreter(InfoPacket p)
{
	//this->_stateA = NONE;
	this->_lastPacket = p;

	for (short int i = 0; i < NUM_FINGERS; i++)
		this->_equalsSeq[i] = 0;

}

/*
	Dtor.
	Input:
		none
	Output:
		none
*/
Interpreter::~Interpreter()
{
	//
}

/*
	The function adds p(InfoPacket) to the InfoPacket list.
	Input:
		p - InfoPacket.
	Output:
		none
*/
bool Interpreter::addInfoPacket(InfoPacket p)
{
	bool retValue;

	retValue = this->InfoPacketsArrayToCharsArray(p);
	this->_lastPacket = p;

	return retValue;
}

/*
	The function prints the InfoPackets.
	Input:
		none
	Output:
		none
*/
void Interpreter::InfoPacketsDetails()
{
	cout << "Flex and Gyro Values: \n";
	for (unsigned int i = 0; i < NUM_FINGERS + NUM_AXIS; i++)
	{
		cout << i+1 << ") " << this->_ranges[i].c_str() << endl;
	}
	//OR
	//this->_rangess.printGesture();
}

/*
	The function clear the interpreter
	Input:
		none
	Output:
		none
*/
void Interpreter::clearAll()
{
	for (int i = 0; i < NUM_FINGERS + NUM_AXIS; i++)
	{
		this->_equalsSeq[i%NUM_FINGERS] = 0;
		this->_ranges[i].clear();
	}
	//OR
	//this->_rangess.clearAll();
	this->_lastPacket = InfoPacket();
}

/*
	This Function change the InfoPacket array to char array.
	*	if the values in some finger is 90 , 80 , 70 , 60.
		then i see "jump" of negative and i write in the char array, - - -
	*	if the values in some finger is 60, 75, 83, 92
		then i see "jump" of postivie and i write in the char array, + + +
	*	if the values in some finger is 90 , 90 , 90 , 90.
		then i see "jump" of 0 and i write in the char array, = = =
	*	if the values in some finger is 60, 75, 75, 50
		then i see several positive jump, zero jump and negative jump and i write in the char array, + = -

		//EDIT:
		same shit but with values and not rangess.

	Input:
		string a[NUM_FINGERS] - Save here the chars array.
	Output:
		none
*/

bool Interpreter::InfoPacketsArrayToCharsArray(InfoPacket newPacket)
{
	this->calculateRanges(newPacket);

	return this->checkToEnd();
}
void Interpreter::saveTheRanges(string *arr)
{
	for (unsigned int i = 0; i < NUM_FINGERS + NUM_AXIS; i++)
	{
		arr[i] = this->_ranges[i];
	}
	//OR
	//gesture = this->_rangess;
}
bool Interpreter::checkToEnd()
{
	for (unsigned int i = 0; i < NUM_FINGERS; i++)
	{
		if (this->_equalsSeq[i] < EQUAL_NUM)
			return false;
	}
	return true;
}
void Interpreter::showSeq()
{
	cout << "Flex Sequance: \n";
	for (int i = 0; i < NUM_FINGERS; i++)
	{
		cout << i + 1 << ") " << this->_equalsSeq[i] << "\n";
	}

}
void Interpreter::calculateRanges(InfoPacket newPacket)
{
	int checkFirst[3];
	_lastPacket.getGyro().getVal(checkFirst);
	if (!(checkFirst[0] == 0 && checkFirst[1] == 0 && checkFirst[2] == 0 && CHECK_FIRST_PRESS)){
		for (unsigned int i = 0; i < NUM_FINGERS + NUM_AXIS; i++)
		{
			int sum = 0;
			if (i < NUM_FINGERS){
				sum = this->_lastPacket.getPress(i).getValue() - newPacket.getPress(i).getValue();
				if (sum >= MAX_OFFSET || sum <= -MAX_OFFSET) // New different from Old
				{
					this->_equalsSeq[i] = 0;
					char offset[3];
					int ranges = valueRange(newPacket.getPress(i).getValue());
					_itoa_s(ranges, offset, 10);
					this->_ranges[i].append(offset);
				}
				else
				{
					this->_equalsSeq[i] += 1;
					this->_equalsSeq[i] = (this->_equalsSeq[i] > EQUAL_NUM) ? EQUAL_NUM : this->_equalsSeq[i];
				}
			}
			else{
				sum = this->_lastPacket.getGyro().getVal(i - NUM_FINGERS) - newPacket.getGyro().getVal(i - NUM_FINGERS);
				if (sum >= MAX_ACCEL_OFFSET || sum <= -MAX_ACCEL_OFFSET){ // New different from Old
					this->_equalsSeq[i] = 0;
					char offset[3];
					int ranges = valueRange(newPacket.getGyro().getVal(i - NUM_FINGERS), true);
					_itoa_s(ranges, offset, 10);
					this->_ranges[i].append(offset);
				}
				else
				{
					this->_equalsSeq[i] += 1;
					this->_equalsSeq[i] = (this->_equalsSeq[i] > EQUAL_NUM) ? EQUAL_NUM : this->_equalsSeq[i];
				}
			}
		}
	}
	else{
		for (unsigned int i = 0; i < NUM_FINGERS + NUM_AXIS; i++){
			char offset[3];

			if (i < NUM_FINGERS){
				int ranges = valueRange(newPacket.getPress(i).getValue());
				_itoa_s(ranges, offset, 10);
				this->_ranges[i].append(offset);
			}
			else{
				int ranges = valueRange(newPacket.getGyro().getVal(i - NUM_FINGERS), true);
				/*if (ranges > 0){
					ranges = ranges / MAX_GYRO_OFFSET + 1;
				}
				else if (ranges < 0){
					ranges = ranges / MAX_GYRO_OFFSET - 1;
				}*/
				_itoa_s(ranges, offset, 10);
				this->_ranges[i].append(offset);
			}
		}
	}
}

int Interpreter::valueRange(int value, bool accel)
{
	Properties p = Properties();
	int offset = (accel) ? p.getValueByName(STR(MAX_ACCEL_OFFSET)) : p.getValueByName(STR(MAX_OFFSET));

	if (value > 0){

		for (int i = 0; i < (100 / offset); i++){
			if (value >= i*offset && value <= i*offset + offset - 1){
				return i + 1;
			}
		}
	}
	else if (value < 0){
		for (int i = 0; i > -(100 / offset); i--){
			if (value <= -i*offset && value >= -(i*offset + offset - 1)){
				return i - 1;
			}
		}
	}
	return 0;
}