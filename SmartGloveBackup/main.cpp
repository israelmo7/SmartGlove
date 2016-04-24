#include <winsock2.h>
#include <iostream>
#include "Traffic.h"
#define DEFAULT_BUFLEN 34
using namespace std;

int main()
{
	char recvbuf[DEFAULT_BUFLEN];
	int iResult, iSendResult;
	Traffic trafficStart = Traffic();
	SOCKET ClientSocket = trafficStart.GetSocket();
		
	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN, 0);
		if (iResult > 0) 
		{
			iSendResult = 1;/*send()*/
			//////////////////////////////////////////////
			//////////////////////////////////////////////
			//////////////////////////////////////////////
			//////////////////////////////////////////////
			//////////////////////////////////////////////
			//////////////////////////////////////////////
			//////////////////////////////////////////////
			//////////////////////////////////////////////
			//////////////////////////////////////////////
			//////////////////////////////////////////////

			if (iSendResult == SOCKET_ERROR)
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
		{
			printf("Connection closing...\n");
		}
		else  
		{
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0);


	trafficStart.CloseSocket(ClientSocket);
	return 0;
}