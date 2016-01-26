import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.EmptyBorder;

/* Zack Ream
 * FifteenSquare Project
 * 
 * This class sets up and runs games of a FifteenSquare puzzle.
 * Customizable Game constants (shuffle count, frame size, etc) are set at the top of the class.
 * It sets up a 4x4 grid of buttons to use as tiles, reused for as long as the frame is open.
 * The frame is divided into two panels in one column. The top boardPanel holds the tiles, and the bottom interfacePanel holds the program buttons.
 * It provides a method newGame to create a new game, restoring the game to its initial state.
 * It provides a method shuffle to shuffle the board to create a solvable result.
 * After each click of a tile, it moves the blank to its position, keeping track of moves, and checks for a winner.
 * 
 * The solution is found if the user gets the board back in the form of:
 * +---+---+---+---+
 * | 1 | 2 | 3 | 4 |
 * +---+---+---+---+
 * | 5 | 6 | 7 | 8 |
 * +---+---+---+---+
 * | 9 | 10| 11| 12|
 * +---+---+---+---+
 * | 13| 14| 15|   |
 * +---+---+---+---+
 *
 * The Hint, Save, and Load buttons are reserved for further functionality.
 */
@SuppressWarnings("serial")
public class FifteenSquare extends JFrame
{
	// constant to hold the number of clicks made through Shuffle()
	final int SHUFFLE_COUNT = 5000;

	// constants for size of the JFrame (the window size)
	final int FRAME_WIDTH = 400;
	final int FRAME_HEIGHT = 500;

	// Main entry-point for the program. Creates a new FifteenSquare frame.
	public static void main(String[] args) throws ClassNotFoundException, InstantiationException, IllegalAccessException, UnsupportedLookAndFeelException
	{
		// set visual style to current system style (ie. Windows 7/8)
		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());

		// create a new FifteenSquare frame, which shows the UI
		@SuppressWarnings("unused")
		FifteenSquare frame = new FifteenSquare();
	}

	// multi-dimensional array of JButtons to hold our tiles
	JButton[][] tiles;

	// game properties
	int gamesPlayed = 0, gamesWon = 0, moves = 0;
	boolean isShuffling = false;

	// separate GUI panels for board and interface
	JPanel boardPanel = new JPanel();
	JPanel interfacePanel = new JPanel();

	// label to tell the player the status of the game
	JLabel statsLabel = new JLabel("Moves: ");

	// constructor for FifteenSquare frame
	public FifteenSquare()
	{
		// set properties of this JFrame
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);

		/* A JFrame's setSize method includes the window's border. By setting the ContentPane's PreferredSize and
		 * packing the JFrame, we set the ContentPane's actual size. */
		this.getContentPane().setPreferredSize(new Dimension(FRAME_WIDTH, FRAME_HEIGHT));
		this.pack();

		// start frame in center of screen (after previously resizing it using .pack())
		this.setLocationRelativeTo(null);

		// we wish to place our tiles on the panel manually
		boardPanel.setLayout(null);

		// set size of boardPanel to frame width x frame width
		boardPanel.setPreferredSize(new Dimension(FRAME_WIDTH, FRAME_WIDTH));
		// set size of interfacePanel to remaining space in the frame
		interfacePanel.setPreferredSize(new Dimension(FRAME_WIDTH, FRAME_HEIGHT - FRAME_WIDTH));

		// add the panels to the frame
		this.add(boardPanel);
		this.add(interfacePanel, BorderLayout.SOUTH);

		// create single listener for keypresses (a button is always in focus)
		TileKeyHandler tileKeyHandler = new TileKeyHandler();

		// initialize board panel buttons
		tiles = new JButton[4][4];
		final int SIDE_PADDING = 20, TILE_PADDING = 10;
		final int TILE_WIDTH = (FRAME_WIDTH - 2 * SIDE_PADDING - 3 * TILE_PADDING) / 4;
		// loop through each row of buttons
		for (int row = 0; row < 4; row++)
		{
			// find y-coordinate of current row of buttons
			final int yCoord = SIDE_PADDING + row * (TILE_WIDTH + TILE_PADDING);

			// loop through each column of each row of buttons
			for (int column = 0; column < 4; column++)
			{
				// find x-coordinate of current button
				final int xCoord = SIDE_PADDING + column * (TILE_WIDTH + TILE_PADDING);

				// create new button
				tiles[row][column] = new JButton();
				// set button properties (font, size)
				tiles[row][column].setFont(tiles[row][column].getFont().deriveFont((float) 40));
				tiles[row][column].setBounds(xCoord, yCoord, TILE_WIDTH, TILE_WIDTH);

				// add property listener to make button visible/invisible depending on number
				tiles[row][column].addPropertyChangeListener(new PropertyChangeListener()
				{
					@Override
					public void propertyChange(PropertyChangeEvent e)
					{
						// check if the source of the event firing was a text change
						if (e.getPropertyName().equals("text"))
						{
							// create button reference "sender", from event source
							JButton sender = (JButton) e.getSource();
							// make button invisible if text is 0, visible otherwise
							sender.setVisible((!e.getNewValue().equals("0")));
						}
					}
				});

				// add listener for button click, set values in constructor (see TileClickHandler declaration)
				tiles[row][column].addActionListener(new TileClickHandler(row, column));

				// add listener for key press
				tiles[row][column].addKeyListener(tileKeyHandler);

				// add button to boardPanel
				boardPanel.add(tiles[row][column]);
			}
		}

		// initialize lower interface panel buttons
		JButton save = new JButton("Save");
		JButton load = new JButton("Load");
		JButton hint = new JButton("Hint");
		JButton newGame = new JButton("New");
		JButton help = new JButton("Help");
		JButton exit = new JButton("Exit");

		// create "Help" JOptionPane.showOptionDialog label
		final JLabel[] helpLabel = new JLabel[5];
		helpLabel[0] = new JLabel("You can click a tile to slide it into the empty space.");
		helpLabel[1] = new JLabel("Adjacent tiles in the way are also moved first.");
		helpLabel[2] = new JLabel();
		helpLabel[3] = new JLabel("Your goal is to move the puzzle into the solved state:");
		helpLabel[4] = new JLabel(
				"<html>+---+---+---+---+<p>| 1 | 2 | 3 | 4 |<p>+---+---+---+---+<p>| 5 | 6 | 7 | 8 |<p>+---+---+---+---+<p>| 9 | 10| 11| 12|<p>+---+---+---+---+<p>| 13| 14| 15|\u00A0\u00A0\u00A0|<p>+---+---+---+---+</html>");
		helpLabel[4].setFont(new Font("Monospaced", Font.PLAIN, helpLabel[4].getFont().getSize()));
		for (int i = 0; i <= 4; i++)
		{
			helpLabel[i].setHorizontalAlignment(JLabel.CENTER);
		}

		// handler for interface buttons
		class interfaceHandler implements ActionListener
		{
			@Override
			public void actionPerformed(ActionEvent arg0)
			{
				// get text on the button
				String source = ((JButton) arg0.getSource()).getText();
				// run commands based on what the button text is
				switch (source.toLowerCase())
				{
				case "new":
					newGame();
					shuffle();
					break;
				case "help":
					JOptionPane.showOptionDialog(FifteenSquare.this, helpLabel, "FifteeenSquare - Help", 0, JOptionPane.PLAIN_MESSAGE, null, new String[] { "OK, Let's Play" },
							"OK, Let's Play");
					break;
				case "exit":
					System.exit(0);
					break;
				default:
					System.out.println("\"" + source + "\" button not yet implemented.");
					break;
				}
			}
		}
		interfaceHandler iHandler = new interfaceHandler();

		// add handler to interface buttons
		save.addActionListener(iHandler);
		load.addActionListener(iHandler);
		hint.addActionListener(iHandler);
		newGame.addActionListener(iHandler);
		help.addActionListener(iHandler);
		exit.addActionListener(iHandler);

		// disable access to placeholders
		hint.setEnabled(false);
		save.setEnabled(false);
		load.setEnabled(false);

		// Add interface components to interface panel.
		// To simplify laying out the interface, the buttons are added in Grids of two.
		interfacePanel.setLayout(new GridLayout(1, 4, TILE_PADDING, 0));
		interfacePanel.setBorder(new EmptyBorder(SIDE_PADDING, SIDE_PADDING, SIDE_PADDING, SIDE_PADDING));
		JPanel buttonCouple;
		GridLayout buttonCoupleLayout = new GridLayout(2, 1, 0, TILE_PADDING);

		buttonCouple = new JPanel(buttonCoupleLayout);
		buttonCouple.add(save);
		buttonCouple.add(load);
		interfacePanel.add(buttonCouple);

		buttonCouple = new JPanel(buttonCoupleLayout);
		buttonCouple.add(hint);
		buttonCouple.add(newGame);
		interfacePanel.add(buttonCouple);

		buttonCouple = new JPanel(buttonCoupleLayout);
		buttonCouple.add(help);
		buttonCouple.add(exit);
		interfacePanel.add(buttonCouple);

		statsLabel.setVerticalAlignment(JLabel.TOP);
		interfacePanel.add(statsLabel);

		// show the form, start the first game
		this.setVisible(true);
		newGame();
		shuffle();
	}

	/* Handler class for tile clicks.
	 * Each instance stores the row and column of its associated button for later actionPerformed calls. */
	class TileClickHandler implements ActionListener
	{
		// store row and column of associated button
		int row, column;

		// constructor to get row and column of associated button
		public TileClickHandler(int row, int column)
		{
			this.row = row;
			this.column = column;
		}

		// method for button click
		@Override
		public void actionPerformed(ActionEvent arg0)
		{
			// makeMove using the associated row and column
			makeMove(row, column);
		}
	}

	/* Handler class for tile key presses.
	 * An arrow key press will fill the gap from whatever direction you pressed. */
	class TileKeyHandler extends KeyAdapter
	{
		@Override
		public void keyPressed(KeyEvent arg0)
		{
			// find blank's row and column
			int blankPos = findBlank();
			int r = row(blankPos);
			int c = column(blankPos);
			
			// get key pressed, ignore everything but arrow keys
			switch (arg0.getKeyCode())
			{
			case 37:
				// left
				c += 1;
				break;
			case 38:
				// up
				r += 1;
				break;
			case 39:
				// right
				c -= 1;
				break;
			case 40:
				// down
				r -= 1;
				break;
			default:
				return;
			}

			// ensure button press is valid
			if(r / 4 == 0 && c / 4 == 0 && c >= 0 && r >= 0)
			{
				makeMove(r,c);
			}
		}
	}

	/* Defer move-making to its own method.
	 * The Shuffle() method can call this instead of .doClick() of the tile to make a move.
	 * This greatly speeds up shuffling. */
	void makeMove(int row, int column)
	{
		// get the current position of the blank tile
		int blankPos = findBlank();
		int blankRow = row(blankPos);
		int blankColumn = column(blankPos);

		// if either the row or the column (exclusively) match the blank's position, the move is valid
		if (row == row(blankPos) ^ column == column(blankPos))
		{
			int gap;
			// if the blank and this tile match in row, move columns
			if (row == row(blankPos))
			{
				// set gap to distance between blank tile and this tile
				gap = Math.abs(column - column(blankPos));
				// perform 'gap' moves, essentially closing the gap
				for (int counter = gap; counter > 0; counter--)
				{
					// each tile movement counts as a move
					incrementMoves();
					if (column < blankColumn)
					{
						// shift blank to the left
						tiles[row][column + counter].setText(tiles[row][column + counter - 1].getText());
						tiles[row][column + counter - 1].setText("0");
					}
					if (blankColumn < column)
					{
						// shift blank to the right
						tiles[row][column - counter].setText(tiles[row][column - counter + 1].getText());
						tiles[row][column - counter + 1].setText("0");
					}
				}
			}
			// if the blank and this tile match in column, move rows
			if (column == column(blankPos))
			{
				// set gap to distance between blank tile and this tile
				gap = Math.abs(row - row(blankPos));
				// perform 'gap' moves, essentially closing the gap
				for (int counter = gap; counter > 0; counter--)
				{
					// each tile movement counts as a move
					incrementMoves();
					if (row < blankRow)
					{
						// shift blank up
						tiles[row + counter][column].setText(tiles[row + counter - 1][column].getText());
						tiles[row + counter - 1][column].setText("0");
					}
					if (blankRow < row)
					{
						// shift blank down
						tiles[row - counter][column].setText(tiles[row - counter + 1][column].getText());
						tiles[row - counter + 1][column].setText("0");
					}
				}
			}

			// check for winner if the board is not currently shuffling
			if (!isShuffling)
			{
				if (isSolved())
				{
					JOptionPane.showMessageDialog(null, "The board is correctly solved!", "Winner!", JOptionPane.INFORMATION_MESSAGE);
					gamesWon++;
					updateStatsLabel();
				}
			}
		}
	}

	// update status label with move count and game stats
	void updateStatsLabel()
	{
		// format the string using html (to make it multi-line)
		String text = "<html>Moves: " + moves + "<br><br>Played: " + gamesPlayed + "<br>Won: " + gamesWon + "</html>";
		statsLabel.setText(text);
	}

	// update status label after incrementing move count
	void incrementMoves()
	{
		moves++;
		updateStatsLabel();
	}

	// reset the board to initial (0 through 15) state
	public void newGame()
	{
		gamesPlayed++;
		updateStatsLabel();
		int counter = 0;
		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				tiles[row][column].setText(Integer.toString(counter++));
			}
		}
	}

	/* Shuffle the board.
	 * The method swaps the 0 and 15 tiles to create a solvable board.
	 * It then loops through SHUFFLE_COUNT shuffles, clicking random possible moves (as described later in the method). */
	void shuffle()
	{
		// make frame title indicate shuffling state
		this.setTitle("FifteenSquare - Shuffling");
		// set property that the board is currently shuffling (this prevents it from checking for winners after each
		// move)
		isShuffling = true;
		// hide the interface panel (essentially to hide the statusLabel)
		interfacePanel.setVisible(false);

		// swap 0 and 15 tile (assuming the board has been reset to its newGame() state).
		tiles[0][0].setText("15");
		tiles[3][3].setText("0");

		// shuffle for 'SHUFFLE_COUNT' times
		for (int counter = 0; counter < SHUFFLE_COUNT;)
		{
			int blankPos = findBlank();
			/* Generate random number between 0 and 5.
			 * If the number is odd, click a button in the same column as blank.
			 * If the number is even, click a button in the same row as blank.
			 * The random [number mod 3] (ranged 0-2) determines which of the 3 available buttons is clicked.
			 * If the [number mod 3] happens to be the blank space, then click the 4th button. */
			int random = (int) (Math.random() * 6);
			int randomButton = random % 3;
			counter++;
			if (random % 2 == 0)
			{
				// number even, click in same column as blank

				// if we happen to have chosen the blank space, choose the 4th remaining tile.
				if (randomButton == row(blankPos))
				{
					randomButton = 3;
				}
				//tiles[randomButton][column(blankPos)].doClick();
				makeMove(randomButton, column(blankPos));
			} else
			{
				// number odd, click in same row as blank

				// if we happen to have chosen the blank space, choose the 4th remaining tile.
				if (randomButton == column(blankPos))
				{
					randomButton = 3;
				}
				//tiles[row(blankPos)][randomButton].doClick();
				makeMove(row(blankPos), randomButton);
			}
		}
		// reset move count, update the status label to 0 moves
		moves = 0;
		updateStatsLabel();
		// reset the normal Frame Title
		this.setTitle("FifteenSquare");
		// set isShuffling state to false
		isShuffling = false;
		// reshow the interfacePanel
		interfacePanel.setVisible(true);
	}

	/* Check whether or not the board is solved.
	 * The solved state is one of increasing numbers from (1 to 15) plus 0.
	 * We can loop column by column, row by row, to check if each new value is greater than the previous.
	 * By assuming the 0 after 15 is a 16, this works for the whole board. */
	public boolean isSolved()
	{
		int previous = 0;
		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				int current = Integer.parseInt(tiles[row][column].getText());
				// if current tile is 0, assume it is 16 for purpose of checking order
				current = (current != 0 ? current : 16);
				// if previous is not less then the current, then the board is not solved
				if (!(previous < current))
				{
					return false;
				}
				previous = current;
			}
		}
		// the tiles increased from 1-15 plus 0, the board is solved
		return true;
	}

	// Find the position (0-15) of the blank space. It loops through columns and rows to find the 0.
	public int findBlank()
	{
		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				if (tiles[row][column].getText().equals("0"))
				{
					return (4 * row + column);
				}
			}
		}
		return -1;
	}

	// get row number (0-2) of the passed position
	private int row(int position)
	{
		return position / 4;
	}

	// get column number (0-2) of the passed position
	private int column(int position)
	{
		return position % 4;
	}
}
