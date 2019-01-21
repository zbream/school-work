using System;
using System.Windows.Controls;

namespace ZR.Calculator.RootAgent.Contracts
{
    interface IRootPresentation
    {
        void RegisterOnClose(EventHandler handler);

        void ShowUI();

        void SetInputUI(UserControl control);

        void SetOutputUI(UserControl control);
    }
}
