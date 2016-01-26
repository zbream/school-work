package view;

import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import contract.ICalcView;

@SuppressWarnings("serial")
public class CalcView extends JFrame implements ICalcView
{
	private JTextField vInput;
	private JButton vMultiply;
	private JTextField vTotal;
	private JButton vClear;

	public CalcView()
	{
		vInput = new JTextField(10);
		vMultiply = new JButton("Multiply");
		vTotal = new JTextField(10);
		vTotal.setEditable(false);
		vClear = new JButton("Clear");

		JPanel content = new JPanel();
		content.setLayout(new FlowLayout());
		content.add(new JLabel("Input"));
		content.add(vInput);
		content.add(vMultiply);
		content.add(new JLabel("Total"));
		content.add(vTotal);
		content.add(vClear);

		this.setContentPane(content);
		this.pack();

		this.setTitle("Performs Simple Multiplication");
	}

	public void showInterface()
	{
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}

	public String getInput()
	{
		return vInput.getText();
	}

	public void setTotal(String total)
	{
		vTotal.setText(total);
	}

	public void showErrorMessage(String message)
	{
		JOptionPane.showMessageDialog(this, message, "Error", JOptionPane.ERROR_MESSAGE);
	}

	public void addMultiplyActionListener(ActionListener listener)
	{
		vMultiply.addActionListener(listener);

		// Multiply on ENTER
		vInput.addActionListener(listener);
	}

	public void addClearActionListener(ActionListener listener)
	{
		vClear.addActionListener(listener);

		// Clear on ESC
		vInput.addKeyListener(new KeyAdapter()
		{
			@Override
			public void keyPressed(KeyEvent e)
			{
				if (e.getKeyCode() == KeyEvent.VK_ESCAPE)
				{
					// we don't care about ActionEvent,
					// only that it occurred
					listener.actionPerformed(null);
				}
			}
		});
	}
}
