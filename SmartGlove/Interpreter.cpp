#include "Interpreter.h"
#include "Order.h"
#include <Windows.h>

#define PAGE_UP      0
#define OPEN_CALC    1
#define OPEN_NOTEPAD 2
#define OPEN_CMD     3


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
The function is executing the appropriate command.
	Input:
		i - the command number
	Output:
		none
*/
void Interpreter::runCommand(int i)
{
	switch (i)
	{
	case PAGE_UP:
		INPUT i;
		i.type = INPUT_KEYBOARD;
		i.ki.wScan = 0;
		i.ki.time = 0;
		i.ki.wVk = VK_PRIOR;
		i.ki.dwExtraInfo = 0;
		i.ki.dwFlags = 0;

		INPUT arr[2];
		arr[0] = i;
		arr[1] = i;
		cout << (SendInput(1, arr, sizeof(INPUT)) ? "Success" : "Failed") << "\n";
		break;

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
/*
	The function starts the translation
	Input:
		i - the command number
	Output:
		none
*/
void Interpreter::begin()
{
	Order o = Order(this->_packetsList);
	this->runCommand(o.getCommandNumber());
}