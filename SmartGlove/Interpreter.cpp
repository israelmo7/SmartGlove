#include "Interpreter.h"
#include "Order.h"


#define OPEN_CALC    1
#define OPEN_NOTEPAD 2
#define OPEN_CMD     3

Interpreter::Interpreter(Packet p)
{
	this->_packetsList.push_back(p);
}
Interpreter::~Interpreter()
{
	//
}
void Interpreter::addPacket(Packet p)
{
	this->_packetsList.push_back(p);
}
void Interpreter::orderPackets(string str)
{
	if (str.length() % 65 == 0)
	{
		for (unsigned int i = 0; i < str.length(); i += 65)
		{
			this->addPacket(str.substr(i, 65));
		}

	}
	else
		this->addPacket(Packet(str));
}
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
void Interpreter::runCommand(int i)
{
	switch (i)
	{
	case OPEN_CALC:
		// OPEN CALCULATOR
		break;

	case OPEN_NOTEPAD:
		// OPEN NOTEPAD
		break;

	case OPEN_CMD:
		// OPEN CMD 
		break;

	default:
		break;
	}
}
void Interpreter::begin()
{
	Order o = Order(this->_packetsList);
	this->runCommand(o.getCommandNumber());
}