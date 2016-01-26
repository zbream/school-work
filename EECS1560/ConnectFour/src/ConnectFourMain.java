import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridLayout;
import java.awt.RenderingHints;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class ConnectFourMain
{

	public static void main(String[] args)
	{
		// create frame for window
		JFrame frame = new JFrame("Connect Four");
		frame.setSize(300, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLocationRelativeTo(null);

		// create new board, add it to frame
		C4Board board;
		if (args.length != 2)
		{
			board = new C4Board();
		} else
		{
			board = new C4Board(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
		}
		frame.add(board);
		// show the frame
		frame.pack();
		frame.setVisible(true);

		// run a round of ConnectFour
		board.runGame();
	}
}

@SuppressWarnings("serial")
class C4Board extends JPanel
{
	// array of columns
	private int columnCount = 0, rowCount = 0;
	private C4Column[] columns;

	// accessor for specified column
	public C4Column getColumn(int column)
	{
		return columns[column];
	}

	// create GUI components
	JPanel game = new JPanel(), top = new JPanel(), bottom = new JPanel();
	JLabel statusLabel = new JLabel("CONNECTFOUR");

	// constructor
	public C4Board(int setColumns, int setRows)
	{
		// initialize column and row count
		columnCount = setColumns;
		rowCount = setRows;

		// divide game panel into column grid
		game.setBackground(Color.BLUE);
		game.setLayout(new GridLayout(1, columnCount));
		// add statusLabel to status panel
		bottom.add(statusLabel);

		// set layout for main panel, add components
		this.setLayout(new BorderLayout());
		top.setLayout(new BorderLayout());
		top.add(game, BorderLayout.CENTER);

		this.add(top);
		this.add(bottom, BorderLayout.SOUTH);

		// initialize each column, add listeners
		columns = new C4Column[columnCount];
		for (int i = 0; i < columnCount; i++)
		{
			columns[i] = new C4Column(i, rowCount);
			columns[i].addMouseListener(new ClickListener());
			game.add(columns[i]);
		}
	}

	public C4Board()
	{
		this(7, 6);
	}

	// game properties, initialized at incrementTurn method
	int turn = 0;
	int winner = 0;
	
	String playerName()
	{
		return (turn % 2 != 0) ? "Red" : "Yellow";
	}
	
	int playerNum()
	{
		return ((turn + 1) % 2) + 1;
	}

	// method that activates a round of ConnectFour
	public void runGame()
	{
		incrementTurn();
		this.setVisible(true);
	}

	private void incrementTurn()
	{
		turn++;
		statusLabel.setText("Player " + playerName() + ", click a column.");
	}

	// object to listen for mouse events on the columns
	class ClickListener extends MouseAdapter
	{
		// when mouse is clicked, add piece if possible
		@Override
		public void mouseClicked(MouseEvent e)
		{
			// cast event source as 'sender'
			C4Column sender = (C4Column) e.getSource();
			// addPeg returns {set success, set column, set row}
			// set success is 1/0, success/fail
			int[] setReturn;
			setReturn = sender.addPeg(playerNum());
			if (setReturn[0] == 1) // set was a success
			{
				// go to next turn
				incrementTurn();
				isWinner(setReturn[1], setReturn[2]);
			}
		}
	}

	public void isWinner(int setColumn, int setRow)
	{
		/* When a piece is placed, this method searches the row, column, and
		 * diagonals emanating from the placed point. This is sufficient, since
		 * a win can only take place along where the piece is placed. it
		 * generates arrays of values, sent from the fourInRow method which
		 * looks for a win.
		 * 
		 * returns 0: No Win
		 * returns 1: Red Wins
		 * returns 2: Yellow Wins */

		// use temporary array to hold values passed to fourInRow method
		int[] tempArray;
		int winner;

		// generate and test horizontal row array
		tempArray = new int[columnCount];
		for (int i = 0; i < columnCount; i++)
		{
			tempArray[i] = getColumn(i).getPanel(setRow).getPeg();
		}
		winner = fourInRow(tempArray);
		// if winner != 0, then there is a winner in the horizontal row
		if (winner != 0)
		{
			endGame(winner);
			return;
		}

		// generate and test vertical column array
		tempArray = new int[rowCount];
		for (int i = 0; i < rowCount; i++)
		{
			tempArray[i] = getColumn(setColumn).getPanel(i).getPeg();
		}
		winner = fourInRow(tempArray);
		// if winner != 0, then there is a winner in the vertical column
		if (winner != 0)
		{
			endGame(winner);
			return;
		}

		// generate and test diagonal array, positive slope
		tempArray = new int[Math.max(columnCount, rowCount)];
		int x = setColumn, y = setRow;
		/* count down positions to bottom left, until we find the coordinate of
		 * the border */
		while ((x > 0) && (y < rowCount - 1))
		{
			x--;
			y++;
		}
		/* Now, x and y hold the coordinate of the bottom left edge of the
		 * positive diagonal. We can loop through the values diagonally,
		 * generating an array of values until we reach the upper right end of
		 * the diagonal, where x=(columnCount-1) or y=0. */
		int i = 0;
		while (x <= columnCount - 1 && y >= 0)
		{
			tempArray[i] = getColumn(x).getPanel(y).getPeg();
			x++;
			y--;
			i++;
		}
		winner = fourInRow(tempArray);
		// if winner != 0, then there is a winner in the positive diagonal
		if (winner != 0)
		{
			endGame(winner);
			return;
		}

		// generate and test diagonal array, negative slope
		tempArray = new int[Math.max(columnCount, rowCount)];
		x = setColumn;
		y = setRow;
		/* count down positions to top left, until we find the coordinate of
		 * the border */
		while (x > 0 && y > 0)
		{
			x--;
			y--;
		}
		/* Now, x and y hold the coordinate of the top left edge of the negative
		 * diagonal. We can loop through the values diagonally, generating an
		 * array of values until we reach the lower right end of the diagonal,
		 * where x=(columnCount-1) or y=(rowCount-1). */
		i = 0;
		while (x <= columnCount - 1 && y <= rowCount - 1)
		{
			tempArray[i] = getColumn(x).getPanel(y).getPeg();
			x++;
			y++;
			i++;
		}
		winner = fourInRow(tempArray);
		// if winner != 0, then there is a winner in the negative diagonal
		if (winner != 0)
		{
			endGame(winner);
			return;
		}

		// if turns are up, there are no more moves, draw
		if (turn == rowCount * columnCount + 1)
		{
			endGame(0);
			return;
		}
	}

	private int fourInRow(int[] seq)
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

			/* after going through a group of four, if isWin is still true,
			 * there is a match, return the winner, the value of any of the
			 * four
			 * elements */
			if (isWin == true)
			{
				return seq[i];
			}
		}
		/* if we make it this far, then there was no win in any group of four:
		 * no winner */
		return 0;
	}

	private void endGame(int winner)
	{
		// loop through columns, disabling mouse listeners
		for (int column = 0; column < columnCount; column++)
		{
			for (MouseListener l : getColumn(column).getMouseListeners())
			{
				getColumn(column).removeMouseListener(l);
			}
		}
		// if winner is not 0, there was a winner. Set status to winner
		// if winner is 0, the game was a draw
		if (winner != 0)
		{
			statusLabel.setText("Game Over. " + (winner == 1 ? "Red" : "Yellow") + " wins.");
		} else
		{
			statusLabel.setText("Game Over. Draw.");
		}
	}

}

@SuppressWarnings("serial")
class C4Column extends JPanel
{
	private int rowCount = 0;
	private C4Panel[] panels;
	private int columnPos;

	// constructor, creates <rowCount> panels
	public C4Column(int column, int setRowCount)
	{
		// make background transparent (board shows through)
		this.setOpaque(false);

		columnPos = column;

		// mutate row count, initialize panel array
		rowCount = setRowCount;
		panels = new C4Panel[rowCount];

		// divide column into rows
		this.setLayout(new GridLayout(rowCount, 1));

		// initialize each panel
		for (int row = 0; row < rowCount; row++)
		{
			panels[row] = new C4Panel(row);
			this.add(panels[row]);
		}
	}

	// accessor for panel at specified row (0 starting at top)
	public C4Panel getPanel(int row)
	{
		return panels[row];
	}

	public int getPosition()
	{
		return columnPos;
	}

	public int[] addPeg(int color)
	{
		for (int y = rowCount - 1; y >= 0; y--)
		{
			if (getPanel(y).setPeg(color) == true) // set successful
			{
				int[] retVals = { 1, this.getPosition(), getPanel(y).getPosition() };
				return retVals;
			}
		}
		return new int[] { 0, 0, 0 };
	}
}

@SuppressWarnings("serial")
class C4Panel extends JPanel
{
	// hold color of peg: 1-RED, 2-YELLOW
	private int peg = 0;
	private int rowPos;

	// constructor to set peg empty (0)
	public C4Panel(int row)
	{
		// make background transparent (board shows through)
		this.setOpaque(false);
		this.setPreferredSize(new Dimension(50,50));

		// mutate position values
		rowPos = row;
		// set peg to empty space
		setPeg(0);
	}

	public int getPosition()
	{
		return rowPos;
	}

	// mutator for current peg, returns true if successful
	public boolean setPeg(int x)
	{
		if (peg == 0)
		{
			peg = ((x >= 0 && x <= 2) ? x : 0);
			this.repaint();
			return true;
		}
		return false;
	}

	// accessor for current peg
	public int getPeg()
	{
		return peg;
	}

	// redraw the circle on paintComponent, padding sets distance from border
	@Override
	protected void paintComponent(Graphics g)
	{
		final int padding = 2;
		super.paintComponent(g);

		Graphics2D g2 = (Graphics2D) g;
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		g2.setColor(Color.WHITE);

		if (peg == 1) // RED
		{
			g2.setColor(Color.RED);
		}
		if (peg == 2) // YELLOW
		{
			g2.setColor(Color.YELLOW);
		}
		g2.fillOval(padding, padding, getWidth() - 2 * padding, getHeight() - 2 * padding);

		g2.setColor(Color.BLACK);

		g2.setStroke(new BasicStroke(2f));

		g2.drawOval(padding, padding, getWidth() - 2 * padding, getHeight() - 2 * padding);

	}
}