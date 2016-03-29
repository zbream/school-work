using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using ZReam.Calculator.InputAgent.Contracts;

namespace ZReam.Calculator.InputAgent
{
    /// <summary>
    /// Interaction logic for InputPresentation.xaml
    /// </summary>
    public partial class InputPresentation : UserControl, IInputPresentation
    {
        public InputPresentation()
        {
            InitializeComponent();
        }

        public UserControl GetUI()
        {
            return this;
        }
    }
}
