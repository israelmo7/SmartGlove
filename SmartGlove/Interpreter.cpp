#include "Interpreter.h"
#include "Order.h"

#define PAGE_UP      0
#define PAGE_DOWN    1
#define REFRESH		 2
#define SNAPSHOT	 3
#define PSMUSIC		 4
#define PSONG		 5
#define NSONG		 6
#define BPAGE		 7
#define FPAGE		 8
#define VOLUMEM		 9
#define VOLUMEU		 10
#define VOLUMED		 11

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
void Interpreter::runCommand(int c)
{
	switch (c)
	{
	case PAGE_UP:
		printf("%s\n",(sendInput(VK_PRIOR))?"Page up success":"Page up failed");
		break;

	case PAGE_DOWN:
		printf("%s\n", (sendInput(VK_NEXT)) ? "Page down success" : "Page down failed");
		break;

	case REFRESH:
		printf("%s\n", (sendInput(VK_F5)) ? "Refresh success" : "Refresh failed");
		break;

	case SNAPSHOT:
		printf("%s\n", (sendInput(VK_SNAPSHOT)) ? "PrintScreen success" : "PrintScreen failed");
		break;
		
	case PSMUSIC:
		printf("%s\n", (sendInput(VK_MEDIA_PLAY_PAUSE)) ? "ToggleMusic success" : "ToggleMusic failed");
		break;
		
	case PSONG:
		printf("%s\n", (sendInput(VK_MEDIA_PREV_TRACK)) ? "PreviousSong success" : "PreviousSong failed");
		break;

	case NSONG:
		printf("%s\n", (sendInput(VK_MEDIA_NEXT_TRACK)) ? "NextSong success" : "NextSong failed");
		break;

	case BPAGE:
		printf("%s\n", (sendInput(VK_BROWSER_BACK)) ? "PreviousPage success" : "PreviousPage failed");
		break;

	case FPAGE:
		printf("%s\n", (sendInput(VK_BROWSER_FORWARD)) ? "ForwardPage success" : "ForwardPage failed");
		break;

	case VOLUMEM:
		printf("%s\n", (sendInput(VK_VOLUME_MUTE)) ? "MuteVolume success" : "MuteVolume failed");
		break;

	case VOLUMEU:
		printf("%s\n", (sendInput(VK_VOLUME_UP)) ? "UpVolume success" : "UpVolume failed");
		break;

	case VOLUMED:
		printf("%s\n", (sendInput(VK_VOLUME_DOWN)) ? "DownVolume success" : "DownVolume failed");
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
bool Interpreter::sendInput(WORD vk)
{
	INPUT i;
	i.type = INPUT_KEYBOARD;
	i.ki.wScan = 0;
	i.ki.time = 5000;

	
	i.ki.wVk = vk;

	i.ki.dwExtraInfo = 0;
	i.ki.dwFlags = 0;

	return (SendInput(1, &i, sizeof(INPUT)) != 0);
}