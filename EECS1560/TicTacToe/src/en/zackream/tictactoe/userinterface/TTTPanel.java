package en.zackream.tictactoe.userinterface;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class TTTPanel extends JPanel
{
	private int symbol;

	TTTPanel()
	{
		// initialize as a blank tile
		setSymbol(0);
	}

	void setSymbol(int newSymbol)
	{
		symbol = newSymbol;
		this.repaint();
	}

	@Override
	protected void paintComponent(Graphics g)
	{
		// draw the current symbol of the panel
		super.paintComponent(g);

		Graphics2D g2 = (Graphics2D) g;
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		if (symbol == 1) // X
		{
			g2.drawLine(10, 10, this.getWidth() - 10, this.getHeight() - 10);
			g2.drawLine(this.getWidth() - 10, 10, 10, this.getHeight() - 10);
		}
		if (symbol == 2) // O
		{
			g2.drawOval(10, 10, this.getWidth() - 20, this.getHeight() - 20);
		}
	}

}
