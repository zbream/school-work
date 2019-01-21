using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Input;
using ZR.Calculator.InputAgent.Contracts;

namespace ZR.Calculator.InputAgent
{
    class InputAbstraction : IInputAbstraction
    {
        public InputAbstraction(Action equalsAction)
        {
            EqualsCommand = new EqualsCommand(equalsAction);
        }

        private string currentInputString;
        public string CurrentInputString
        {
            get
            {
                return currentInputString;
            }

            set
            {
                currentInputString = value;
                OnPropertyChanged();
            }
        }

        private bool isSpeechEnabled;
        public bool IsSpeechEnabled
        {
            get
            {
                return isSpeechEnabled;
            }
            set
            {
                isSpeechEnabled = value;
                OnPropertyChanged();
            }
        }

        public EqualsCommand EqualsCommand { get; }

        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    class EqualsCommand : ICommand
    {
        private Action equalsAction;

        public EqualsCommand(Action equalsAction)
        {
            this.equalsAction = equalsAction;
        }

        public void Execute(object parameter)
        {
            equalsAction();
        }

        public event EventHandler CanExecuteChanged;
        public bool CanExecute(object parameter)
        {
            return true;
        }
    }
}
