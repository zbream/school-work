package en.zackream.tictactoe.engine;

/**
 * Individual TicTacToe Panel for the TTTGame engine.
 * 
 * @author Zack Ream
 * 
 */
class TTTPanel
{
	// store current symbol
	private int symbol;

	/**
	 * Constructor.
	 */
	TTTPanel()
	{
		this.setSymbol(0);
	}

	/**
	 * Returns the current symbol of the Panel.
	 * 
	 * @return the current symbol of the Panel.
	 */
	int getSymbol()
	{
		return this.symbol;
	}

	/**
	 * Tests whether or not the panel is free.
	 * 
	 * @return True if the panel is free. Otherwise, false.
	 */
	boolean isFree()
	{
		return (this.getSymbol() == 0);
	}

	/**
	 * Set the current symbol of the Panel.
	 * 
	 * @param newSymbol
	 *            the new symbol to set to the Panel.
	 */
	void setSymbol(int newSymbol)
	{
		symbol = ((newSymbol >= 0 && newSymbol <= 2) ? newSymbol : 0);
	}

}
