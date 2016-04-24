#include <winsock2.h>
#include <iostream>
#include "Traffic.h"
#include "Order.h"
#include <ctime>


#define DEFAULT_BUFLEN 19 // Size of The packet
#define FULL_SIZE 6 // 5 fingers + 1 Accel'

using namespace std;

void closeSocket(SOCKET s);
void sendToOrder(string temp[FULL_SIZE]);

int main()
{
	Interpreter interPreter = Interpreter();
	char recvbuf[DEFAULT_BUFLEN+1]; // More one for the NULL byte.
	int iResult;
	SOCKET ClientSocket = Traffic().getSocket();
		

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN, 0); // Recv Data from Client.
		recvbuf[19] = NULL;
		cout << recvbuf << endl;
		if (iResult > 0) 
		{
			InfoPacket temPacket = InfoPacket(recvbuf); // Make InfoPacket from the Data.

			if (interPreter.addInfoPacket(temPacket)) // Check if the Gesture is done.
			{
				cout << "In !\n";
				string toSend[FULL_SIZE];
				interPreter.saveTheSymbol(toSend); // Save the "Symbol" in 'toSend'.
				sendToOrder(toSend);
				interPreter.clearAll();				// Clear the InterPreter.
			}
			//interPreter.InfoPacketsDetails();

			//interPreter.showSeq();
			//system("cls");
			interPreter.showAccel();
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


	closeSocket(ClientSocket); // Close The socket.
	system("pause");
	return 0;
}
/*
	The Function Closes the Socket.
		
		Input:
			SOCKET s - The socket.
		Output:
			none
*/
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
/*
	The function sends the temp(5 fingers state and accel') to the Order.
		
		Input:
			string temp[6] - 5 fingers state and accel'

		Output:
			none

*/
void sendToOrder(string temp[FULL_SIZE])
{
	Order doTheCommands;
	doTheCommands.TheComparetion(temp);
}