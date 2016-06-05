#include <Windows.h>
#include "InfoPacket.h"

//#define STEPMOVEMOUSE 10
#define DEFAULT_BUFLEN 19 // Size of The packet
//#define WIDTH_SCREEN  1366 /*Properties*/
//#define HEIGHT_SCREEN 768 /*Properties*/

class Mouse
{
public:
	//Mouse(){}
	Mouse(SOCKET s, string lastRecv);
	Mouse(POINT position) :_position(position){};
	~Mouse(){}
	
	bool changePosition(Gesture g, InfoPacket packet);
	int calculateDistance(int aOld, int aNew);
	void click(bool leftClick = true);
	void release(bool leftClick = true);
	bool openKeyboard(string s = "C:/windows/System32/osk.exe");
	bool FocusOnKeyboard(HWND window);
	inline bool onKeyboardCheck();
	bool setCursorIcon(string path);
private:

	void GetDesktopResolution();
	string getWindowTitle();

	POINT _position;
	InfoPacket _lastPacket;
	//Gesture _gesture;
};