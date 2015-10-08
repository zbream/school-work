#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "Common.h"
#include "ApplicationLayer.h"
#include "LinkLayer.h"

#define OUTPATH "output.txt"

int main(int argc, char *argv[])
{
	// check arguments
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " port" << std::endl;
		return 1;
	}

	// store result of Winsock commands
	int wsaResult;
	WSADATA wsaData;

	// initialize Winsock
	WORD wsaVersion = MAKEWORD(2, 2);
	wsaResult = WSAStartup(wsaVersion, &wsaData);
	if (wsaResult != NO_ERROR)
	{
		std::cerr << "ERROR, WSAStartup failed: " << wsaResult << std::endl;
		return 1;
	}

	// initialize Listen socket (IPv4, TCP)
	SOCKET sockListen = socket(AF_INET, SOCK_STREAM, 0);
	if (sockListen == INVALID_SOCKET)
	{
		int errorNo = WSAGetLastError();
		std::cerr << "ERROR opening socket: " << errorNo << std::endl;
		return 1;
	}

	// create server address
	struct sockaddr_in addrServer;
	memset((char*)&addrServer, 0, sizeof(addrServer));
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.s_addr = INADDR_ANY;
	addrServer.sin_port = htons(atoi(argv[1]));

	// bind socket to address
	wsaResult = bind(sockListen, (sockaddr*)&addrServer, sizeof(addrServer));
	if (wsaResult == SOCKET_ERROR)
	{
		int errorNo = WSAGetLastError();
		std::cerr << "ERROR binding socket: " << errorNo << std::endl;
		return 1;
	}

	// prompt for client
	std::cout << "Run client by providing host and port." << std::endl;

	// listen for connections (backlog of 5)
	wsaResult = listen(sockListen, 5);
	if (wsaResult == SOCKET_ERROR)
	{
		int errorNo = WSAGetLastError();
		std::cerr << "ERROR listening: " << errorNo << std::endl;
		return 1;
	}

	// get client address and transmit socket
	struct sockaddr_in addrClient;
	int addrClientL = sizeof(addrClient);
	SOCKET sockTransmit = accept(sockListen, (sockaddr*)&addrClient, &addrClientL);
	if (sockTransmit == INVALID_SOCKET)
	{
		int errorNo = WSAGetLastError();
		std::cerr << "ERROR accepting: " << errorNo << std::endl;
		return 1;
	}

	// open output file
	FILE *output;
	if (fopen_s(&output, OUTPATH, "wb"))
	{
		// error opening output
		std::cerr << "ERROR opening file for writing" << OUTPATH << std::endl;
		return 1;
	}

	// create frame buffer (to receive)
	uch frameBuffer[3 + 8 * CHAR_LIMIT];
	uch frameN;

	// create char buffer (to output file)
	uch charBuffer[CHAR_LIMIT];
	uch charN;

	while (true)
	{
		// receive transmission
		frameN = recv(sockTransmit, (char*)frameBuffer, 3 + 8 * CHAR_LIMIT, 0);

		if (frameN == 0)
		{
			// connection closed gracefully
			break;
		}
		else if (frameN == 0xFF)//SOCKET_ERROR)
		{
			int errorNo = WSAGetLastError();
			std::cerr << "ERROR receiving: " << errorNo << std::endl;
			return 1;
		}
		else if (frameN > 0)
		{
			// received a transmission, read it

			// check parity
			if (l_validateFrame(frameBuffer, frameN))
			{
				// parse frame
				charN = l_parseFrame(frameBuffer, frameN, charBuffer);
			}
			else
			{
				// create notifier
				memcpy(charBuffer, "[PARITY]", 8);
				charN = 8;
			}

			// write to file
			a_writeBuffer(output, charBuffer, charN);

			// and output to the user
			std::cout.write((char*)charBuffer, charN);
		}
	}
	
	// close the output file
	fclose(output);

	// close the socket
	wsaResult = closesocket(sockListen);
	if (wsaResult == SOCKET_ERROR)
	{
		int errorNo = WSAGetLastError();
		std::cerr << "ERROR, closesocket: " << errorNo << std::endl;
		WSACleanup();
		return 1;
	}

	WSACleanup();
	return 0;
}





