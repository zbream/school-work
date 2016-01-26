package util;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/*
 * Class to easily return words from a text file.
 * 
 * Upon each getNextWord, we return the next word (omitting punctuation).
 * If a word is empty, skip it and get the next word.
 * 
 * Upon the EOF, return 'null' 
 */
public class WordReader
{
	// declare necessary objects
	File file;
	Scanner reader;
	String rawWord, fixedWord;

	// Constructor for WordReader, opens the passed filePath text file.
	public WordReader(String filePath) throws FileNotFoundException
	{
		file = new File(filePath);

		// if the file doesn't exist, throw exception
		if (!file.exists())
		{
			throw new java.io.FileNotFoundException();
		}

		// open the file to the Scanner
		reader = new Scanner(file);
	}

	/* Returns the next word in the file, NULL if no more strings.
	 * 
	 * If the file has another word, then we read the file;
	 * if it does not, then we return null.
	 * That word is normalized (to lowercase, removing punctuation).
	 * 
	 * If the normalized result is not empty, return the word.
	 * If the normalized result is empty "", there was only punctuation.
	 * Run the method again (recursively) until we either:
	 * 1. get a new word
	 * 2. reach the end of the file */
	public String getNextWord()
	{
		// check if EOF
		if (reader.hasNext())
		{
			// read the raw word
			rawWord = reader.next();
			// normalize it (lowercase, remove punctuation)
			fixedWord = normalizeString(rawWord);
			// if word is empty, get new one
			if (!fixedWord.equals(""))
			{
				return fixedWord;
			} else
			{
				return getNextWord();
			}
		} else
		{
			return null;
		}
	}

	/* Return a word, in lowercase, with punctuation (nonalpha chars) removed.
	 * 
	 * REGEX: replace 1 or more non(a-z, 1-9) chars */
	private String normalizeString(String input)
	{
		return input.toLowerCase().replaceAll("[^a-z0-9]+", "");
	}

	// close the word file
	public void closeFile()
	{
		reader.close();
	}
}
