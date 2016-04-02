using System.Windows.Controls;

namespace ZReam.Calculator.OutputAgent.Contracts
{
    interface IOutputController
    {
        UserControl GetUI();

        void ToggleSpeech(bool enable);

        void UpdateOutput(string outputVisible, string outputAudible);

        void RepeatSpeech();
    }
}
