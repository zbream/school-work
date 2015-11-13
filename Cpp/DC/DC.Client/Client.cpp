#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#include "Common.h"
#include "ApplicationLayer.h"
#include "LinkLayer.h"
#include "RNG.h"

// defaults
#define INPATH "input.txt"

int frameNum = 0;

int main(int argc, char *argv[])
{	
	// check arguments
	char* paramHost;
	char* paramPort;
	int paramMaxErrorsPerFrame;
	EC paramEC;
	char* paramInput;
	if (argc < 4)
	{
		std::cerr << "Usage: " << argv[0] << " hostname port maxErrorsPerFrame [crc|hamming] [inputPath]" << std::endl;
		return 1;
	}
	else
	{
		paramHost = argv[1];
		paramPort = argv[2];
		paramMaxErrorsPerFrame = std::stoi(argv[3]);
		paramEC = EC_NONE;
		paramInput = INPATH;

		if (argc == 4)
		{
			// no EC, no inPath
		}
		else if (argc == 5)
		{
			// no EC, inPath
			paramInput = argv[4];
		}
		else if (argc == 6)
		{
			// EC, inPath
			if (streq(argv[4], "crc"))
			{
				paramEC = EC_CRC;
			}
			else if (streq(argv[4], "hamming"))
			{
				paramEC = EC_HAMMING;
			}

			paramInput = argv[5];
		}
	}

	// open input file
	FILE *input = fopen(paramInput, "rb");
	if (input == NULL)
	{
		// error opening input
		std::cerr << "ERROR opening file for reading: " << paramInput << std::endl;
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
	serverHost = gethostbyname(paramHost);
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
	addrServer.sin_port = htons(atoi(paramPort));

	// connect to server
	wsaResult = connect(sockTransmit, (sockaddr*)&addrServer, sizeof(addrServer));
	if (wsaResult == SOCKET_ERROR)
	{
		int errorNo = WSAGetLastError();
		std::cerr << "ERROR connecting to server: " << errorNo << std::endl;
		return 1;
	}
	
	// initialize the RNG
	rng_seed();
		
	// char buffer (data stream)
	uch charBuffer[CHAR_LIMIT];
	uint charN;

	// transmit buffer (0/1 chars)
	uch transmitBuffer[TRANSMIT_LIMIT];
	uint transmitN;

	// data portion of transmission excludes first 3 bytes
	uch* dataBuffer = &transmitBuffer[3];

	// initialization for sending a frame
	int sentBytes;
	int* introducedErrorPos = new int[paramMaxErrorsPerFrame];

	// loop for entire transmission
	while (true)
	{
		charN = a_readBuffer(input, charBuffer);
		if (charN > 0)
		{
			// have more data, prepare and send
			frameNum++;

			// prepare transmission
			l_addCharParity(charBuffer, charN);
			switch (paramEC)
			{
			case EC_CRC:
				transmitN = l_prepareDataCrc(charBuffer, charN, dataBuffer) + 3;
				break;
			case EC_HAMMING:
				transmitN = l_prepareDataHamming(charBuffer, charN, dataBuffer) + 3;
				break;
			default:
				transmitN = l_prepareData(charBuffer, charN, dataBuffer) + 3;
			}

			// introduce errors
			if (paramMaxErrorsPerFrame > 0)
			{
				uint introducedErrors = l_introduceErrors(dataBuffer, transmitN - 3, paramMaxErrorsPerFrame, introducedErrorPos);
				for (uint i = 0; i < introducedErrors; i++)
				{
					std::cout << "Error introduced... frame " << (frameNum) << " rawDataBit " << (introducedErrorPos[i]) << std::endl;
				}
			}			

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