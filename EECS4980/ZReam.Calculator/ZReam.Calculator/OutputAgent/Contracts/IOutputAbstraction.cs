using System.ComponentModel;

namespace ZReam.Calculator.OutputAgent.Contracts
{
    interface IOutputAbstraction : INotifyPropertyChanged
    {
        string CurrentOutputVisible { get; set; }

        string CurrentOutputAudible { get; set; }

        bool IsSpeechEnabled { get; set; }
    }
}
