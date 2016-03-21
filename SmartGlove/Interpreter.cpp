#include "Interpreter.h"
#include "Order.h"
#include <fstream>
#include <string>

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
#define X			 1
#define Y			 2
#define Z			 3

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
		printf("The command not found\n");
		break;
	}
}
/*
	The function starts the translation
	Input:
		none
	Output:
		none
*/
void Interpreter::begin()
{
	string fingerState[NUM_FINGERS+1];

	Order o = Order(this->_packetsList);
	o.packetsArrayToCharsArray(fingerState);
	char gyroXState = o.gyroToChar(X);
	char gyroYState = o.gyroToChar(Y);
	char gyroZState = o.gyroToChar(Z);

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

			this->fileLineToStringArray(a, line);

			if (sameChecks(fingerState,a))
			{
				int c = atoi(a[0].c_str());
				o.setCommandNumber(c);
			}
			
		}

		file.close();
	}
	else
	{
		cout << "Cant find the Profile file \n";
	}


	//
	this->runCommand(o.getCommandNumber());
}
/*
	The Functionsend input to the computer (simulate)
	Input:
		WORD vk - the Virtual Key you want to send
	Output:
		bool - true if success and false if not
*/
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

/*
	The Function get the values from the line and save it in 'a'
	Input:
		string a[NUM_FINGERS+1] - 5 fingers pressure[0-4] and  one "gyro"[5]
		string line - the line from the text file
	Output:
		none
*/
void Interpreter::fileLineToStringArray(string a[NUM_FINGERS + 1], string line)
{
	int cnt = 0;

	for (unsigned int i = 3; i < line.length()-1; i++)
	{
		if (line[i] == '*')
		{
			cnt++;
		}
		else
		{
			if (a[cnt].length() == 1 && a[cnt][0] == ' ')
			{
				a[cnt][0] = line[i];
			}
			else
			{
				a[cnt].push_back(line[i]);
			}
		}
	}
}
/*
	The Function checks if the strings array are the same
	Input:
		string a[NUM_FINGERS] - number one
		string b[NUM_FINGERS] - number two
	Output:
		bool - true if same and false if not.
*/
bool Interpreter::sameChecks(string a[], string b[])
{
	for (int i = 0; i < NUM_FINGERS+1; i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}