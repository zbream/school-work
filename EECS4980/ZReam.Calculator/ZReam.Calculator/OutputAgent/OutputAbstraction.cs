using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

using ZReam.Calculator.OutputAgent.Contracts;

namespace ZReam.Calculator.OutputAgent
{
    class OutputAbstraction : IOutputAbstraction
    {
        private string currentOutputVisible;
        public string CurrentOutputVisible
        {
            get
            {
                return currentOutputVisible;
            }
            set
            {
                currentOutputVisible = value;
                OnPropertyChanged();
            }
        }

        private string currentOutputAudible;
        public string CurrentOutputAudible
        {
            get
            {
                return currentOutputAudible;
            }
            set
            {
                currentOutputAudible = value;
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

        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
