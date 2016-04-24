#pragma once
#include <iostream>
#include "Interpreter.h"
using namespace std;

class Traffic
{
public:
	Traffic();
	~Traffic(){};
	SOCKET getSocket() const;
private:
	SOCKET _sock;
};