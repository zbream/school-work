/* Ream, Zack - Collatz Sequence Frequency Table
EECS 3540 - 2/2/2016 */

#include <iostream>
#include <iomanip>
#include <map>
#include <math.h> // log10
#include <cstdlib> // atoi

// function declarations
int getCollatzStoppingTime(unsigned int);
int getColumnWidth(int, int);

int main(int argc, char *argv[])
{
	std::cout << "Collatz Sequence Frequency Table\n";

	// get range
	int start, end;
	if (argc >= 3)
	{
		// from command line
		start = atoi(argv[1]);
		end = atoi(argv[2]);
	}
	else
	{
		// from user
		std::cout << "Enter inclusive min/max, separated by a space:\n ";
		std::cin >> start >> end;
	}
	std::cout << std::endl;

	// validate range
	if (start > end || start < 0)
	{
		std::cerr << "Invalid range.\n";
		return 1;
	}

	// get frequencies
	std::map<int, int> freq;
	int maxStoppingTime = 0;
	int maxFreq = 0;

	std::map<int, int>::iterator freqIt, freqEnd;
	int freqCurrent, collatzStoppingTime;
	for (unsigned int n = start; n <= end; n++)
	{
		collatzStoppingTime = getCollatzStoppingTime(n);

		// insert if it's missing
		freqIt = freq.find(collatzStoppingTime);
		if (freqIt == freq.end())
		{
			freqIt = freq.insert(freqIt, std::pair<int, int>(collatzStoppingTime, 0));
		}

		// and increment its count
		freqCurrent = ++(freqIt->second);

		// store column maximums
		if (collatzStoppingTime > maxStoppingTime)
		{
			maxStoppingTime = collatzStoppingTime;
		}
		if (freqCurrent > maxFreq)
		{
			maxFreq = freqCurrent;
		}
	}

	// get widths of columns
	int maxStoppingTimeWidth = getColumnWidth(4, maxStoppingTime); // "STOP"
	int maxFreqWidth = getColumnWidth(4, maxFreq); // "FREQ"

	// print frequency table
	std::cout 
		<< std::setw(maxStoppingTimeWidth) << "STOP"
		<< " | "
		<< std::setw(maxFreqWidth) << "FREQ" << std::endl
		<< std::string(maxStoppingTimeWidth, '-')
		<< "-+-"
		<< std::string(maxFreqWidth, '-') << std::endl;
	
	freqIt = freq.begin();
	freqEnd = freq.end();
	while (freqIt != freqEnd)
	{
		std::cout 
			<< std::setw(maxStoppingTimeWidth) << freqIt->first
			<< " | "
			<< std::setw(maxFreqWidth) << freqIt->second
			<< std::endl;

		freqIt++;
	}

	return 0;
}

#define COLLATZ_ODD(n) (3 * (n) + 1)
#define COLLATZ_EVEN(n) ((n) / 2)

int getCollatzStoppingTime(unsigned int n)
{
	int ops = 0;

	while (n > 1)
	{
		++ops;
		n = (n % 2) ? COLLATZ_ODD(n) : COLLATZ_EVEN(n);
	}

	return ops;
}

int getColumnWidth(int headerWidth, int maxCellValue)
{
	// calculate digits of maximum width
	int maxCellValueWidth = (int)(log10(maxCellValue) + 1);
	
	return (maxCellValueWidth > headerWidth ? maxCellValueWidth : headerWidth);
}