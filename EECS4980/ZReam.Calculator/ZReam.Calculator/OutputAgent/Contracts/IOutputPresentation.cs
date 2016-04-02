using System.Windows.Controls;

namespace ZReam.Calculator.OutputAgent.Contracts
{
    interface IOutputPresentation
    {
        UserControl GetUI();
    }
}
