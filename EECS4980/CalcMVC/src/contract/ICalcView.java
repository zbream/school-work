package contract;

import java.awt.event.ActionListener;

public interface ICalcView
{
	public void showInterface();

	public String getInput();

	public void setTotal(String total);

	public void showErrorMessage(String message);

	public void addMultiplyActionListener(ActionListener listener);

	public void addClearActionListener(ActionListener listener);
}
