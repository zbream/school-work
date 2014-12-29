import java.awt.GridLayout;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;

public class FourCards
{

	public static void main(String[] args)
	{
		// create frame
		JFrame frame = new JFrame("Exercise 12.11");
		frame.setSize(304, 150);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// create layout
		GridLayout grid = new GridLayout(1, 4);
		frame.setLayout(grid);

		// add cards
		int[] cardNumbers = draw();
		Card[] cardButtons = new Card[4];
		for (int x = 0; x < 4; x++)
		{
			cardButtons[x] = new Card(cardNumbers[x]);
			frame.add(cardButtons[x]);
		}

		// show window
		frame.setVisible(true);
	}

	static int[] draw()
	{
		int[] cards = new int[4];
		do
		{
			for (int x = 0; x < 4; x++)
			{
				cards[x] = (int) (Math.random() * 54 + 1);
			}
		} while (notEqual(cards) == false);
		return cards;
	}

	static boolean notEqual(int[] cards)
	{
		for (int x = 0; x < 3; x++)
		{
			for (int y = x + 1; y < 4; y++)
			{
				if (cards[x] == cards[y])
				{
					return false;
				}
			}
		}
		return true;
	}

}

class Card extends JButton
{
	public Card(int drawNumber)
	{
		ImageIcon defaultIcon = new ImageIcon("image/card/b1fv.png");
		ImageIcon pressedIcon = new ImageIcon("image/card/" + drawNumber + ".png");
		this.setIcon(defaultIcon);
		this.setPressedIcon(pressedIcon);
	}
}