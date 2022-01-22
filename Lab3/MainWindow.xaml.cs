using System.Text;
using System.Windows;
using Lab3.UnmanagedCode;

namespace Lab3
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void ButtonBase_OnClick(object sender, RoutedEventArgs e)
        {
            var name = new StringBuilder("hi");
            var inPath = new StringBuilder("hi");
            var outPath = new StringBuilder("hi");
            Sum.Text = OtikArchNative.MakeArch(name, name.Length, inPath, inPath.Length,
                outPath, outPath.Length, false, false, false).ToString();
        }
    }
}