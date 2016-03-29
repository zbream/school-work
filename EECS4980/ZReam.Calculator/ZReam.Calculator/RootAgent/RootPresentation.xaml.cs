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
using System.Windows.Shapes;

using ZReam.Calculator.RootAgent.Contracts;

namespace ZReam.Calculator.RootAgent
{
    /// <summary>
    /// Interaction logic for RootPresentation.xaml
    /// </summary>
    public partial class RootPresentation : Window, IRootPresentation
    {
        public RootPresentation()
        {
            InitializeComponent();
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            
            Application.Current.Shutdown(0);
        }

        public void ShowUI()
        {
            this.Show();
        }

        public void SetInputUI(UserControl control)
        {
            InputUI.Children.Clear();
            InputUI.Children.Add(control);
        }

        public void SetOutputUI(UserControl control)
        {
            OutputUI.Children.Clear();
            OutputUI.Children.Add(control);
        }
    }
}
