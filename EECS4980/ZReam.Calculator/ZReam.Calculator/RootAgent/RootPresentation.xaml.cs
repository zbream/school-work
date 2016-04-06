using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
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

        public void RegisterOnClose(EventHandler handler)
        {
            Closed += handler;
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

        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);
            WindowUtil.HideMaximizeButton(this);
        }
    }

    internal static class WindowUtil
    {
        private const int GWL_STYLE = -16;
        private const int WS_MAXIMIZEBOX = 0x10000;

        [DllImport("user32.dll")]
        extern private static int GetWindowLong(IntPtr hwnd, int index);

        [DllImport("user32.dll")]
        extern private static int SetWindowLong(IntPtr hwnd, int index, int value);

        public static void HideMaximizeButton(Window window)
        {
            IntPtr hwnd = new WindowInteropHelper(window).Handle;
            var currentStyle = GetWindowLong(hwnd, GWL_STYLE);

            SetWindowLong(hwnd, GWL_STYLE, currentStyle & ~WS_MAXIMIZEBOX);
        }
    }
}
