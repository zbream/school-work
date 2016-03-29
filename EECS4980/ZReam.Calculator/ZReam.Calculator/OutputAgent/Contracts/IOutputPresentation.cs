using System.Windows.Controls;

namespace ZReam.Calculator.OutputAgent.Contracts
{
    interface IOutputPresentation
    {
        UserControl GetUI();

        void PlaySpeech(string text);

        void StopSpeech();
    }
}
