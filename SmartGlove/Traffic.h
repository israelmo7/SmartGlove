#pragma once
<<<<<<< HEAD
#include <iostream>
#include "Interpreter.h"
#include "SmartGloveDll.h"
using namespace std;
=======

#define DEFAULT_PORT "80"
>>>>>>> origin/israel

_declspec(dllexport) class /*SMARTGLOVE_API*/ Traffic
{
public:
	Traffic();
	~Traffic(){};
	SOCKET getSocket() const;
private:
	SOCKET _sock;
};