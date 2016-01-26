import java.awt.*;
import javax.swing.*;

public class Checker
{

	/* Zack Ream
	 * Ex12.10 - Display a Checkerboard
	 * 
	 * This program displays an 8x8 checkerboard of buttons with alternating
	 * black/white panels. */

	public static void main(String[] args)
	{
		// create a frame for the window
		JFrame frame = new JFrame("Exercise 12.10");
		frame.setSize(400, 400);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		// create a grid layout, 8x8, set it to frame
		GridLayout grid = new GridLayout(8, 8);
		frame.setLayout(grid);
		
		// create components
		for (int row = 1; row <= grid.getRows(); row++)
		{
			for (int column = 1; column <= grid.getColumns(); column++)
			{
				// create a new button
				JButton button = new JButton();
				// if column=odd, WHITE. if column=even, BLACK.
				// the row number swaps these, so just add row to column
				Color col;
				col = ((column + row) % 2 == 0) ? Color.WHITE : Color.BLACK;
				button.setBackground(col);
				// add the button to the frame
				frame.add(button);

			}
		}

		// show the frame (window)
		frame.setVisible(true);
	}

}
