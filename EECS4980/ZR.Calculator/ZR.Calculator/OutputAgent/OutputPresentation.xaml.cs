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

using ZR.Calculator.OutputAgent.Contracts;

namespace ZR.Calculator.OutputAgent
{
    /// <summary>
    /// Interaction logic for OutputPresentation.xaml
    /// </summary>
    public partial class OutputPresentation : UserControl, IOutputPresentation
    {
        public OutputPresentation()
        {
            InitializeComponent();
        }

        public UserControl GetUI()
        {
            return this;
        }
    }
}
