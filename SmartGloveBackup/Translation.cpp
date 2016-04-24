#include "Translation.h"
#include "Functions.h"
#include <fstream>
#include <string>
#include <time.h>



/*
	Ctor.
	Input:
		p - The first InfoPacket in the InfoPacket list.
	Output:
		none
*/
Translation::Translation(InfoPacket p)
{
	this->_InfoPacketsList.push_back(p);
}

/*
	Dtor.
	Input:
		none
	Output:
		none
*/
Translation::~Translation()
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
void Translation::Add(InfoPacket p)
{
	this->_InfoPacketsList.push_back(p);
}

/*
	The function prints the InfoPackets.
	Input:
		none
	Output:
		none
*/
void Translation::Details()
{
	int cnt = 1;
	for each (InfoPacket i in this->_InfoPacketsList)
	{
		cout << "InfoPacket " << cnt++ << ": \n";
		i.showDetails();
		cout << endl;
	}
}

/*
	The function starts the translation /////EXPLANATION...........
	Input:
		none
	Output:
		none
*/
void Translation::BeginTrans()
{
	string fingerState[NUM_FINGERS];
	
	this->TransPackets(fingerState);

	Functions funcs = Functions();
	
	funcs.Comparation(fingerState);			/////EXPLANATION...........

}

/*
	This function change the InfoPacket array to char array.
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

void Translation::TransPackets(string a[NUM_FINGERS])
{
	for (int j = 0; j < NUM_FINGERS; j++)
	{
		int count = 0;
		for (unsigned int i = 0; i < this->_InfoPacketsList.size() - 1; i++)
		{
			int sum = _InfoPacketsList[j].getPress(i).getValue() - this->_InfoPacketsList[j + 1].getPress(i).getValue();

			if (sum > 0)					// _arr[i] > _arr[i+1]
			{
				if (i)
				{
					if (a[j][i - 1] != '-')
						a[j].push_back('-');
				}
				else
					a[j].push_back('-');
			}
			else if (sum < 0)				// _arr[i] < _arr[i+1]
			{
				if (i)
				{
					if (a[j][i - 1] != '+')
						a[j].push_back('+');
				}
				else
					a[j].push_back('+');
			}
			else							// _arr[i] == _arr[i+1]
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