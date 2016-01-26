import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.border.Border;
import javax.swing.border.LineBorder;

public class SwingLabels
{

	public static void main(String[] args)
	{
		// create frame
		JFrame frame = new JFrame("Exercise 12.08");
		frame.setSize(400, 300);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// create layout
		GridLayout grid = new GridLayout(2, 3);
		frame.setLayout(grid);

		myLabel[] labels = new myLabel[6];

		// create labels
		labels[0] = new myLabel(Color.black, "black");
		labels[1] = new myLabel(Color.blue, "blue");
		labels[2] = new myLabel(Color.cyan, "cyan");
		labels[3] = new myLabel(Color.green, "green");
		labels[4] = new myLabel(Color.magenta, "magenta");
		labels[5] = new myLabel(Color.orange, "orange");

		// add labels to frame
		for (int x=0; x<6; x++)
		{
			frame.add(labels[x]);
		}

		frame.setVisible(true);
	}
}

class myLabel extends JLabel
{
	public myLabel(Color foreground, String toolTip)
	{
		this.setText(toolTip);
		this.setForeground(foreground);
		this.setBorder(new LineBorder(Color.yellow));
		this.setFont(new Font("Times New Roman", 0, 20));
		this.setToolTipText(toolTip);
	}
}
