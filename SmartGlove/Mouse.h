#include <Windows.h>
#include <iostream>
#include "Gesture.h"
#include "Point.h"

class Mouse
{
public:
	Mouse(Point position) :_position(position){};
	~Mouse();
	void changePosition(Gesture g);
	void click(bool leftClick = true);
private:
	Point _position;
};