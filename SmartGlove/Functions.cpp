#include "Functions.h"

/*
	Ctor.
	Input:
		arr - array of Packets.
	Output:
		none
*/
Functions::Functions(vector<Packet> arr)
{
	this->_arr = arr;
	this->_commandNumber = 9;
}

/*
	Dtor.
	Input:
		none
	Output:
		none
*/
Functions::~Functions()
{

}

/*
	The function Return the CommandNumber.
	Input:
		none
	Output:
		int - the comamndNumber
*/
int Functions::getCommandNumber()
{
	return this->_commandNumber;
}

/*
	This Function change the packet array to char array.
	*	if the values in some finger is 90 , 80 , 70 , 60.
		then i see "jump" of negative and i write in the char array, - - - 
	*	if the values in some finger is 60, 75, 83, 92
		then i see "jump" of postivie and i write in the char array, + + + 
	*	if the values in some finger is 90 , 90 , 90 , 90.
		then i see "jump" of 0 and i write in the char array, = = = 
	*	if the values in some finger is 60, 75, 75, 50
		then i see several positive jump, zero jump and negative jump and i write in the char array, + = - 

	Input:
		string a[NUM_FINGERS] - Save here the chars array.
	Output:
		none
*/
void Functions::packetsArrayToCharsArray(string a[NUM_FINGERS])		//-----ToBeDecided-----//
{
	for (int j = 0; j < NUM_FINGERS; j++)
	{
		int count = 0;
		for (unsigned int i = 0; i < this->_arr.size() - 1; i++)
		{
			int sum = *(this->_arr[i].getPress(j)->getValues()) - *(this->_arr[i + 1].getPress(j)->getValues());

			if (sum > 0) // _arr[i] > _arr[i+1]
			{
				if (i)
				{
					if (a[j][i - 1] != '-')
						a[j].push_back('-');
				}
				else
					a[j].push_back('-');
			}
			else if (sum < 0) // _arr[i] < _arr[i+1]
			{
				if (i)
				{
					if (a[j][i - 1] != '+')
						a[j].push_back('+');
				}
				else
					a[j].push_back('+');
			}
			else // _arr[i] == _arr[i+1]
			{
				if (i)
				{
					if (a[j][i - 1] != '=')
						a[j].push_back('=');
				}
				else
					a[j].push_back('=');
			}
		}
	}
}

/*
*/
char Functions::gyroToChar(int what)
{
	if (this->_arr.size() < 2){
		return 'n';
	}
	int* vals;
	vals = this->_arr.end()->getGyro().getValues();
	int* oldvals = this->_arr.at(this->_arr.size() - 2).getGyro().getValues();
	switch (what){
	case 1:
		int x = vals[0] - oldvals[0];
		if (x > 0){
			return 'f';
		}
		else if (x < 0){
			return 'b';
		}
		else{
			return 'n';
		}
		break;
	case 2:
		int y = vals[1] - oldvals[1];
		if (y > 0){
			return 'r';
		}
		else if (y < 0){
			return 'l';
		}
		else{
			return 'n';
		}
		break;
	case 3:
		int z = vals[2] - oldvals[2];
		if (y > 0){
			return 'u';
		}
		else if (y < 0){
			return 'd';
		}
		else{
			return 'n';
		}
		break;
	}
}

/*
	This Function set the command number
	Input:
		int c - the command number
	Output:
		none
*/
void Functions::setCommandNumber(int c)
{
	this->_commandNumber = c;
}


/*
The Function get the values from the line and save it in 'a'
Input:
string a[NUM_FINGERS+1] - 5 fingers pressure[0-4] and  one "gyro"[5]
string line - the line from the text file
Output:
none
*/
void Functions::fileLineToStringArray(string a[NUM_FINGERS + 1], string line)
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
bool Functions::sameChecks(string a[], string b[])
{
	for (int i = 0; i < NUM_FINGERS + 1; i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}


/*
The Function send input to the computer (simulate)
Input:
WORD vk - the Virtual Key you want to send
Output:
bool - true if success and false if not
*/
bool Functions::sendInput(WORD vk)
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
The function is executing the appropriate command.
Input:
i - the command number
Output:
none
*/
void Functions::runCommand(int c)
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