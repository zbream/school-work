using System.ComponentModel;

namespace ZReam.Calculator.InputAgent.Contracts
{
    interface IInputAbstraction : INotifyPropertyChanged
    {
        string CurrentInputString { get; set; }

        bool IsSpeechEnabled { get; set; }
    }
}
