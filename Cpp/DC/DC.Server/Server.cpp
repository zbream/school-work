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

// separate sections of output
char* sep = "\n==========\n";

uch charBuffer[CHAR_LIMIT];
uch charBufferFlags[CHAR_LIMIT];

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
		std::cout << "Usage: " << argv[0] << " port [/ec (crc|hamming)] [/path <outputFile>]" << sep;
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
		std::cout << "ERROR, unable to open file for writing: " << paramOutput << std::endl;
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
		std::cout << "ERROR, WSAStartup failed: " << wsaResult << std::endl;
		return 1;
	}

	// initialize Listen socket (IPv4, TCP)
	SOCKET sockListen = socket(AF_INET, SOCK_STREAM, 0);
	if (sockListen == INVALID_SOCKET)
	{
		int errorNo = WSAGetLastError();
		std::cout << "ERROR, opening socket failed: " << errorNo << std::endl;
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
		std::cout << "ERROR, binding socket failed: " << errorNo << std::endl;
		return 1;
	}

	// listen for connections (backlog of 5)
	wsaResult = listen(sockListen, 5);
	if (wsaResult == SOCKET_ERROR)
	{
		int errorNo = WSAGetLastError();
		std::cout << "ERROR, listening on socket failed: " << errorNo << std::endl;
		return 1;
	}

	// get client address and transmit socket
	struct sockaddr_in addrClient;
	int addrClientL = sizeof(addrClient);
	SOCKET sockTransmit = accept(sockListen, (sockaddr*)&addrClient, &addrClientL);
	if (sockTransmit == INVALID_SOCKET)
	{
		int errorNo = WSAGetLastError();
		std::cout << "ERROR, accepting connection failed: " << errorNo << std::endl;
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
				std::cout << "ERROR, receiving failed: " << errorNo << std::endl;
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
		std::cout << "ERROR, closesocket failed: " << errorNo << std::endl;
		WSACleanup();
		return 1;
	}

	WSACleanup();
	return 0;
}

void printFrameError(uint charN)
{
	std::cout << "ERROR found, in frame " << frameNum << ":\n     ";
	std::cout.write((char*)charBuffer, charN);
	std::cout << std::endl;
}

void printParityErrors(uint charN)
{
	std::cout << " PAR:";
	for (uint i = 0; i < charN; i++)
	{
		std::cout.put((charBufferFlags[i] & FLAG_ER_PARITY) ? '^' : ' ');
	}
	std::cout << std::endl;
}

void printCrcError()
{
	std::cout << " CRC:invalid" << std::endl;
}

void printHammingErrors(uint charN)
{
	std::cout << " HAM:";
	for (uint i = 0; i < charN; i++)
	{
		uch flag = charBufferFlags[i];
		char c;
		if (flag & FLAG_ER_HAMMING_CORRECTED)
		{
			c = '^';
		}
		else if (flag & FLAG_ER_HAMMING_DETECTED)
		{
			c = '!';
		}
		else
		{
			c = ' ';
		}
		std::cout.put(c);
	}
	std::cout << std::endl;
}

void handleNone(uch transmitBuffer[TRANSMIT_LIMIT], uint transmitN, FILE* output)
{	
	uch* dataBuffer = &transmitBuffer[3];
	uint dataN = transmitN - 3;
	uint charN;

	// clear flags
	memset(charBufferFlags, 0, CHAR_LIMIT);

	// decode using HDB3
	l_decodeHdb3(dataBuffer, dataN);

	// parse transmission (0/1 -> raw frame)
	charN = l_parseData(dataBuffer, dataN, charBuffer);

	// check and strip parity
	bool validParity = l_validateCharParity(charBuffer, charN, charBufferFlags);
	l_stripCharParity(charBuffer, charN);

	if (!validParity)
	{
		printFrameError(charN);
		printParityErrors(charN);
		std::cout << std::endl;
	}

	// write to file
	a_writeBuffer(output, charBuffer, charN);
}

void handleCrc(uch transmitBuffer[TRANSMIT_LIMIT], uint transmitN, FILE* output)
{
	uch* dataBuffer = &transmitBuffer[3];
	uint dataN = transmitN - 3;
	uint charN;

	// clear flags
	memset(charBufferFlags, 0, CHAR_LIMIT);

	// decode using HDB3
	l_decodeHdb3(dataBuffer, dataN);

	// check CRC and parse data
	bool validCrc = l_validateDataCrc(dataBuffer, dataN);
	charN = l_parseDataCrc(dataBuffer, dataN, charBuffer);

	// check and strip parity
	bool validParity = l_validateCharParity(charBuffer, charN, charBufferFlags);
	l_stripCharParity(charBuffer, charN);

	if (!validParity || !validCrc)
	{
		printFrameError(charN);
		if (!validParity) printParityErrors(charN);
		if (!validCrc) printCrcError();
		std::cout << std::endl;
	}

	// write to file
	a_writeBuffer(output, charBuffer, charN);
}

void handleHamming(uch transmitBuffer[TRANSMIT_LIMIT], uint transmitN, FILE* output)
{
	uch* dataBuffer = &transmitBuffer[3];
	uint dataN = transmitN - 3;
	uint charN;

	// clear flags
	memset(charBufferFlags, 0, CHAR_LIMIT);

	// decode using HDB3
	l_decodeHdb3(dataBuffer, dataN);

	// correct hamming if possible
	bool validHamming = l_validateDataHamming(dataBuffer, dataN, charBufferFlags);
	
	// parse transmission (0/1 -> raw frame)
	charN = l_parseDataHamming(dataBuffer, dataN, charBuffer);

	// check and strip parity
	bool validParity = l_validateCharParity(charBuffer, charN, charBufferFlags);
	l_stripCharParity(charBuffer, charN);

	if (!validParity || !validHamming)
	{
		printFrameError(charN);
		if (!validHamming) printHammingErrors(charN);
		if (!validParity) printParityErrors(charN);
		std::cout << std::endl;
	}

	// write to file
	a_writeBuffer(output, charBuffer, charN);
}


