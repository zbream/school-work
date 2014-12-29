import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Polygon;
import java.awt.RenderingHints;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class SinCosMain
{
	/* Zack Ream
	 * Ex13.12 - Plot sin() and cos()
	 * 
	 * This program displays a plot of sin(x) and cos(x), by plotting values for
	 * sin and cos along a domain of x. It adds these polygons of points to the
	 * class DisplayPlot, which in turn graphs them on a plot. */

	public static void main(String[] args)
	{
		// create frame to display our program
		JFrame frame = new JFrame();
		frame.setSize(420, 240);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// create a new panel to show plot, add it to our frame
		DisplayPlot plot = new DisplayPlot();
		frame.add(plot, BorderLayout.CENTER);

		// add plot of sin(x) to plot panel
		Polygon plotSin = new Polygon();
		for (int x = -170; x <= 170; x++)
		{
			plotSin.addPoint(x + 200, 100 - (int) (50 * Math.sin((x / 100.0) * 2 * Math.PI)));
		}
		plot.addPlot(plotSin, Color.red);

		// add plot of cos(x) to plot panel
		Polygon plotCos = new Polygon();
		for (int x = -170; x <= 170; x++)
		{
			plotCos.addPoint(x + 200, 100 - (int) (50 * Math.cos((x / 100.0) * 2 * Math.PI)));
		}
		plot.addPlot(plotCos, Color.blue);

		// show the frame
		frame.setVisible(true);

	}

}

class DisplayPlot extends JPanel
{
	/* Zack Ream
	 * 
	 * This class is a panel on which to draw graphics.
	 * 
	 * It is used to draw axes of a X-Y plane, and plots added to it using the
	 * addPlot function. These plots take the form of Polygons, which hold x,y
	 * values for a domain of x-values. */

	// when this panel is repainted, paint on it our graphics
	@Override
	protected void paintComponent(Graphics g)
	{
		// clear the canvas
		super.paintComponent(g);

		Graphics2D g2 = (Graphics2D) g;
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		// draw axes
		// g2.drawLine(200, 10, 200, 190);
		// g2.drawLine(10, 100, 390, 100);
		g2.drawLine(getWidth() / 2, 10, getWidth() / 2, getHeight() - 10);
		g2.drawLine(10, getHeight() / 2, getWidth() - 10, getHeight() / 2);

		// draw axes labels
		// g2.drawString("Y", 210, 20);
		// g2.drawString("X", 380, 112);
		g2.drawString("Y", getWidth() / 2 + 10, 20);
		g2.drawString("X", getWidth() - 20, getHeight() / 2 + 12);

		// draw strings for x-values on the graph
		g2.drawString("-2\u03c0", 100, 120);
		g2.drawString("-\u03c0", 150, 120);
		g2.drawString("0", 200, 120);
		g2.drawString("\u03c0", 250, 120);
		g2.drawString("2\u03c0", 300, 120);

		// draw plots from plotList
		for (int plotCounter = 0; plotCounter < plotCount; plotCounter++)
		{
			g2.setColor(colorList[plotCounter]);
			g2.drawPolyline(plotList[plotCounter].xpoints, plotList[plotCounter].ypoints, plotList[plotCounter].npoints);
		}

	}

	// array to hold a list of polygons that are the plots added to the panel
	private Polygon[] plotList = new Polygon[5];
	private Color[] colorList = new Color[5];
	private int plotCount = 0;

	// method to add a plot to this panel
	public void addPlot(Polygon p, Color c)
	{
		plotList[plotCount] = p;
		colorList[plotCount++] = c;
		this.repaint();
	}
}