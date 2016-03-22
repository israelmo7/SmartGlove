#include "Interpreter.h"

/*
	Ctor.
	Input:
		p - The first Packet in the packet list.
	Output:
		none
*/
Interpreter::Interpreter(Packet p)
{
	this->_packetsList.push_back(p);
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
	The function adds p(Packet) to the packet list.
	Input:
		p - packet.
	Output:
		none
*/
void Interpreter::addPacket(Packet p)
{
	this->_packetsList.push_back(p);
}

/*
	The function prints the packets.
	Input:
		none
	Output:
		none
*/
void Interpreter::packetsDetails()
{
	int cnt = 1;
	for each (Packet i in this->_packetsList)
	{
		cout << "Packet " << cnt++ << ": \n";
		i.showDetails();
		cout << endl;
	}
}

/*
	The function starts the translation
	Input:
		none
	Output:
		none
*/
string* Interpreter::begin()
{
	string fingerState[NUM_FINGERS+1];

	Functions funcs = Functions(this->_packetsList);
	funcs.packetsArrayToCharsArray(fingerState);
	char gyroXState = funcs.gyroToChar(X);
	char gyroYState = funcs.gyroToChar(Y);
	char gyroZState = funcs.gyroToChar(Z);

	fingerState[NUM_FINGERS] = gyroXState;
	//
	ifstream file;
	file.open("Profile.txt");

	if (file.is_open())
	{

		string line;

		while (getline(file,line))
		{
			string a[NUM_FINGERS + 1] = { " " };
			funcs.fileLineToStringArray(a, line);

			if (funcs.sameChecks(fingerState, a) && a[5] == )
			{
				int c = atoi(a[0].c_str());
				funcs.setCommandNumber(c);
			}
			
		}

		file.close();
	}
	else
	{
		cout << "Cant find the Profile file \n";
	}


	//
	funcs.runCommand(funcs.getCommandNumber());
	return fingerState;
}