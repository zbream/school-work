import java.util.Scanner;

public class C4
{
	/* Zack Ream
	 * Ex7.20 - Game: Connect Four
	 * 
	 * This program runs a general Connect Four game, alternating between two
	 * players: Red and Yellow. It maintains and redraws the board, accepts
	 * input for adding pieces, and checks for winners or full columns/board. */

	// board is static, accessible to any method in ConnectFour class
	static int[][] board;

	public static void main(String[] args)
	{
		// initialize variables
		int turn = 0;
		int player;
		int winner = 0;
		Scanner input = new Scanner(System.in);

		// initialize board as 6x7 array 'board', filled with 0s
		// board[column][row]
		board = new int[7][6];
		printBoard();

		// take turns until 42 turns have passed == the board is full
		while (turn < 42)
		{
			turn++;
			// set current player from turn number, odd is Red (1), even is
			// Yellow (2)
			player = ((turn - 1) % 2) + 1;

			// inputColumn holds value for input, which is the chosen column
			// openSpaceIndex holds value returned from openSpace, which tells
			// us the row index which is the first open of the column
			int inputColumn, openSpaceIndex;

			// keep prompting for a column number when a full/invalid column is
			// chosen, post-loop test
			do
			{
				// show correct prompt for current players
				System.out.print("Turn " + turn + ": ");
				switch (player)
				{
				case 1:
					System.out.print("Drop a Red disk at column (0-6): ");
					break;
				case 2:
					System.out.print("Drop a Yellow disk at column (0-6): ");
					break;
				}
				// get input of column
				inputColumn = input.nextInt();

				// get row index of first open spot
				openSpaceIndex = openSpace(inputColumn);
			} while (openSpaceIndex == -1);

			// separate new turn
			System.out.println("\n==============================================\n");

			// set player peg in chosen spot
			board[inputColumn][openSpaceIndex] = player;

			// redisplay board
			printBoard();

			// check for winner on placed piece
			winner = isWinner(inputColumn, openSpaceIndex);
			// if winner is not 0, then there is a winner
			// print winner, and break the loop
			if (winner != 0)
			{
				switch (winner)
				{
				case 1:
					System.out.println("The Red Player Won.");
					break;
				case 2:
					System.out.println("The Yellow Player Won.");
					break;
				}
				// since there was a winner, break the loop prematurely
				break;
			}
		}

		// if we got here and winner is 0, then there was no winner, the board
		// is full == it is a draw
		if (winner == 0)
		{
			System.out.println("The board is full, it is a draw!");
		}
		input.close();
		// END OF PROGRAM
	}

	public static void printBoard()
	{
		// loop through the rows and columns of the board, printing the board in
		// the console
		// (0,0) is the bottom left of the board

		// loop through the rows (y)

		for (int y = 5; y >= 0; y--)
		{
			// loop through the columns (x)
			for (int x = 0; x < 7; x++)
			{
				// print separating grid lines
				System.out.print("|");
				// 0 is Blank space, 1 is Red, 2 is Yellow
				switch (board[x][y])
				{
				case 0:
					System.out.print(" ");
					break;
				case 1:
					System.out.print("R");
					break;
				case 2:
					System.out.print("Y");
					break;
				}
			}
			// print final grid line at end of row, starting a new line after
			System.out.println("|");
		}
		// print bottom grid line
		System.out.println("+—+—+—+—+—+—+—+");
	}

	public static int openSpace(int column)
	{
		// return column index of lowest open space, returns -1 if full or out
		// of range.

		// If out of range, tell the player
		if ((column > 6) || (column < 0))
		{
			System.out.println(" Column " + column + " does not exist.");
			return -1;
		}
		// loop from bottom to top of column
		for (int y = 0; y < 6; y++)
		{
			// loop through until you see the first blank space (0), return the
			// index of that row
			if (board[column][y] == 0)
			{
				return y;
			}
		}
		// if the method makes it here, there are no open spaces in the column,
		// tell the player
		System.out.println(" Column " + column + " is full.");
		return -1;
	}

	public static int isWinner(int column, int row)
	{
		/* When a piece is placed, this method searches the row, column, and
		 * diagonals emanating from the placed point. This is sufficient, since
		 * a win can only take place along where the piece is placed. It
		 * generates arrays of values, sent to the fourInRow method which looks
		 * for a win.
		 * 
		 * Returns 0: No Win
		 * Returns 1: Red Wins
		 * Returns 2: Yellow Wins */

		// use temporary array to hold values passed to fourInRow method
		int[] tempArray;
		int winner;

		// generate and test horizontal row array
		tempArray = new int[7];
		for (int i = 0; i < 7; i++)
		{
			tempArray[i] = board[i][row];
		}
		winner = fourInRow(tempArray);
		// if winner != 0, then there is a winner in the horizontal row
		if (winner != 0)
		{
			return winner;
		}

		// generate and test vertical column array
		tempArray = board[column];
		winner = fourInRow(tempArray);
		// if winner != 0, then there is a winner in the vertical column
		if (winner != 0)
		{
			return winner;
		}

		// generate and test diagonal array, positive slope
		tempArray = new int[6];
		int x = column, y = row;
		// count down positions to bottom left, until we find the coordinate of
		// the border
		while ((x > 0) && (y > 0))
		{
			x--;
			y--;
		}
		// now, x and y hold the coordinate of the bottom left edge of the
		// positive diagonal.
		// we can loop through the values diagonally, generating an array of
		// values until we reach the upper right end of the diagonal, where
		// x = 6 or y = 5
		int i = 0;
		while (x <= 6 && y <= 5)
		{
			tempArray[i] = board[x][y];
			x++;
			y++;
			i++;
		}
		winner = fourInRow(tempArray);
		// if winner != 0, then there is a winner in the positive diagonal
		if (winner != 0)
		{
			return winner;
		}

		// generate and test diagonal array, negative slope
		tempArray = new int[6];
		x = column;
		y = row;
		// count down positions to top left, until we find the coordinate of
		// the border
		while (x > 0 && y < 5)
		{
			x--;
			y++;
		}
		// now, x and y hold the coordinate of the top left edge of the
		// negative diagonal.
		// we can loop through the values diagonally, generating an array of
		// values until we reach the lower right end of the diagonal, where
		// x = 6 or y = 0
		i = 0;
		while (x <= 6 && y >= 0)
		{
			tempArray[i] = board[x][y];
			x++;
			y--;
			i++;
		}
		winner = fourInRow(tempArray);
		// if winner != 0, then there is a winner in the negative diagonal
		if (winner != 0)
		{
			return winner;
		}

		// if the method makes it to this point, there was no winner, return 0
		return 0;
	}

	public static int fourInRow(int[] seq)
	{
		/* Loop through the passed array, looking for four in a row. We go
		 * through each position, checking to see if it and the next three
		 * elements are equal. For this reason, we don't need to start from the
		 * last three elements of the array; hence, the (seq.length - 3)
		 * 
		 * returns 0: No Win
		 * returns 1: Red Wins
		 * returns 2: Yellow Wins */

		for (int i = 0; i < (seq.length - 3); i++)
		{
			/* set win flag to true, loop through next four elements of the
			 * array, if one is not equal to another, then the four do not
			 * match: isWin sets to false for this group of four. Move on to the
			 * next group of four. */
			boolean isWin = true;
			// check the group of four elements for a win
			// check if seq[0]=seq[1], then seq[1]=seq[2], then seq[2]=seq[3]
			for (int j = 0; j < 3; j++)
			{
				// if two elements do not match, not a win
				if (seq[i + j] != seq[i + j + 1])
				{
					isWin = false;
					break;
				}
			}

			// after going through a group of four, if isWin is still true,
			// there is a match, return the winner, the value of any of the four
			// elements
			if (isWin == true)
			{
				return seq[i];
			}
		}
		// if we make it this far, then there was no win in any group of four:
		// no winner
		return 0;
	}

}