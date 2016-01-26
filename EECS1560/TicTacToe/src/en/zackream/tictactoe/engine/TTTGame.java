package en.zackream.tictactoe.engine;

/**
 * Engine for a TicTacToe game.
 * 
 * @author Zack Ream
 * 
 */
public class TTTGame
{
	/**
	 * Multi-dimensional array of TTTPanels.
	 */
	private TTTPanel[][] panels = new TTTPanel[3][3];

	/**
	 * Constructor.
	 * <p>
	 * Initializes the 9 TTTPanels of the game.
	 */
	public TTTGame()
	{
		for (int row = 0; row < 3; row++)
		{
			for (int column = 0; column < 3; column++)
			{
				panels[row][column] = new TTTPanel();
			}
		}
	}

	/**
	 * Game Properties.
	 */
	int turn = 1, lastTurn = 9;

	/**
	 * Returns the current turn number (1-based).
	 * 
	 * @return the current turn number.
	 */
	public int getTurn()
	{
		return turn;
	}

	/**
	 * Increases the turn counter by one.
	 */
	public void incrementTurn()
	{
		turn++;
	}

	/**
	 * Returns the number (1/2) of the current player.
	 * <p>
	 * It is calculated through modular arithmetic of the turn number.
	 * 
	 * @return the number of the current player.
	 */
	public int getCurrentPlayerNum()
	{
		return ((turn + 1) % 2) + 1;
	}

	/**
	 * Returns the name (X/O) of the current player.
	 * <p>
	 * It is calculated through modular arithmetic of the turn number.
	 * 
	 * @return the name of the current player (in char format)
	 */
	public char getCurrentPlayerName()
	{
		return (turn % 2 != 0) ? 'X' : 'O';
	}

	/**
	 * Returns the name (X/O) of the passed player number;
	 * 
	 * @param playerNum
	 *            The number of the player (1/2)
	 * @return the name of playerNum
	 */
	public char getPlayerName(int playerNum)
	{
		return (playerNum == 1) ? 'X' : 'O';
	}

	/**
	 * Returns a reference to the TTTPanel at the specified location.
	 * 
	 * @param row
	 *            The row of the TTTPanel.
	 * @param column
	 *            The column of the TTTPanel.
	 * @return the specified TTTPanel
	 */
	private TTTPanel getPanel(int row, int column)
	{
		return panels[row][column];
	}

	/**
	 * Set the symbol of the TTTPanel at the specified location.
	 * <p>
	 * The symbol set is that of the current player.
	 * 
	 * @param row
	 *            The row of the TTTPanel.
	 * @param column
	 *            The column of the TTTPanel.
	 * @return the [new] symbol of the TTTPanel.
	 */
	public int setPanelSymbol(int row, int column)
	{
		if (getPanel(row, column).isFree())
		{
			getPanel(row, column).setSymbol(getCurrentPlayerNum());
			incrementTurn();
		}
		checkWinner();
		return getPanelSymbol(row, column);
	}

	/**
	 * Returns the symbol of the TTTPanel at the specified location.
	 * 
	 * @param row
	 *            The row of the TTTPanel.
	 * @param column
	 *            The column of the TTTPanel.
	 * @return the symbol of the TTTPanel.
	 */
	public int getPanelSymbol(int row, int column)
	{
		return getPanel(row, column).getSymbol();
	}

	/* Holds the current winner of the game.
	 * 0 == no winner (game not ended)
	 * 1 == X winner
	 * 2 == O winner
	 * -1 = draw (game ended)F */
	private int winner = 0;

	/**
	 * Returns the winner of the game.
	 * 
	 * @return the winner of the game.
	 */
	public int getWinner()
	{
		return winner;
	}

	// checks for winner, updates the current winner variable
	void checkWinner()
	{
		TTTPanel[] tempArray = new TTTPanel[3];
		// test horizontal
		for (int row = 0; row < 3; row++)
		{
			winner = threeInRow(panels[row]);
			if (winner != 0)
			{
				return;
			}
		}

		// test vertical
		for (int column = 0; column < 3; column++)
		{
			for (int row = 0; row <= 2; row++)
			{
				tempArray[row] = getPanel(row, column);
			}
			winner = threeInRow(tempArray);
			if (winner != 0)
			{
				return;
			}
		}

		// test diagonal, positive slope
		for (int x = 0, y = 2, i = 0; x < 3; x++, y--, i++)
		{
			tempArray[i] = getPanel(y, x);
		}
		winner = threeInRow(tempArray);
		if (winner != 0)
		{
			return;
		}

		// test diagonal, negative slope
		for (int x = 0, y = 0, i = 0; y < 3; x++, y++, i++)
		{
			tempArray[i] = getPanel(y, x);
		}
		winner = threeInRow(tempArray);
		if (winner != 0)
		{
			return;
		}
		if (turn > lastTurn)
		{
			winner = -1;
			return;
		}
		winner = 0;
		return;
	}

	// used by checkWinner, to see if there are three winning pieces in a row
	private int threeInRow(TTTPanel[] line)
	{
		if ((line[0].getSymbol() == line[1].getSymbol()) && (line[1].getSymbol() == line[2].getSymbol()))
		{
			return line[0].getSymbol();
		}
		return 0;
	}

}
