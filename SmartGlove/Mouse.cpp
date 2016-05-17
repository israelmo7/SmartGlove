#include "Mouse.h"
#define STEP 10
#define DEFAULT_BUFLEN 19 // Size of The packet
#define WIDTH_SCREEN  1366
#define HEIGHT_SCREEN 768

Mouse::Mouse(SOCKET s)
{
	bool flag = true;
	this->_first = true;
	//
	int iResult;
	char recvbuf[DEFAULT_BUFLEN + 1]; // More one for the NULL byte.

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(s, recvbuf, DEFAULT_BUFLEN, 0); // Recv Data from Client.
		recvbuf[DEFAULT_BUFLEN] = NULL;
		//cout << recvbuf << endl;
		if (iResult > 0)
		{
			InfoPacket p = InfoPacket(recvbuf);
			if (!this->_first)
			{
				Gesture g = p - this->_lastPacket;

				flag = changePosition(g);
			}
			else
			{
				this->_first = false;
			}
			
			this->_lastPacket = p;

		}
		else if (iResult == 0)
		{
			printf("Waiting .. \n");
		}
		else
		{
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(s);
			WSACleanup();
			return;
		}

	} while (flag);

	closesocket(s);
}
bool Mouse::changePosition(Gesture g) 
{
	if (g._fingers[0] == "+")
		return false;

	POINT p;
	if (!GetCursorPos(&p))
	{
		cout << "Error: cant find mouse position \n";
		return true;
	}
	g.printGesture();
	
	for (int i = 1; i < 3; i++)
	{
		if (g._fingers[i] == "+")
		{
			click(!(i - 1));
			//release(!(i - 1));
		}
		else if (g._fingers[i] == "-")
		{
			release(!(i - 1));
		}
	}


	if (g._acceleration[0] != "")
	{
		if (g._acceleration[0] == "+")
		{
			cout << "X+ \n";
			p.x = (p.x + STEP > WIDTH_SCREEN) ? WIDTH_SCREEN : p.x + STEP;
		}
		else if (g._acceleration[0] == "-")
		{
			cout << "X- \n";
			p.x = (p.x - STEP < 0) ? 0 : p.x - STEP;
		}
	}
	if (g._acceleration[1] != "")
	{
		if (g._acceleration[1] == "+")
		{
			cout << "Y+ \n";
			p.y = (p.y - STEP < 0) ? 0 : p.y - STEP;

		}
		else if (g._acceleration[1] == "-")
		{
			cout << "Y- \n";
			p.y = (p.y + STEP > HEIGHT_SCREEN) ? HEIGHT_SCREEN : p.y + STEP;
		}
	}
	if (!SetCursorPos(p.x, p.y))
	{
		cout << "Error: cant set the mouse \n";
	}
	else
		this->_position = p;

	return true;
}
void Mouse::click(bool leftClick)
{
	INPUT i;
	i.type = INPUT_MOUSE;
	i.mi.dx = this->_position.x;
	i.mi.dy = this->_position.y;
	i.mi.time = 1000;

	i.mi.dwFlags = (leftClick) ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &i, sizeof(INPUT));
}
void Mouse::release(bool leftClick)
{
	INPUT i;
	i.type = INPUT_MOUSE;
	i.mi.dx = this->_position.x;
	i.mi.dy = this->_position.y;
	i.mi.time = 1000;

	i.mi.dwFlags = (leftClick) ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
	SendInput(1, &i, sizeof(INPUT));
}