#include <vector>
#include "Order.h"
#include <string>
#include <fstream>

#define MINSPEEDMOVE 0
#define FINSPEEDMOVE 70
#define MAXSPEEDMOVE 100
#define PATHFILE "Profile.txt"

/*
	Ctor.
	Input:
		arr - array of InfoPackets.
	Output:
		none
*/
Order::Order()
{
	ifstream file;
	
	file.open(PATHFILE);

	if (file.is_open())
	{
		int cnt = 0;
		string line;

		while (getline(file, line))
		{
			string tempStr[6] = {""};
			int commandNumber;
			commandNumber = this->fileLineToStringArray(line, tempStr);
			this->_lines.push_back(new Gesture(tempStr, commandNumber, "n"));
		}

		file.close();
	}
	else
		cout << "Can not open this File - " << PATHFILE << "\n";
	
}

/*
	Dtor.
	Input:
		none
	Output:
		none
*/
Order::~Order()
{
	/*for (unsigned int i = 0; i < this->_lines.size();i++)
	{
		delete this->_lines[i];
	}*/
}


void Order::TheComparetion(string* infoPackets)
{

	for (unsigned int i = 0; i < this->_lines.size(); i++)
	{
		cout << infoPackets[5] << " - " << this->_lines[i]->_acceleration << endl;
		if (sameChecks(this->_lines[i]->_fingers, infoPackets) && infoPackets[5] == this->_lines[i]->_acceleration)
		{
			this->runCommand(this->_lines[i]->_commandNumber);
		}
	}
}
/*
	The Function get the values from the line and save it in 'a'
	Input:
		string a[NUM_FINGERS+1] - 5 fingers pressure[0-4] and  one "gyro"[5]
		string line - the line from the text file
	Output:
		int - the command
*/
int Order::fileLineToStringArray(string line, string* save)
{
	int cnt = 0;

	for (unsigned int i = 3; i < line.length() - 1; i++)
	{
		if (line[i] == '*')
		{
			cnt++;
		}
		else
		{
			if (save[cnt].length() == 1 && save[cnt][0] == ' ')
			{
				save[cnt][0] = line[i];
			}
			else
			{
				save[cnt].push_back(line[i]);
			}
		}
	}
	return atoi(line.substr(0, 3).c_str());
}
/*
	The function checks if both sames.
	Input:
		string a[NUM_FINGERS] - the first
		string b[NUM_FINGERS] - the seconed
	Output:
		true if same and false if not.
*/
bool Order::sameChecks(string a[NUM_FINGERS], string b[NUM_FINGERS])
{
	for (int i = 0; i < NUM_FINGERS; i++)
	{
//		cout << a[i] << " == " << b[i] << "\n";
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}
/*
	The function runs the command by the int 'c'
	Input:
		int c - the serial command number
	Output:
		none
*/
void Order::runCommand(int c)
{
	switch (c)
	{

	case PAGE_UP:
		printf("%s\n", (sendInput(VK_PRIOR)) ? "Page up success" : "Page up failed");
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
	The Functionsend input to the computer (simulate)
	Input:
		WORD vk - the Virtual Key you want to send
	Output:
		bool - true if success and false if not
*/
bool Order::sendInput(WORD vk)
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
void Order::printLines()
{
	for (unsigned int i = 0; i < this->_lines.size(); i++)
	{
		cout << "Gesture - " <<  i + 1 << endl;
		this->_lines[i]->printGesture();
	}
}