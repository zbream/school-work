package en.zackream.tictactoe.userinterface;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 * UserInterface Window to play TicTacToe.
 * <p>
 * It is made up of several tictactoe.userinterface.TTTPanel's layed out in a grid.
 * 
 * @author Zack Ream
 * 
 */
@SuppressWarnings("serial")
public class TTTWindow extends JFrame
{
	/**
	 * Main entry point for program.
	 */
	public static void main(String[] args)
	{
		// create new TTTWindow, allow it to run the game
		TTTWindow frame = new TTTWindow();
		frame.runGame();
	}

	/**
	 * Instance of a TicTacToe game engine.
	 */
	private en.zackream.tictactoe.engine.TTTGame gameEngine = new en.zackream.tictactoe.engine.TTTGame();

	/**
	 * A multi-dimensional array of userinterface TTTPanels.
	 */
	private TTTPanel[][] panels = new TTTPanel[3][3];

	/**
	 * A label displayed on the frame, to indicate game status.
	 */
	JLabel statusLabel = new JLabel();

	/**
	 * Constructor
	 */
	TTTWindow()
	{
		// set properties about the frame
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// divide the frame into two panels, one for the game and one for status
		JPanel game = new JPanel(), status = new JPanel();
		this.setLayout(new BorderLayout());
		this.add(game);
		this.add(status, BorderLayout.SOUTH);

		// set up two main panels
		status.add(statusLabel, BorderLayout.CENTER);
		game.setLayout(new GridLayout(3, 3));

		// create and add the userinterface TTTPanels
		for (int row = 0; row < 3; row++)
		{
			for (int column = 0; column < 3; column++)
			{
				panels[row][column] = new TTTPanel();
				panels[row][column].addMouseListener(new ClickListener(row, column));
				game.add(panels[row][column]);
			}
		}

		// make game panel a set square, resize the frame to fit this
		game.setPreferredSize(new Dimension(300, 300));
		this.pack();
		
		this.setLocationRelativeTo(null);

		// show instructions for first turn
		updateStatus();

		// make game invisible until runGame() is called
		this.setVisible(false);
	}

	/**
	 * Handler for clicking one of the userinterface TTTPanels.
	 * 
	 * @author Zack Ream
	 * 
	 */
	class ClickListener extends MouseAdapter
	{
		// store the associated panel's row and column
		int row, column;

		// constructor to set the associated panel's row and column
		public ClickListener(int row, int column)
		{
			this.row = row;
			this.column = column;
		}

		@Override
		public void mouseClicked(MouseEvent e)
		{
			TTTPanel sender = (TTTPanel) e.getSource();
			// set gameEngine's panel, and set this panel's symbol based on result
			sender.setSymbol(gameEngine.setPanelSymbol(row, column));
			// If the game has not ended (no winner), update the status. Otherwise, end the game.
			if (gameEngine.getWinner() == 0)
			{
				updateStatus();
			} else
			{
				endGame();
			}
		}
	}

	/**
	 * Start the game, making the frame visible.
	 */
	public void runGame()
	{
		this.setVisible(true);
	}

	/**
	 * Display the current game state on the statusLabel.
	 */
	public void updateStatus()
	{
		statusLabel.setText("Player " + gameEngine.getCurrentPlayerName() + ", enter a position.");
	}

	/**
	 * End the game
	 * <p>
	 * Disables clicking the panels, and writes the results in the StatusLabel.
	 */
	public void endGame()
	{
		// loop through panels, disabling mouse listeners
		for (int row = 0; row < 3; row++)
		{
			for (int column = 0; column < 3; column++)
			{
				for (MouseListener l : panels[row][column].getMouseListeners())
				{
					panels[row][column].removeMouseListener(l);
				}
			}
		}
		// If there is a winner, display him on the statusLabel. Otherwise, the game was a draw.
		if (gameEngine.getWinner() != 0 && gameEngine.getWinner() != -1)
		{
			statusLabel.setText("Game Over. " + (gameEngine.getWinner() == 1 ? "X" : "O") + " wins.");
		} else
		{
			statusLabel.setText("Game Over. Draw.");
		}
	}
}
