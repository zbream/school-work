using System.Windows.Controls;

namespace ZReam.Calculator.RootAgent.Contracts
{
    interface IRootPresentation
    {
        void ShowUI();

        void SetInputUI(UserControl control);

        void SetOutputUI(UserControl control);
    }
}
