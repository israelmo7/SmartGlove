#include "Interpreter.h"
#include "Order.h"
#include <Windows.h>

#define PAGE_UP      0
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
void Interpreter::begin()
{
	Order o = Order(this->_packetsList);
	this->runCommand(o.getCommandNumber());
}