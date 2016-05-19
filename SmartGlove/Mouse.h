#include <Windows.h>
#include "InfoPacket.h"
#include "SmartGloveDll.h"

<<<<<<< HEAD
_declspec(dllexport) class /*SMARTGLOVE_API*/ Mouse
=======
//#define STEPMOVEMOUSE 10
#define DEFAULT_BUFLEN 19 // Size of The packet
//#define WIDTH_SCREEN  1366 /*Properties*/
//#define HEIGHT_SCREEN 768 /*Properties*/

class Mouse
>>>>>>> origin/israel
{
public:
	//Mouse(){}
	Mouse(SOCKET s);
	Mouse(POINT position) :_position(position){};
	~Mouse(){}
	
	bool changePosition(Gesture g);
	void click(bool leftClick = true);
	void release(bool leftClick = true);
	bool openKeyboard(string s = "C:/windows/System32/osk.exe");
	bool FocusOnKeyboard(HWND window);
private:

	void GetDesktopResolution();
	POINT _position;
	InfoPacket _lastPacket;
	bool _first;
	//Gesture _gesture;
};