using System.ComponentModel;

using ZReam.Calculator.Math;

namespace ZReam.Calculator.OutputAgent.Contracts
{
    interface IOutputAbstraction : INotifyPropertyChanged
    {
        AST CurrentOutput { get; set; }

        string CurrentOutputTEX { get; }

        bool IsSpeechEnabled { get; set; }
    }
}
