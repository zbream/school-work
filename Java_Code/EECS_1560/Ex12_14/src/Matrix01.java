import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;

public class Matrix01
{

	public static void main(String[] args)
	{
		// create frame
		JFrame frame = new JFrame("Exercise 12.14");
		frame.setSize(500, 500);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// create layout grid
		GridLayout grid = new GridLayout(10, 10);
		frame.setLayout(grid);

		// add controls
		for (int x = 0; x < 100; x++)
		{
			frame.add(new digit(rand()));
		}

		// show window
		frame.setVisible(true);
	}

	static int rand()
	{
		return (int) (Math.random() * 2);
	}

}

class digit extends JLabel
{
	public digit(int number)
	{
		this.setText(number + "");
		this.setHorizontalAlignment(CENTER);
		this.setVerticalAlignment(CENTER);
	}
}