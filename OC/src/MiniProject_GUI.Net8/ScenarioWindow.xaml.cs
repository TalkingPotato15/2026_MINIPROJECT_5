using System.Windows;

namespace MiniProject_GUI
{
    public partial class ScenarioWindow : Window
    {
        public ScenarioWindow()
        {
            InitializeComponent();
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            if (DataContext is MainViewModel viewModel)
            {
                viewModel.ApplyScenarioPreview();
            }

            DialogResult = true;
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = false;
        }
    }
}

