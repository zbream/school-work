package model;

import java.math.BigInteger;

import contract.ICalcModel;

public class CalcModel implements ICalcModel
{
	private static final String INITIAL_VALUE = "1";

	private BigInteger total;

	public CalcModel()
	{
		clear();
	}

	public void clear()
	{
		total = new BigInteger(INITIAL_VALUE);
	}

	public void multiply(String n) throws NumberFormatException
	{
		total = total.multiply(new BigInteger(n));
	}

	public String getTotal()
	{
		return total.toString();
	}
}