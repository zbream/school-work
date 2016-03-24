using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace ZReam.Calculator.RootAgent.Contracts
{
    interface IRootPresentation
    {
        void ShowInterface();

        void SetInputUI(UserControl control);

        void SetOutputUI(UserControl control);
    }
}
