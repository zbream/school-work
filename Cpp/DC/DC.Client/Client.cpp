#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "Common.h"
#include "ApplicationLayer.h"
#include "LinkLayer.h"
#include "RNG.h"

#include "PhysicalLayer.h"

// defaults
#define INPATH "input.txt"

// separate sections of output
char* sep = "\n==========\n";

int frameNum = 0;

int main(int argc, char *argv[])
{	
	std::cout << "Data Communications - Client (Transmitter)\n";
		
	char* paramHost;
	char* paramPort;
	int paramMaxErrorsPerFrame;
	EC paramEC;
	char* paramInput;

	// check arguments
	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " hostname port [/ec (crc|hamming)] [/path <inputFile>] [/e <maxErrorsPerFrame>]" << std::endl;
		return 1;
	}
	else
	{
		paramHost = argv[1];
		paramPort = argv[2];
		paramMaxErrorsPerFrame = 0;
		paramEC = EC_NONE;
		paramInput = INPATH;

		// check switches
		int switchc = argc - 2;
		char **switchv = argv + 2;

		if (switchc >= 2)
		{
			int pos;

			// check EC mode
			pos = a_findCommandLineSwitch(switchc, switchv, "/ec", 1);
			if (pos > -1)
			{
				if (streq(switchv[pos + 1], "crc"))
				{
					paramEC = EC_CRC;
				}
				else if (streq(switchv[pos + 1], "hamming"))
				{
					paramEC = EC_HAMMING;
				}
			}

			// check path
			pos = a_findCommandLineSwitch(switchc, switchv, "/path", 1);
			if (pos > -1)
			{
				paramInput = switchv[pos + 1];
			}

			// check errors per frame
			pos = a_findCommandLineSwitch(switchc, switchv, "/e", 1);
			if (pos > -1)
			{
				paramMaxErrorsPerFrame = atoi(switchv[pos + 1]);
			}
		}
	}

	// confirm arguments
	std::cout
		<< "Transmit host: " << paramHost
		<< "\nTransmit port: " << paramPort
		<< "\nError Mode:    " << ECString(paramEC)
		<< "\nMax Err/Frame: " << paramMaxErrorsPerFrame
		<< "\nInput File:    " << paramInput
		<< sep;

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
	uint dataN;

	// initialization for sending a frame
	int sentBytes;
	int* introducedErrorPos = new int[paramMaxErrorsPerFrame];
	int bitsPerChar;

	// loop for entire transmission
	while (true)
	{
		charN = a_readBuffer(input, charBuffer);
		if (charN > 0)
		{
			// have more data, prepare and send
			frameNum++;

			// prepare transmission
			l_prepareFrameHeader(transmitBuffer, charN);
			l_addCharParity(charBuffer, charN);
			switch (paramEC)
			{
			case EC_CRC:
				dataN = l_prepareDataCrc(charBuffer, charN, dataBuffer) - 16;
				transmitN = dataN + 16 + 3;
				bitsPerChar = 8;
				break;
			case EC_HAMMING:
				dataN = l_prepareDataHamming(charBuffer, charN, dataBuffer);
				transmitN = dataN + 3;
				bitsPerChar = 12;
				break;
			default:
				dataN = l_prepareData(charBuffer, charN, dataBuffer);
				transmitN = dataN + 3;
				bitsPerChar = 8;
			}

			// introduce errors
			if (paramMaxErrorsPerFrame > 0)
			{
				uint introducedErrors = l_introduceErrors(dataBuffer, dataN, paramMaxErrorsPerFrame, introducedErrorPos);
				for (uint i = 0; i < introducedErrors; i++)
				{
					std::cout << "Error introduced... frame " << (frameNum) << " character " << ((introducedErrorPos[i] / bitsPerChar) + 1) << std::endl;
				}
			}

			// encode using HDB3
			l_encodeHdb3(dataBuffer, transmitN - 3);

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