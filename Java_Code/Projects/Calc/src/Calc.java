// Calc.java -- Everything in one file.

//     A common style of programming is to put all processing
//     in the GUI.  This works Ok as long as the "model", the
//     logic, is so small that it isn't worth putting into
//     a separate class.  
//
//     However, mixing model with presentation usually makes the 
//     program hard to read, and the inevitable growth of the 
//     program leads to a mess.
//
//     This fails the simple Interface Independence test.
//       Could the model easily work with a command line or 
//       web interface? No.
//
//     It also fails the Model Independence test.
//       Could we easily change the model, eg, to BigDecimal?  No.

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.math.BigInteger;

public class Calc
{
	public static void main(String[] args)
	{
		JFrame window = new CalcGUI();
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.setTitle("Performs Simple Multiplications");
		window.setVisible(true);
	}
}

class CalcGUI extends JFrame
{
	private static final String INITIAL_VALUE = "1";

	private JTextField m_totalTf = new JTextField(10);
	private JTextField m_userInputTf = new JTextField(10);
	private JButton m_multiplyBtn = new JButton("Multiply");
	private JButton m_clearBtn = new JButton("Clear");

	private BigInteger m_total; // The total current value state.

	CalcGUI()
	{
		m_total = new BigInteger(INITIAL_VALUE);
		m_totalTf.setText(INITIAL_VALUE);
		m_totalTf.setEditable(false);

		JPanel content = new JPanel();
		content.setLayout(new FlowLayout());
		content.add(new JLabel("Input"));
		content.add(m_userInputTf);
		content.add(m_multiplyBtn);
		content.add(new JLabel("Total"));
		content.add(m_totalTf);
		content.add(m_clearBtn);

		this.setContentPane(content);
		this.pack();

		// ... Listener to do multiplication
		m_multiplyBtn.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				try
				{
					m_total = m_total.multiply(new BigInteger(m_userInputTf.getText()));
					m_totalTf.setText(m_total.toString());
				} catch (NumberFormatException nex)
				{
					JOptionPane.showMessageDialog(CalcGUI.this, "Bad Number");
				}
			}
		});

		// ... Listener to clear.
		m_clearBtn.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				m_total = new BigInteger(INITIAL_VALUE);
				m_totalTf.setText(INITIAL_VALUE);
			}
		});
	}
}
