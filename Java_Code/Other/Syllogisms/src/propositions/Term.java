package propositions;

public class Term
{
	public Term(String name)
	{
		this.name = name; 
	}
	
	public Term(String name, boolean isComplemented)
	{
		this(name);
		this.complemented = isComplemented;
	}
	
	private String name;

	public String getName()
	{
		return name;
	}

	private boolean complemented;

	public boolean isComplemented()
	{
		return complemented;
	}

	@Override
	public String toString()
	{
		String output = "";
		if (isComplemented())
			output = "non-";
		return output + getName();
	}
}
