#pragma once
#include <iostream>
#include "Translation.h"
using namespace std;

class Traffic
{
public:
	Traffic();
	~Traffic(){};
	SOCKET GetSocket() const;
	void CloseSocket(SOCKET s);
private:
	SOCKET _sock;
};