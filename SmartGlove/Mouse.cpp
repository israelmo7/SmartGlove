#include "Mouse.h"
#include "Properties.h"

#define STR(x) #x

int WIDTH_SCREENm = 0;
int HEIGHT_SCREENm = 0;
int STEPMOVEMOUSE = 0;
Mouse::Mouse(SOCKET s)
{
	this->GetDesktopResolution();
	Properties p = Properties();

	STEPMOVEMOUSE = p.getValueByName(STR(STEPMOVEMOUSE));
//	cout << "Width: " << WIDTH_SCREENm << "\nHeight: " << HEIGHT_SCREENm << "\nStep: " << STEPMOVEMOUSE << endl;
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
	else if (g._fingers[0] == "2")
	{
		if (!(this->openKeyboard() && this->FocusOnKeyboard(GetForegroundWindow())))
		{
			cout << "Error: " << GetLastError() << endl;
			return false;
		}
		return true;
	}
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
			p.x = (p.x + STEPMOVEMOUSE > WIDTH_SCREENm) ? WIDTH_SCREENm : p.x + STEPMOVEMOUSE;
		}
		else if (g._acceleration[0] == "-")
		{
			cout << "X- \n";
			p.x = (p.x - STEPMOVEMOUSE < 0) ? 0 : p.x - STEPMOVEMOUSE;
		}
	}
	if (g._acceleration[1] != "")
	{
		if (g._acceleration[1] == "+")
		{
			cout << "Y+ \n";
			p.y = (p.y - STEPMOVEMOUSE < 0) ? 0 : p.y - STEPMOVEMOUSE;

		}
		else if (g._acceleration[1] == "-")
		{
			cout << "Y- \n";
			p.y = (p.y + STEPMOVEMOUSE > HEIGHT_SCREENm) ? HEIGHT_SCREENm : p.y + STEPMOVEMOUSE;
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
bool Mouse::openKeyboard(string s)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(
		TEXT(s.c_str()),
		NULL, NULL, NULL, FALSE,
		0,
		NULL, NULL,
		&si,
		&pi
		)
		)
	{
		printf("Unable to execute. Error %d \n", GetLastError());
		return false;
	}
	else
	{
		CloseHandle(pi.hProcess);
	}
	return true;
}
bool Mouse::FocusOnKeyboard(HWND window)
{
	if (window)
	{
		RECT r;
		if (GetWindowRect(window, &r))
		{
			//topL->x = r.left;
			//topL->y = r.top;

			//bottomR->x = r.right;
			//bottomR->y = r.bottom;

			if (SetCursorPos((r.right + r.left) / 2, (r.top + r.bottom) / 2))
			{
				return true;
			}
		}		
	}
	cout << "Error: " << GetLastError() << endl;
	return false;
}
void Mouse::GetDesktopResolution()
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	WIDTH_SCREENm = desktop.right;
	HEIGHT_SCREENm = desktop.bottom;
}