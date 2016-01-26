package controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import contract.ICalcController;
import contract.ICalcModel;
import contract.ICalcView;

public class CalcController implements ICalcController
{
	private ICalcModel model;
	private ICalcView view;

	public CalcController(ICalcModel model, ICalcView view)
	{
		this.model = model;
		this.view = view;

		initializeView();
	}
	
	public void start()
	{
		view.showInterface();
	}

	private void initializeView()
	{
		view.addMultiplyActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				try
				{
					model.multiply(view.getInput());
					view.setTotal(model.getTotal());
				} catch (NumberFormatException ex)
				{
					view.showErrorMessage("Bad Number");
				}
			}
		});

		view.addClearActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				model.clear();
				view.setTotal(model.getTotal());
			}
		});

		view.setTotal(model.getTotal());
	}
}
