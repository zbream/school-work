import contract.ICalcController;
import contract.ICalcModel;
import contract.ICalcView;
import controller.CalcController;
import model.CalcModel;
import view.CalcView;

public class CalcMVC
{
	public static void main(String[] args)
	{
		ICalcView view = new CalcView();
		ICalcModel model = new CalcModel();

		ICalcController controller = new CalcController(model, view);
		controller.start();
	}
}
