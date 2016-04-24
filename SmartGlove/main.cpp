#include <winsock2.h>
#include <iostream>
#include "Traffic.h"
#include "Order.h"
#include <ctime>

//clock_t timerStart;

#define DEFAULT_BUFLEN 19
//#define SECONDS ((timerStart) / (float)(CLOCKS_PER_SEC))

using namespace std;
void closeSocket(SOCKET s);
void sendToOrder(string temp[NUM_FINGERS]);

int main()
{
	Interpreter interPreter = Interpreter();
	char recvbuf[DEFAULT_BUFLEN+1];
	int iResult;
	SOCKET ClientSocket = Traffic().getSocket();
		

	//timerStart = clock();
	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN, 0);
		recvbuf[19] = NULL;
		cout << recvbuf << endl;
		if (iResult > 0) 
		{
			InfoPacket temPacket = InfoPacket(recvbuf);

			if (interPreter.addInfoPacket(temPacket))
			{
				string toSend[NUM_FINGERS];
				interPreter.saveTheSymbol(toSend);
				sendToOrder(toSend);
				interPreter.clearAll();
			}
			interPreter.InfoPacketsDetails();

			interPreter.showSeq();
		}
		else if (iResult == 0)
		{		
		//	interPreter.showSeq();

			/*string temp[NUM_FINGERS];
			interPreter.saveTheSymbol(temp);
			interPreter.InfoPacketsDetails();
			sendToOrder(temp);*/
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


	closeSocket(ClientSocket);

	//cout << "Seconds: " << SECONDS << endl;
	system("pause");
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
void sendToOrder(string temp[NUM_FINGERS])
{
	Order doTheCommands;
	doTheCommands.TheComparetion(temp);
}