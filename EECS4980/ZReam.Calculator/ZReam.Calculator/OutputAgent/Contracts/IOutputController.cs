using System.Windows.Controls;

using ZReam.Calculator.Math;

namespace ZReam.Calculator.OutputAgent.Contracts
{
    interface IOutputController
    {
        UserControl GetUI();

        void UpdateOutput(AST syntaxTree);

        void RepeatSpeech();
    }
}
