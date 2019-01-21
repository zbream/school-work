using System.Windows.Controls;

namespace ZR.Calculator.InputAgent.Contracts
{
    interface IInputController
    {
        UserControl GetUI();

        void ToggleSpeech(bool enable);
    }
}
