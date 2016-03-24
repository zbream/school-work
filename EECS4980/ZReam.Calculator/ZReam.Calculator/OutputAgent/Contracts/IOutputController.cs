using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

using ZReam.Calculator.Math;

namespace ZReam.Calculator.OutputAgent.Contracts
{
    interface IOutputController
    {
        UserControl GetUI();

        void UpdateOutput(AST syntaxTree);

        void RepeatOutput();
    }
}
