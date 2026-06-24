using System;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace MiniProject_GUI
{
    public partial class ScenarioWindow : Window
    {
        private const double MapWidth = 620;
        private const double MapHeight = 660;
        private const double MapCenterX = 310;
        private const double MapCenterY = 405;
        private const double MapScale = 1.15;

        private static readonly double MinMapX = -MapCenterX / MapScale;
        private static readonly double MaxMapX = (MapWidth - MapCenterX) / MapScale;
        private static readonly double MinMapY = -(MapHeight - MapCenterY) / MapScale;
        private static readonly double MaxMapY = MapCenterY / MapScale;

        private static readonly DependencyProperty LastValidTextProperty =
            DependencyProperty.RegisterAttached(
                "LastValidText",
                typeof(string),
                typeof(ScenarioWindow),
                new PropertyMetadata("0"));

        private bool isRestoringText;

        public ScenarioWindow()
        {
            InitializeComponent();
            DataObject.AddPastingHandler(this, ScenarioNumberTextBox_Pasting);
        }

        private void ScenarioNumberTextBox_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            if (sender is not TextBox textBox || !HasValidationTag(textBox)) return;

            var proposedText = GetProposedText(textBox, e.Text);
            if (!ValidateInput(textBox, proposedText, allowIntermediate: true, showWarning: true))
            {
                e.Handled = true;
            }
        }

        private void ScenarioNumberTextBox_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (sender is TextBox textBox && HasValidationTag(textBox) && e.Key == Key.Space)
            {
                e.Handled = true;
            }
        }

        private void ScenarioNumberTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (sender is not TextBox textBox || !HasValidationTag(textBox)) return;
            if (isRestoringText) return;

            if (ValidateInput(textBox, textBox.Text, allowIntermediate: false, showWarning: false))
            {
                textBox.SetValue(LastValidTextProperty, textBox.Text);
                return;
            }

            if (IsIntermediateNumber(textBox.Text)) return;

            RestoreLastValidText(textBox);
        }

        private void ScenarioNumberTextBox_LostFocus(object sender, RoutedEventArgs e)
        {
            if (sender is not TextBox textBox || !HasValidationTag(textBox)) return;

            if (ValidateInput(textBox, textBox.Text, allowIntermediate: false, showWarning: true)) return;

            RestoreLastValidText(textBox);
        }

        private void ScenarioNumberTextBox_Pasting(object sender, DataObjectPastingEventArgs e)
        {
            if (e.Source is not TextBox textBox || !HasValidationTag(textBox)) return;

            if (!e.DataObject.GetDataPresent(DataFormats.Text))
            {
                e.CancelCommand();
                return;
            }

            var pasteText = e.DataObject.GetData(DataFormats.Text) as string ?? "";
            var proposedText = GetProposedText(textBox, pasteText);
            if (!ValidateInput(textBox, proposedText, allowIntermediate: false, showWarning: true))
            {
                e.CancelCommand();
            }
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            if (!ValidateAllInputs(this))
            {
                return;
            }

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

        private static bool HasValidationTag(TextBox textBox)
        {
            return textBox.Tag is string tag && !string.IsNullOrWhiteSpace(tag);
        }

        private static string GetProposedText(TextBox textBox, string input)
        {
            var text = textBox.Text ?? "";
            var selectionStart = Math.Clamp(textBox.SelectionStart, 0, text.Length);
            var selectionLength = Math.Clamp(textBox.SelectionLength, 0, text.Length - selectionStart);

            if (selectionLength > 0)
            {
                text = text.Remove(selectionStart, selectionLength);
            }

            return text.Insert(selectionStart, input);
        }

        private bool ValidateInput(TextBox textBox, string text, bool allowIntermediate, bool showWarning)
        {
            var tag = textBox.Tag as string ?? "";

            if (allowIntermediate && IsIntermediateNumber(text))
            {
                return true;
            }

            if (!TryParseDouble(text, out var value))
            {
                if (showWarning) ShowInputWarning("숫자만 입력할 수 있습니다.");
                return false;
            }

            if (tag == "NonNegative")
            {
                if (value >= 0) return true;

                if (showWarning) ShowInputWarning("0 이상의 값만 입력할 수 있습니다.");
                return false;
            }

            if (tag == "AltitudeZ")
            {
                if (value >= 0 && value <= 20) return true;

                if (showWarning) ShowInputWarning("Z 값은 0 ~ 20 범위로 입력하세요.");
                return false;
            }

            switch (tag)
            {
                case "MapX":
                    if (value >= MinMapX && value <= MaxMapX) return true;
                    if (showWarning)
                    {
                        ShowInputWarning($"지도 화면 범위 밖입니다.\nX는 {MinMapX:F0} ~ {MaxMapX:F0} 범위 안으로 입력하십시오.");
                    }
                    return false;

                case "MapY":
                    if (value >= MinMapY && value <= MaxMapY) return true;
                    if (showWarning)
                    {
                        ShowInputWarning($"지도 화면 범위 밖입니다.\nY는 {MinMapY:F0} ~ {MaxMapY:F0} 범위 안으로 입력하십시오.");
                    }
                    return false;

                default:
                    return true;
            }
        }

        private static bool TryParseDouble(string text, out double value)
        {
            return double.TryParse(text, NumberStyles.Float, CultureInfo.CurrentCulture, out value) ||
                   double.TryParse(text, NumberStyles.Float, CultureInfo.InvariantCulture, out value);
        }

        private static bool IsIntermediateNumber(string text)
        {
            return string.IsNullOrWhiteSpace(text) ||
                   text == "-" ||
                   text == "+" ||
                   text == "." ||
                   text == "-." ||
                   text == "+.";
        }

        private bool ValidateAllInputs(DependencyObject parent)
        {
            for (var i = 0; i < VisualTreeHelper.GetChildrenCount(parent); i++)
            {
                var child = VisualTreeHelper.GetChild(parent, i);
                if (child is TextBox textBox && HasValidationTag(textBox))
                {
                    if (!ValidateInput(textBox, textBox.Text, allowIntermediate: false, showWarning: true))
                    {
                        textBox.Focus();
                        textBox.SelectAll();
                        return false;
                    }
                }

                if (!ValidateAllInputs(child))
                {
                    return false;
                }
            }

            return true;
        }

        private void RestoreLastValidText(TextBox textBox)
        {
            var lastValidText = (string)textBox.GetValue(LastValidTextProperty);
            isRestoringText = true;
            textBox.Text = string.IsNullOrWhiteSpace(lastValidText) ? "0" : lastValidText;
            textBox.SelectionStart = textBox.Text.Length;
            isRestoringText = false;
            textBox.GetBindingExpression(TextBox.TextProperty)?.UpdateSource();
        }

        private void ShowInputWarning(string message)
        {
            MessageBox.Show(this, message, "입력 범위 오류", MessageBoxButton.OK, MessageBoxImage.Warning);
        }
    }
}
