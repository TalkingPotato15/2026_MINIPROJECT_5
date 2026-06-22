using System;
using System.Windows;
using System.Windows.Interop;

namespace MiniProject_GUI
{
    public partial class MainWindow : Window
    {
        private readonly MainViewModel viewModel;

        public MainWindow()
        {
            InitializeComponent();

            viewModel = new MainViewModel();
            DataContext = viewModel;

            Loaded += MainWindow_Loaded;
            Closed += MainWindow_Closed;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            var windowHandle = new WindowInteropHelper(this).Handle;
            if (PresentationSource.FromVisual(this) is HwndSource source)
            {
                source.AddHook(viewModel.WndProcCallback);
            }

            viewModel.Initialize(windowHandle);
        }

        private void MainWindow_Closed(object? sender, EventArgs e)
        {
            viewModel.Cleanup();
        }
    }
}

