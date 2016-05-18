#pragma once
#include <iostream>
#include "Interpreter.h"
#include "SmartGloveDll.h"
using namespace std;

_declspec(dllexport) class /*SMARTGLOVE_API*/ Traffic
{
public:
	Traffic();
	~Traffic(){};
	SOCKET getSocket() const;
private:
	SOCKET _sock;
};