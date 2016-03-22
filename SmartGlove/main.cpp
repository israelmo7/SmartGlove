#include <winsock2.h>
#include <iostream>
#include "Traffic.h"

using namespace std;
void closeSocket(SOCKET s);

int main()
{
	//SOCKET sock = Traffic().getSocket();
	Interpreter p;
	Traffic(p);
	string* fingersState = p.begin();
	/*
		
		The Loop and all the code.

	*/

	//closeSocket(sock);
	return 0;
}

void closeSocket(SOCKET s)
{
	int iResult;

	iResult = shutdown(s, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout << ("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return;
	}

	// cleanup
	closesocket(s);
	WSACleanup();
	return;
}