#include <iostream>
#include "SmartGloveDll.h"

_declspec(dllexport) class /*SMARTGLOVE_API*/ Point
{
public:
	Point(long x, long y) :_x(x), _y(y){};
	~Point();
	long getX(){ return _x;}
	long getY(){ return _y;}
private:
	long _x;
	long _y;
};