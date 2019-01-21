using System.Windows.Controls;

namespace ZR.Calculator.OutputAgent.Contracts
{
    interface IOutputPresentation
    {
        UserControl GetUI();
    }
}
