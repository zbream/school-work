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
	FILE *output = fopen(OUTPATH, "wb");
	if(output == NULL)
	{
		// error opening output
		std::cerr << "ERROR opening file for writing" << OUTPATH << std::endl;
		return 1;
	}

	// raw transmission buffer (0/1 chars)
	uch transmitBuffer[TRANSMIT_LIMIT];
	uint transmitN;
	
	// frame buffer (3 chars + data stream)
	uch frameBuffer[FRAME_LIMIT];
	uint frameN;

	// char buffer (data stream)
	uch charBuffer[CHAR_LIMIT];
	uint charN;

	// initialization for reading an entire frame
	FD_SET readSet;
	int readBytes;

	// loop for entire transmission
	while (true)
	{
		// begin reading a new frame
		readBytes = 0;
		transmitN = 0;
		while (true)
		{
			// wait for data at the socket
			FD_ZERO(&readSet);
			FD_SET(sockTransmit, &readSet);
			select(sockTransmit, &readSet, NULL, NULL, NULL);

			// receive data at socket
			readBytes = recv(sockTransmit, (char*)&transmitBuffer[transmitN], ((CHAR_LIMIT + 3) * 8) - transmitN, 0);
			if (readBytes == 0)
			{
				// nothing to receive
				break;
			}
			else if (readBytes == SOCKET_ERROR)
			{
				int errorNo = WSAGetLastError();
				std::cerr << "ERROR receiving: " << errorNo << std::endl;
				return 1;
			}
			else
			{
				// received a [partial] frame
				transmitN += readBytes;
				if (transmitN == (CHAR_LIMIT + 3) * 8)
				{
					// received a complete frame
					break;
				}
			}
		}

		if (transmitN == 0)
		{
			// connection closed gracefully
			break;
		}
		else
		{
			// received a transmission, read it

			// parse transmission (0/1 -> raw frame)
			frameN = l_parseTransmit(transmitBuffer, transmitN, frameBuffer);

			// check parity
			if (l_validateFrame(frameBuffer, frameN))
			{
				// parse frame
				charN = l_parseFrame(frameBuffer, frameN, charBuffer);
			}
			else
			{
				// create notifier
				memcpy(charBuffer, "[PARITY_PARITY_PARITY_PARITY_PARITY_PARITY_PARITY_PARITY_PARITY]", 64);
				charN = 64;
			}

			// write to file
			a_writeBuffer(output, charBuffer, charN);

			// and output to the console
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





