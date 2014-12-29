import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class HangmanReadMain
{

	public static void main(String[] args) throws FileNotFoundException
	{
		// create an array of words
		// final String[] wordList = { "write", "that", "program" };
		final String[] wordList;

		// create a file object, and associate it with "Hangman.txt"
		File file = new File("Hangman.txt");
		if (!file.exists())
		{
			System.out.println("Cannot find word list \"Hangman.txt\"");
			System.exit(0);
		}

		// create a scanner, and attach it to the file object
		Scanner read = new Scanner(file);

		// as long as there are words to read (from the file), read them into
		// our word array
		int wordCount = 0;
		while (read.hasNext())
		{
			read.next();
			wordCount++;
		}

		// close the file
		read.close();

		// now we know how large to make the array.
		wordList = new String[wordCount];

		// reopen the word file
		read = new Scanner(file);

		// read in the N words we counted above
		for (int counter = 0; counter < wordCount; counter++)
		{
			wordList[counter] = read.next();
		}

		// close the file
		read.close();

		// initialize variables
		Scanner input = new Scanner(System.in);
		int randomIndex;
		char inputedLetter;
		hangman H;

		// loop until the player says stop, check post-loop
		do
		{
			// choose a random word out of the list
			randomIndex = (int) (Math.random() * wordList.length);

			// create new instance of hangman to handle game, with starting word
			H = new hangman(wordList[randomIndex]);

			// loop turns until isComplete() returns true, using a post-test
			do
			{
				// prompt user to guess a letter
				System.out.print("(Guess) Enter a letter in word " + H.Word() + " > ");

				// read the first char of the inputed string
				inputedLetter = input.next().charAt(0);

				// test how that letter effects our displayed word
				H.checkLetter(inputedLetter);

			} while (H.isComplete() != true);

			// player has finished the word, print misses and end program
			System.out.println("  The word is " + H.Word() + ". You missed " + H.misses() + " time(s).");

			// prompt for replay
			System.out.print("Do you want to guess another word? Enter 'y' or 'n' > ");
			inputedLetter = input.next().charAt(0);

			// print separator between rounds
			System.out.println();
		} while (inputedLetter == 'y');

		// user has not inputed 'y' to play again, the program ends
		input.close();
	}

}

class hangman
{
	// initialize variables
	private int misses;
	private String completeWord;
	private StringBuilder displayedWord;

	public hangman(String word)
	{
		// initialize strings based on chosen, passed string

		// completeWord holds the unhidden word the user is seeking
		completeWord = word;
		// displayedWord holds the starred-out version of the string
		displayedWord = new StringBuilder(completeWord.length());
		for (int x = 0; x < completeWord.length(); x++)
		{
			displayedWord.append("*");
		}
	}

	public void checkLetter(char letter)
	{
		/* String.indexOf(x) returns -1 if the character is not found
		 * 
		 * IF displayedWord contains the letter, then the letter has already
		 * been guessed and shown.
		 * 
		 * IF NOT, we continue.
		 * IF correctWord does not contain the letter, then the letter is not in
		 * the word, an incorrect guess.
		 * 
		 * IF NOT, we know the letter has not been guessed and that the word
		 * contains it.
		 * 
		 * We can then loop through each letter of the correctWord, and if the
		 * character at that position matches the guessed letter, then we put
		 * that letter at the same index in the displayedWord string. */

		if (displayedWord.toString().indexOf(letter) != -1)
		{
			// the letter is already displayed -> already guessed
			System.out.println("  " + letter + " is already in the word.");
		} else
		{
			// the letter has not already been guessed, continue check
			if (completeWord.indexOf(letter) == -1)
			{
				// the letter does not exist in the word -> +1 miss
				System.out.println("  " + letter + " is not in the word.");
				misses++;
			} else
			{
				// the letter exists in the word -> replace asterisks with it
				for (int index = 0; index < completeWord.length(); index++)
				{
					if (completeWord.charAt(index) == letter)
					{
						displayedWord.setCharAt(index, letter);
					}
				}
			}
		}
	}

	public boolean isComplete()
	{
		/* String.indexOf(x) returns -1 if the character is not found.
		 * If the displayedWord does not contain any asterisks, it's completed */
		boolean containsAsterisks;
		containsAsterisks = (displayedWord.toString().indexOf("*") != -1);
		return !containsAsterisks;
	}

	public int misses()
	{
		// return private value 'misses'
		return misses;
	}

	public String Word()
	{
		// return non-reference to displayedWord
		return displayedWord.toString();
	}

}