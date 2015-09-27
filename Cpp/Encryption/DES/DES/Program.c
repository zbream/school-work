#include "Common.h"
#include "DESMain.h"
#include <string.h>
#include <stdio.h>

// case insensitive check for equality
#define streq(s1, s2) !_stricmp(s1, s2)

// enum declarations
typedef enum { ACTION_INVALID, ACTION_ENCRYPT, ACTION_DECRYPT } action;
typedef enum { MODE_INVALID, MODE_ECB } mode;

// function declarations
action getAction(char arg[]);
bool getKey(char arg[], ull *key);
bool getKeyString(char arg[], ull *key);
bool getKeyChar(char arg[], ull *key);
mode getMode(char arg[]);

void printUsage()
{
	printf(
		"-----\n"
		"DES File Encrypter/Decrypter - Zack Ream\n"
		"Encrypts or Decrypts an input file using the DES algorithm.\n\n"
		"DES (-e|-d) key mode input output\n\n"
		"  -e       Specifies that the file will be encrypted.\n"
		"  -d       Specifies that the file will be decrypted.\n"
		"  key      Specifies the key used in the encryption as either:\n"
		"             An 8-char string surrounded in single quotes.\n"
		"             A 16-digit hexadecimal value (no quotes).\n"
		"  mode     Specifies the mode of encryption/decryption:\n"
		"             ECB: Electronic Code Book\n"
		"             CBC: Cipher Block Chaining (not implemented)\n"
		"  input    Specifies the path to the input file.\n"
		"  output   Specifies the path to the output file.\n"
		"-----\n"
		);
}

int main(int argc, char *argv[])
{
	int rVal = 0;

	if (argc == 6)
	{
		bool validConfiguration = true;

		// read action
		action cAction = getAction(argv[1]);
		if (cAction == ACTION_INVALID)
		{
			// invalid action
			printf("Invalid action specified.\n");

			validConfiguration = false;
		}

		// read key
		ull cKey;
		if (!getKey(argv[2], &cKey))
		{
			// invalid key
			printf("Invalid key specified.\n");

			validConfiguration = false;
		}

		// read mode
		mode cMode = getMode(argv[3]);
		if (cMode == MODE_INVALID)
		{
			// invalid mode
			printf("Invalid mode specified.\n");

			validConfiguration = false;
		}
				
		if (validConfiguration)
		{
			bool validFiles = true;

			// open input file, for reading
			FILE *iFile;
			if (fopen_s(&iFile, argv[4], "rb"))
			{
				// error opening input
				printf("Unable to open input file for reading.\n");
				validFiles = false;
			}

			// open output file, for writing
			FILE *oFile;
			if (fopen_s(&oFile, argv[5], "wb"))
			{
				// error opening output
				printf("Unable to open output file for writing.\n");
				validFiles = false;
			}

			if (validFiles)
			{
				switch (cAction)
				{
				case ACTION_ENCRYPT:
					DESFileEncrypt(cKey, iFile, oFile);
					break;
				case ACTION_DECRYPT:
					DESFileDecrypt(cKey, iFile, oFile);
					break;
				}
			}
			else
			{
				printUsage();
				rVal = 3;
			}

			_fcloseall();
		}
		else
		{
			printUsage();
			rVal = 2;
		}
	}
	else
	{
		printf("Invalid number of arguments.\n");
		printUsage();
		rVal = 1;
	}

	return rVal;
}

action getAction(char arg[])
{
	action output = ACTION_INVALID;

	if (streq(arg, "-e"))
	{
		output = ACTION_ENCRYPT;
	}
	if (streq(arg, "-d"))
	{
		output = ACTION_DECRYPT;
	}

	return output;
}

bool getKey(char arg[], ull *key)
{
	int inLength = strlen(arg);
	switch (inLength)
	{
		case 10:
			return getKeyString(arg, key);
		case 16:
			return getKeyHex(arg, key);
		default:
			return false;
	}
}

bool getKeyString(char arg[], ull *key)
{
	// key is presumably a character string

	// check if first/last chars are single quotes
	if (arg[0] == '\'' && arg[9] == '\'')
	{
		ull output = 0;

		for (ush i = 1; i <= 8; i++) 
		{
			output <<= 8;
			output |= arg[i];
		}

		*key = output;
		return true;
	}
	else
	{
		return false;
	}
}

bool getKeyHex(char arg[], ull *key)
{
	// key is presumably a hex string

	ull output = 0;

	for (ush i = 0; i < 16; i++)
	{
		output <<= 4;

		char c = arg[i];
		if (c >= '0' && c <= '9')
		{
			output |= (c - '0');
		}
		else if (c >= 'A' && c <= 'F')
		{
			output |= (c - 'A' + 10);
		}
		else if (c >= 'a' && c <= 'f')
		{
			output |= (c - 'a' + 10);
		}
		else
		{
			return false;
		}
	}
	
	*key = output;
	return true;
}

mode getMode(char arg[])
{
	mode output = MODE_INVALID;

	if (streq(arg, "ecb"))
	{
		output = MODE_ECB;
	}

	return output;
}

// Forouzan text
//ull key = 0xAABB09182736CCDDULL;
//ull block = 0x123456ABCD132536ULL;

// DES Algorithm Illustrated
//ull key = 0x133457799BBCDFF1ULL;
//ull block = 0x0123456789ABCDEFULL;

// Reverse - Forouzan
//ull key = 0xAABB09182736CCDDULL;
//ull block = 0xc0b7a8d05f3a829cULL;