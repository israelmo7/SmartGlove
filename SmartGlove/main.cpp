#include <winsock2.h>
#include <iostream>
#include "Traffic.h"
#include "Interpreter.h"
#include "Order.h"
#include "Mouse.h"

#define DLLNAME "DllSmartGlove.dll"
#define DEFAULT_BUFLEN 19 // Size of The packet
#define RECV_SIZE DEFAULT_BUFLEN-1 // Without Null Byte
#define FULL_SIZE 8 // 5 fingers + 3 Axis

using namespace std;

typedef int(__stdcall *f_funci)();

void loadDll();

int main()
{
	Traffic connection = Traffic();
	Order commanderOrder = Order();
	Interpreter interPreter = Interpreter();
	bool lastOne;
	char recvbuf[DEFAULT_BUFLEN+1]; // More one for the NULL byte.
	int iResult, cnt = 0;
	SOCKET ClientSocket = connection.getSocket();
		

	iResult = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN, 0); // Recv Data from Client.
	commanderOrder.runCommand(MOUSEMODE, recvbuf, ClientSocket);
	// Receive until the peer shuts down the connection
	do {
		recvbuf[DEFAULT_BUFLEN] = NULL;
		if (iResult > 0) 
		{
			cout << recvbuf << endl;

			lastOne = true;
			InfoPacket temPacket = InfoPacket(recvbuf); // Make InfoPacket from the Data.

			if (interPreter.addInfoPacket(temPacket)) // Check if the Gesture is done.
			{
				if (cnt % 2 == 0){
					cout << "In !\n";
					string toSend[FULL_SIZE];
					interPreter.saveTheRanges(toSend); // Save the "ranges" in 'toSend'.
					commanderOrder.TheComparation(toSend, recvbuf, ClientSocket);
					interPreter.clearAll();				// Clear the InterPreter.
				}
				else{
					interPreter.clearAll();				// Clear the InterPreter.
				}
			}
			interPreter.InfoPacketsDetails();
			interPreter.showSeq();
		}
		else if (iResult == 0)
		{		
		//	interPreter.showSeq();

			if (lastOne)
			{
				lastOne = false;

				string toSend[FULL_SIZE];
				interPreter.saveTheRanges(toSend); // Save the "ranges" in 'toSend'.
				commanderOrder.TheComparation(toSend, recvbuf, ClientSocket);
				interPreter.clearAll();
			}
			else{
				break;
			}
		}
		else  
		{
			printf("recv failed with error: %d\n", WSAGetLastError());
			connection.closeSocket();
			return 1;
		}
		iResult = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN, 0); // Recv Data from Client.
		cnt++;
	} while (true);
	
	//commanderOrder.destroy();
	connection.closeSocket();
	system("pause");
	return 0;
}
/*
	The function loads the DLL.
		Input:
			None
		Output:
			None
*/
void loadDll()
{
	HINSTANCE dll = LoadLibrary(DLLNAME);

	if (dll)
	{
		cout << "Found!\n";
		f_funci funci = (f_funci)GetProcAddress(dll, "Add");
		if (funci)
		{
			cout << funci() << "\n";
		}
		else
			cout << "Function not found - Error " << GetLastError() << "\n";
	}
	else
	{
		cout << "Dll not found - Error " << GetLastError() << "\n";
	}
}