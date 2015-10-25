#include "Common.h"
#include "AESMain.h"
#include <time.h>

// case insensitive check for equality
#define streq(s1, s2) !_stricmp(s1, s2)

// enum declarations
typedef enum { ACTION_INVALID, ACTION_ENCRYPT, ACTION_DECRYPT } ACTION;
typedef enum { MODE_INVALID, MODE_ECB } MODE;

// function declarations
ACTION getAction(char[]);
bool getKey(char[], uch[]);
bool getKeyString(char[], uch[]);
bool getKeyHex(char[], uch[]);
MODE getMode(char[]);

// Outputs the command-line usage to the console.
void printUsage()
{
	printf(
		"-----\n"
		"AES File Encrypter/Decrypter - Zack Ream\n"
		"Encrypts or Decrypts an input file using the AES algorithm.\n\n"
		"AES (-e|-d) key mode input output\n\n"
		"  -e       Specifies that the file will be encrypted.\n"
		"  -d       Specifies that the file will be decrypted.\n"
		"  key      Specifies the key used in the encryption as either:\n"
		"             A 16-char string surrounded in single quotes.\n"
		"             A 32-digit hexadecimal value (no quotes).\n"
		"  mode     Specifies the mode of encryption/decryption:\n"
		"             ECB: Electronic Code Book\n"
		"             CBC: Cipher Block Chaining (not implemented)\n"
		"  input    Specifies the path to the input file.\n"
		"  output   Specifies the path to the output file.\n"
		"-----\n"
		);
}

// The main entry-point to the program.
int main(int argc, char *argv[])
{
	int rVal = 0;

	if (argc == 6)
	{
		bool validConfiguration = true;

		// read action
		ACTION cAction = getAction(argv[1]);
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
		MODE cMode = getMode(argv[3]);
		if (cMode == MODE_INVALID)
		{
			// invalid mode
			printf("Invalid mode specified.\n");

			validConfiguration = false;
		}

		if (validConfiguration)
		{
			bool validInput = true;

			// open input file, for reading
			FILE *iFile;
			if (fopen_s(&iFile, argv[4], "rb"))
			{
				// error opening input
				printf("Unable to open input file for reading.\n");
				validInput = false;
			}

			if (validInput)
			{
				bool validOutput = true;

				// open output file, for writing
				FILE *oFile;
				if (fopen_s(&oFile, argv[5], "wb"))
				{
					// error opening output
					printf("Unable to open output file for writing.\n");
					validOutput = false;
				}

				if (validOutput)
				{
					// start time
					clock_t timeBegin = clock();

					switch (cAction)
					{
					case ACTION_ENCRYPT:
						AESFileEncrypt(cKey, iFile, oFile);
						break;
					case ACTION_DECRYPT:
						AESFileDecrypt(cKey, iFile, oFile);
						break;
					}

					// end time
					clock_t timeEnd = clock();
					printf("Time elapsed: %ims", timeEnd - timeBegin);
				}
				else
				{
					printUsage();
					rVal = 4;
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

// Parse the encrypt/decrypt action from a command-line parameter.
// Returns the ACTION parsed.
ACTION getAction(char arg[])
{
	ACTION output = ACTION_INVALID;

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

// Parse the 16-byte key from a command-line parameter.
// If valid input, places the key in *key and returns true.
bool getKey(char arg[], uch key[16])
{
	int inLength = strlen(arg);
	switch (inLength)
	{
	case 18:
		return getKeyString(arg, key);
	case 32:
		return getKeyHex(arg, key);
	default:
		return false;
	}
}

// Parse the 16-byte key from a command-line parameter, as a 16-character string.
// If valid input, places the key in *key and returns true.
bool getKeyString(char arg[], uch key[16])
{
	// key is presumably a character string

	// check if first/last chars are single quotes
	if (arg[0] == '\'' && arg[17] == '\'')
	{
		for (int i = 0; i < 16; i++)
		{
			key[i] = arg[i + 1];
		}
		return true;
	}
	else
	{
		return false;
	}
}

// Parse the 16-byte key from a command-line parameter, as a 32-digit hex string.
// If valid input, places the key in *key and returns true.
bool getKeyHex(char arg[], uch key[16])
{
	// key is presumably a hex string

	for (int i = 0; i < 16; i++)
	{
		uch output = 0;

		for (int j = 0; j < 2; j++)
		{
			output <<= 4;

			char c = arg[2 * i + j];
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

		key[i] = output;
	}

	return true;
}

// Parse the AES mode from a command-line parameter.
// Returns the MODE parsed.
MODE getMode(char arg[])
{
	MODE output = MODE_INVALID;

	if (streq(arg, "ecb"))
	{
		output = MODE_ECB;
	}

	return output;
}