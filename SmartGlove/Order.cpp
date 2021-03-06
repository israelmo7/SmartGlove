#include "Order.h"
#include "cMoveWindow.h"
#include <string>
#include <fstream>
#include "Mouse.h"

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
		string line;

		while (getline(file, line))
		{
			string tempStr[8] = { "" };
			int commandNumber;
			commandNumber = this->fileLineToStringArray(line, tempStr);
			this->_lines.push_back(new Gesture(tempStr, commandNumber));
		}

		file.close();
	}
	else
		cout << "'"<< PATHFILE << "' File not found\n";// << PATHFILE << "\n";
	
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
	delete _lines[0];
	delete _lines[1];
	delete _lines[2];
	delete _lines[3];
	delete _lines[4];
	delete _lines[5];
	delete _lines[6];
	_lines.resize(0);
}

//checking:
void Order::destroy()
{
	/*int i = 0;
	while (i != _lines.size()){
		_
	}*/
	//cout << &this->_lines << endl;
	delete this->_lines[0];
	delete this->_lines[1];
	delete this->_lines[2];
	delete this->_lines[3];
	delete this->_lines[4];
	delete this->_lines[5];
	delete this->_lines[6];
	//vector<Gesture*> temp;
	//_lines.clear();
	//temp.swap(_lines);
}

void Order::TheComparation(string* infoPackets, string data, SOCKET s)
{

	for (unsigned int i = 0; i < this->_lines.size(); i++)
	{
		vector<string> line;
		line.reserve(NUM_FINGERS + NUM_AXIS);
		line.insert(line.end(), this->_lines[i]->_fingers.begin(), this->_lines[i]->_fingers.end());
		line.insert(line.end(), this->_lines[i]->_acceleration.begin(), this->_lines[i]->_acceleration.end());

		if (sameChecks(line, infoPackets))
		{
			this->runCommand(this->_lines[i]->_commandNumber, data, s);
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

	for (unsigned int i = 3; i < line.length(); i++)
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
	vector<string> a	  - the first
	string b[NUM_FINGERS] - the seconed
	Output:
	true if same and false if not.
	*/
bool Order::sameChecks(vector<string> a, string b[NUM_FINGERS])
{
	for (int i = 0; i < NUM_FINGERS + NUM_AXIS; i++)
	{
		if (a[i] != b[i] && a[i] !=	"")
			return false;
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
void Order::runCommand(int c, string data, SOCKET s)
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
	case MOUSEMODE:
	{
		printf("Change to 'Mouse Mode' \n");
		Mouse m = Mouse(s, data);
		break;
	}
	case DRAGMODE:
	{
		printf("Change to 'Drag Mode' \n");
		cMoveWindow c = cMoveWindow(s, data);
		break;
	}
	case MSGBOX:
	{
		if (!MessageBoxA(NULL, data.c_str(), "SmartGlove", MB_OK))
		{
			cout << "Error with MessageBox. error " << GetLastError() << "\n";
		}
		break;
	}
	default:
		printf("The command not found\n");
		break;
	}
}
/*
	The Function sends input to the computer (simulate)
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

/*
	This function is used to print the lines.
	Input:
		none.
	Output:
		prints the lines.
*/
void Order::printLines()
{
	for (unsigned int i = 0; i < this->_lines.size(); i++)
	{
		cout << "Gesture - " <<  i + 1 << endl;
		this->_lines[i]->printGesture();
	}
}