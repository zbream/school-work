#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "Common.h"
#include "ApplicationLayer.h"
#include "LinkLayer.h"

// defaults
#define OUTPATH "output.txt"

// function declarations
void handleNone(uch transmitBuffer[TRANSMIT_LIMIT], uint transmitN, FILE* output);
void handleCrc(uch transmitBuffer[TRANSMIT_LIMIT], uint transmitN, FILE* output);
void handleHamming(uch transmitBuffer[TRANSMIT_LIMIT], uint transmitN, FILE* output);

char* sep = "\n==========\n";

int getSwitch(int switchc, char** switchv, const std::string& option, int nOptionParameters)
{
	int pos = std::find(switchv, switchv + switchc, option) - switchv;
	if (switchc - pos - 1 >= nOptionParameters)
	{
		return pos;
	}
	else
	{
		return -1;
	}
}

int frameNum = 0;

int main(int argc, char *argv[])
{
	std::cout << "Data Communications - Server (Receiver)\n";
	
	char* paramPort;
	EC paramEC;
	char* paramOutput;

	// check arguments
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " port [/ec (crc|hamming)] [/path <outputFile>]" << sep;
		return 1;
	}
	else
	{
		paramPort = argv[1];
		paramEC = EC_NONE;
		paramOutput = OUTPATH;

		// check switches
		int switchc = argc - 2;
		char **switchv = argv + 2;

		if (switchc >= 2)
		{
			int pos;

			// check EC mode
			pos = getSwitch(switchc, switchv, "/ec", 1);
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
			pos = getSwitch(switchc, switchv, "/path", 1);
			if (pos > -1)
			{
				paramOutput = switchv[pos + 1];
			}
		}
	}

	// confirm arguments
	std::cout
		<< "Listen port: " << paramPort
		<< "\nError Mode:  " << ECString(paramEC)
		<< "\nOutput File: " << paramOutput
		<< sep;

	// open output file
	FILE *output = fopen(paramOutput, "wb");
	if (output == NULL)
	{
		// error opening output
		std::cerr << "ERROR opening file for writing" << paramOutput << std::endl;
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
	addrServer.sin_port = htons(atoi(paramPort));

	// bind socket to address
	wsaResult = bind(sockListen, (sockaddr*)&addrServer, sizeof(addrServer));
	if (wsaResult == SOCKET_ERROR)
	{
		int errorNo = WSAGetLastError();
		std::cerr << "ERROR binding socket: " << errorNo << std::endl;
		return 1;
	}

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

	// max frame size
	uint frameN;
	switch (paramEC)
	{
	case EC_CRC:
		frameN = MAX_TRANSMIT_CRC;
		break;
	case EC_HAMMING:
		frameN = MAX_TRANSMIT_HAMMING;
		break;
	default:
		frameN = MAX_TRANSMIT_NONE;
		break;
	}
	
	// transmit buffer (0/1 chars)
	uch transmitBuffer[TRANSMIT_LIMIT];
	uint transmitN;

	// data portion of transmission excludes first 3 bytes
	uch* dataBuffer = &transmitBuffer[3];

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
			readBytes = recv(sockTransmit, (char*)&transmitBuffer[transmitN], frameN - transmitN, 0);
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
				if (transmitN == frameN)
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
			frameNum++;

			switch (paramEC)
			{
			case EC_CRC:
				handleCrc(transmitBuffer, transmitN, output);
				break;
			case EC_HAMMING:
				handleHamming(transmitBuffer, transmitN, output);
				break;
			default:
				handleNone(transmitBuffer, transmitN, output);
				break;
			}
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

uch charBuffer[CHAR_LIMIT];
bool charBufferParity[CHAR_LIMIT];

void handleNone(uch transmitBuffer[TRANSMIT_LIMIT], uint transmitN, FILE* output)
{
	uch* dataBuffer = &transmitBuffer[3];
	uint dataN = transmitN - 3;

	uint charN;

	// decode using HDB3
	l_decodeHdb3(dataBuffer, dataN);

	// parse transmission (0/1 -> raw frame)
	charN = l_parseData(dataBuffer, dataN, charBuffer);

	// check and strip parity
	bool validParity = l_validateCharParity(charBuffer, charN, charBufferParity);
	l_stripCharParity(charBuffer, charN);

	if (!validParity)
	{
		std::cout << "ERROR, ASCII parity, frame " << frameNum << ":\n";
		std::cout.write((char*)charBuffer, charN);
		std::cout << "\n";
		for (int i = 0; i < charN; i++)
		{
			std::cout.put(charBufferParity[i] ? ' ' : '^');
		}
		std::cout << "\n\n";
	}

	// write to file
	a_writeBuffer(output, charBuffer, charN);
}

void handleCrc(uch transmitBuffer[TRANSMIT_LIMIT], uint transmitN, FILE* output)
{
	uch* dataBuffer = &transmitBuffer[3];
	uint dataN = transmitN - 3;

	uint charN;

	// decode using HDB3
	l_decodeHdb3(dataBuffer, dataN);

	// check CRC and parse data
	bool validCrc = l_validateDataCrc(dataBuffer, dataN);
	charN = l_parseDataCrc(dataBuffer, dataN, charBuffer);

	// check and strip parity
	bool validParity = l_validateCharParity(charBuffer, charN, charBufferParity);
	l_stripCharParity(charBuffer, charN);

	if (!validCrc)
	{
		std::cout << "ERROR, CRC check, frame " << frameNum << ":\n";
		std::cout.write((char*)charBuffer, charN);
		std::cout << "\n\n";
	}

	if (!validParity)
	{
		std::cout << "ERROR, ASCII parity, frame " << frameNum << ":\n";
		std::cout.write((char*)charBuffer, charN);
		std::cout << "\n";
		for (int i = 0; i < charN; i++)
		{
			std::cout.put(charBufferParity[i] ? ' ' : '^');
		}
		std::cout << "\n\n";
	}

	// write to file
	a_writeBuffer(output, charBuffer, charN);
}

void handleHamming(uch transmitBuffer[TRANSMIT_LIMIT], uint transmitN, FILE* output)
{
	uch* dataBuffer = &transmitBuffer[3];
	uint dataN = transmitN - 3;

	uint charN;

	// decode using HDB3
	l_decodeHdb3(dataBuffer, dataN);

	// TODO: perform Hamming correction
	
	// parse transmission (0/1 -> raw frame)
	charN = l_parseDataHamming(dataBuffer, dataN, charBuffer);

	// check and strip parity
	bool validParity = l_validateCharParity(charBuffer, charN, charBufferParity);
	l_stripCharParity(charBuffer, charN);

	if (!validParity)
	{
		std::cout << "ERROR, ASCII parity, frame " << frameNum << ":\n";
		std::cout.write((char*)charBuffer, charN);
		std::cout << "\n";
		for (int i = 0; i < charN; i++)
		{
			std::cout.put(charBufferParity[i] ? ' ' : '^');
		}
		std::cout << "\n\n";
	}

	// write to file
	a_writeBuffer(output, charBuffer, charN);
}


