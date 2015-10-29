#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "Common.h"
#include "ApplicationLayer.h"
#include "LinkLayer.h"

#define INPATH "input.txt"

int main(int argc, char *argv[])
{
	// check arguments
	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " hostname port" << std::endl;
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

	// initialize Transmit socket (IPv4, TCP)
	SOCKET sockTransmit = socket(AF_INET, SOCK_STREAM, 0);
	if (sockTransmit == INVALID_SOCKET)
	{
		int errorNo = WSAGetLastError();
		std::cerr << "ERROR opening socket: " << errorNo << std::endl;
		return 1;
	}

	// create server host
	struct hostent *serverHost;
	serverHost = gethostbyname(argv[1]);
	if (serverHost == NULL)
	{
		std::cerr << "ERROR, no such host" << std::endl;
		return 1;
	}

	// create server address
	struct sockaddr_in addrServer;
	memset((char*)&addrServer, 0, sizeof(addrServer));
	addrServer.sin_family = AF_INET;
	memmove((char*)&addrServer.sin_addr.s_addr, (char*)serverHost->h_addr, serverHost->h_length);
	addrServer.sin_port = htons(atoi(argv[2]));

	// connect to server
	wsaResult = connect(sockTransmit, (sockaddr*)&addrServer, sizeof(addrServer));
	if (wsaResult == SOCKET_ERROR)
	{
		int errorNo = WSAGetLastError();
		std::cerr << "ERROR connecting to server: " << errorNo << std::endl;
		return 1;
	}

	// open input file
	FILE *input = fopen(INPATH, "rb");
	if(input == NULL)
	{
		// error opening input
		std::cerr << "ERROR opening file for reading: " << INPATH << std::endl;
		return 1;
	}

	// char buffer (data stream)
	uch charBuffer[CHAR_LIMIT];
	uint charN;

	// frame buffer (3 chars + data stream)
	uch frameBuffer[FRAME_LIMIT];
	uint frameN;

	// raw transmission buffer (0/1 chars)
	uch transmitBuffer[TRANSMIT_LIMIT];
	uint transmitN;
	
	// initialization for sending a frame
	int sentBytes;

	// loop for entire transmission
	while (true)
	{
		charN = a_readBuffer(input, charBuffer);
		if (charN > 0)
		{
			// have more data, prepare and send

			// prepare frame
			frameN = l_prepareFrame(charBuffer, charN, frameBuffer);

			// prepare transmission
			transmitN = l_prepareTransmit(frameBuffer, frameN, transmitBuffer);

			// transmit
			sentBytes = send(sockTransmit, (char*)transmitBuffer, transmitN, 0);
			if (sentBytes == SOCKET_ERROR)
			{
				int errorNo = WSAGetLastError();
				std::cerr << "ERROR sending: " << errorNo << std::endl;
				return 1;
			}
			else if (sentBytes != transmitN)
			{
				std::cerr << "ERROR, entire buffer was not sent for some reason." << std::endl;
				return 1;
			}
		}
		else
		{
			// file done, exit
			break;
		}
	}

	// close the input file
	fclose(input);

	// close the socket
	wsaResult = closesocket(sockTransmit);
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