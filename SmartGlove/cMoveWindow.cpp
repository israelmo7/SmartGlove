#include "cMoveWindow.h"
#include "cResizeWindow.h"
#include "Properties.h"

#define STR(x) #x
int WIDTH_SCREENw= 0;
int HEIGHT_SCREENw = 0;
int STEPMOVEWINDOW = 0;


cMoveWindow::cMoveWindow(SOCKET s, string lastRecv)
{
	Properties p = Properties();
	STEPMOVEWINDOW = p.getValueByName(STR(STEPMOVEWINDOW));

	this->GetDesktopResolution();
	this->_lastPacket = InfoPacket(lastRecv);
	bool flag = true;
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

			int temp[NUM_FINGERS];
			temp[0] = p.getPress(0).getValue();
			temp[1] = p.getPress(1).getValue();
			temp[2] = p.getPress(2).getValue();
			temp[3] = p.getPress(3).getValue();
			temp[4] = p.getPress(4).getValue();
			Gesture g = (p - this->_lastPacket);
			flag = changePosition(g, temp);


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
	cout << "Exit from 'Drag Mode' \n";
}
cMoveWindow::~cMoveWindow()
{
	//
}

bool cMoveWindow::changePosition(Gesture g, int fingerState[NUM_FINGERS])
{

	cResizeWindow res = cResizeWindow(GetForegroundWindow());

	if (g._fingers[0] == "+" &&
		g._fingers[1] == "+" &&
		g._fingers[2] == "+")
		return false;

	if (g._fingers[2] == "+")
		this->replaceWindows();

	POINT topL,
		bottomR;
	int values[4]; // [0] - Top-Left Point (X)
				   // [1] - Top-Left Point (Y)
				   // [2] - Width
				   // [3] - Height 


	if (!getPosition(&topL, &bottomR))
	{
		cout << "Error: cant find mouse position \n";
		return true;
	}

	values[2] = bottomR.x - topL.x; // Width
	values[3] = bottomR.y - topL.y; // Height

	if (g._acceleration[0] != "")
	{
		if (g._acceleration[0] == "+")
		{
			cout << "X+ \n";
			//temp.x += STEP;
			topL.x = (bottomR.x + STEPMOVEWINDOW > WIDTH_SCREENw) ? topL.x : topL.x + STEPMOVEWINDOW;
		}
		else if (g._acceleration[0] == "-")
		{
			cout << "X- \n";
			topL.x = (topL.x - STEPMOVEWINDOW < 0) ? 0 : topL.x - STEPMOVEWINDOW;
		}

	}
	if (g._acceleration[1] != "")
	{
		if (g._acceleration[1] == "+")
		{
			cout << "Y+ \n";
			topL.y = (topL.y - STEPMOVEWINDOW < 0) ? 0 : topL.y - STEPMOVEWINDOW;
		}
		else if (g._acceleration[1] == "-")
		{
			cout << "Y- \n";
			topL.y = (bottomR.y + STEPMOVEWINDOW > HEIGHT_SCREENw) ? topL.y : topL.y + STEPMOVEWINDOW;
		}
	}


	values[0] = topL.x;
	values[1] = topL.y;
	res.reSizeForMoveWindowClass(g, values,fingerState);

	if (!setWindowPos(values))//(temp.x, temp.y))
	{
		cout << "Error: cant set the mouse \n";
	}

	return true;
}
bool cMoveWindow::getPosition(POINT* topL, POINT* bottomR)
{
	HWND window;
	
	window = GetForegroundWindow();
	RECT r;

	if(GetWindowRect(window, &r))
	{
		topL->x = r.left;
		topL->y = r.top;

		bottomR->x = r.right;
		bottomR->y = r.bottom;
		return true;
	}
	return false;
	
}
bool cMoveWindow::setWindowPos(int values[4])
{
	//values[0] - top left.x
	//values[1] - top left.y
	//values[2] - width
	//values[3] - height

	//cout << "(" << values[0] << ", " << values[1] << ")\n";
	//cout << "Width - " << values[2] << "\nHeight - " << values[3] << "\n";

	HWND window = GetForegroundWindow();
	if(MoveWindow(window, values[0], values[1], values[2], values[3], false))
	{
		return true;
	}
	return false;
}
void cMoveWindow::GetDesktopResolution()
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)

	WIDTH_SCREENw = desktop.right;
	HEIGHT_SCREENw = desktop.bottom;
}
bool cMoveWindow::replaceWindows()
{
	INPUT ip;
	INPUT ip2;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = VK_LMENU;
	ip.ki.dwFlags = 0;
	if (!SendInput(1, &ip, sizeof(INPUT)))
		return false;

	Sleep(100);

	ip2.type = INPUT_KEYBOARD;
	ip2.ki.wScan = 0;
	ip2.ki.time = 0;
	ip2.ki.dwExtraInfo = 0;
	ip2.ki.wVk = VK_TAB;
	ip2.ki.dwFlags = 0;
	SendInput(1, &ip2, sizeof(INPUT));

	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
	ip2.ki.dwFlags = KEYEVENTF_KEYUP;
	return (SendInput(1, &ip2, sizeof(INPUT)) != 0);
}

