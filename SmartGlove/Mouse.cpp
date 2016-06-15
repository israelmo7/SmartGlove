#include "Mouse.h"
#include "Properties.h"

#define STR(x) #x
#define ABS(x) ((x < 0)?x*-1:x)
#define BIGGER(a,b) ((a > b)? a:b)
#define SMALLER(a,b) ((a < b)? a:b)
#define ISINSIDE()
#define LEVEL0 5
#define LEVEL1 10
#define LEVEL2 15
#define LEVEL3 20
#define KEYBOARD_TITLE "On-Screen KeyBoard"

int WIDTH_SCREENm = 0;
int HEIGHT_SCREENm = 0;
int STEPMOVEMOUSE = 10;


Mouse::Mouse(SOCKET s, string lastRecv)
{
	this->GetDesktopResolution();
	Properties p = Properties();

	STEPMOVEMOUSE = p.getValueByName(STR(STEPMOVEMOUSE));

	bool flag = true;
	this->_lastPacket = InfoPacket(lastRecv);

	int iResult;
	char recvbuf[DEFAULT_BUFLEN + 1]; // More one for the NULL byte.

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(s, recvbuf, DEFAULT_BUFLEN, 0); // Recv Data from Client.
		recvbuf[DEFAULT_BUFLEN] = NULL;
		//cout << recvbuf << endl;
		if (iResult > 0)
		{
			InfoPacket packet = InfoPacket(recvbuf);

			Gesture g = packet - this->_lastPacket;

			flag = changePosition(g,packet);

			
			this->_lastPacket = packet;

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

	cout << "Exit from 'Mouse Mode' \n";
}
bool Mouse::changePosition(Gesture g, InfoPacket packet) 
{
	int fingersInt[3] = { atoi(g._fingers[0].c_str()), atoi(g._fingers[1].c_str()),
		atoi(g._fingers[2].c_str()) };
	bool fingersRange[3] = { (valueRange(packet.getPress(0).getValue()) != valueRange(this->_lastPacket.getPress(0).getValue())),
		(valueRange(packet.getPress(1).getValue()) != valueRange(this->_lastPacket.getPress(1).getValue())),
		(valueRange(packet.getPress(2).getValue()) != valueRange(this->_lastPacket.getPress(2).getValue())) };
	int accelInt[2] = { atoi(g._acceleration[0].c_str()), atoi(g._acceleration[1].c_str()) };
	bool accelRange[2] = { (valueRange(packet.getGyro().getVal(0)) != valueRange(this->_lastPacket.getGyro().getVal(0))),
		(valueRange(packet.getGyro().getVal(1)) != valueRange(this->_lastPacket.getGyro().getVal(1))) };
	
	//Exit Mouse Mode condition:
	if (fingersInt[0] > 0 && fingersRange[0])
		return false;

	POINT p;
	if (!GetCursorPos(&p))
	{
		cout << "Error: cant find mouse position \n";
		return true;
	}
	if (fingersRange[1]){
		if (fingersInt[1] < 0)
			click(); // left click - sends true as default.
		else if (fingersInt[1] > 0)
			release(); // left release - sends true as default.
	}

	if (fingersRange[2]){
		if (fingersInt[2] < 0)
			click(false); //right click.
		else if (fingersInt[2] > 0)
			release(false); //right release.
	}
	int step = STEPMOVEMOUSE;

	if (g._acceleration[0] != "0")
	{
		if (accelRange[0]){
			if (accelInt[0] < 0)
			{
				cout << "X+ \n";
				p.x = (p.x + step > WIDTH_SCREENm) ? WIDTH_SCREENm : p.x + step;
			}
			else if (accelInt[0] > 0)
			{
				cout << "X- \n";
				p.x = (p.x - step < 0) ? 0 : p.x - step;
			}
		}
	}
	if (g._acceleration[1] != "0")
	{
		if (accelRange[1]){
			if (accelInt[1] < 0)
			{
				cout << "Y+ \n";
				p.y = (p.y - step < 0) ? 0 : p.y - step;

			}
			else if (accelInt[1] > 0)
			{
				cout << "Y- \n";
				p.y = (p.y + step > HEIGHT_SCREENm) ? HEIGHT_SCREENm : p.y + step;
			}
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
	//INPUT i;
	//i.type = INPUT_MOUSE;
	//i.mi.dx = this->_position.x;
	//i.mi.dy = this->_position.y;
	//i.mi.time = 1000;

	//i.mi.dwFlags = (leftClick) ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
	//SendInput(1, &i, sizeof(INPUT));
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
		SetFocus(window);
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
int  Mouse::calculateDistance(int aOld,int aNew)
{
	int sum = aNew - aOld;
	sum = ABS(sum);
	if (sum > 5)
	{
		return LEVEL1;
	}
	else if (sum > 10)
	{
		return LEVEL2;
	}
	else if (sum > 15)
	{
		return LEVEL3;
	}
	else
	{
		return LEVEL0;
	}
}
inline bool Mouse::onKeyboardCheck()
{
	HWND window = GetForegroundWindow();

	if (window)
	{
		if (this->getWindowTitle() == KEYBOARD_TITLE)
		{
			RECT r;
			if (GetWindowRect(window, &r))
			{

				if ((this->_position.x >= r.left && this->_position.x <= r.right) && (this->_position.y >= r.bottom && this->_position.y <= r.top))
				{
					return true;
				}
			}
		}
	}
	return false;
}
string Mouse::getWindowTitle()
{
	char wnd_title[256];
	HWND hwnd = GetForegroundWindow(); // get handle of currently active window
	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	return wnd_title;
}


//DELETE:
bool Mouse::setCursorIcon(string path)
{
	//HCURSOR curs = (HCURSOR)LoadImage(NULL, IDC_WAIT, IMAGE_CURSOR, 0, 0, LR_SHARED);
	return false;
}

int Mouse::valueRange(int value)
{
	Properties p = Properties();
	int offset = p.getValueByName(STR(MAX_OFFSET));
	if (value > 0){
		for (int i = 0; i < offset; i++){
			if (value >= i*offset && value <= i*offset + 9){
				return i + 1;
			}
		}
	}
	else if(value < 0){
		for (int i = 0; i > -offset; i--){
			if (value >= i*offset && value <= i*offset + 9){
				return i - 1;
			}
		}
	}
	return 0;
}