using System.Windows.Controls;

namespace ZReam.Calculator.InputAgent.Contracts
{
    interface IInputController
    {
        UserControl GetUI();

        void ToggleSpeech(bool enable);
    }
}
