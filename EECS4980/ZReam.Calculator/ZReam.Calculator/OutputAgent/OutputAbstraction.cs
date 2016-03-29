using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using ZReam.Calculator.Math;
using ZReam.Calculator.OutputAgent.Contracts;

namespace ZReam.Calculator.OutputAgent
{
    class OutputAbstraction : IOutputAbstraction, INotifyPropertyChanged
    {
        private AST currentOutput;
        public AST CurrentOutput
        {
            get
            {
                return currentOutput;
            }
            set
            {
                currentOutput = value;
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

    [ValueConversion(typeof(AST), typeof(string))]
    public class ASTtoTEXConverer : BaseConverter, IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value != null)
            {
                return ((AST)value).RenderOutputTEX();
            }
            else
            {
                return string.Empty;
            }
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
