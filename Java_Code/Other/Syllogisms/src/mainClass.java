import syllogisms.Argument;
import syllogisms.InvalidForm;


public class mainClass
{

	public static void main(String[] args) throws InvalidForm
	{
		Argument test = new Argument(126);
		
		System.out.println(test.getForm());
		System.out.println(test.toString());
		
	}
	
}
