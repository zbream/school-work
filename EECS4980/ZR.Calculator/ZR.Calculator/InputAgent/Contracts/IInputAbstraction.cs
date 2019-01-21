using System.ComponentModel;

namespace ZR.Calculator.InputAgent.Contracts
{
    interface IInputAbstraction : INotifyPropertyChanged
    {
        string CurrentInputString { get; set; }

        bool IsSpeechEnabled { get; set; }
    }
}
