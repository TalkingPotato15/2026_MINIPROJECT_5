using System;
using System.Windows;
using System.Windows.Interop;

namespace MiniProject_GUI
{
    public partial class MainWindow : Window
    {
        private MainViewModel _viewModel;

        public MainWindow()
        {
            InitializeComponent();

            // ViewModel 인스턴스화 및 DataContext 설정
            _viewModel = new MainViewModel();
            this.DataContext = _viewModel;

            // 윈도우 라이프사이클 이벤트 연결
            this.Loaded += MainWindow_Loaded;
            this.Closed += MainWindow_Closed;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            // WPF 창의 네이티브 핸들을 획득하여 ViewModel 초기화에 전달
            IntPtr windowHandle = new WindowInteropHelper(this).Handle;

            // NOMHandler의 윈도우 메시지 처리 함수 등록 (HwndSource 필요)
            HwndSource source = PresentationSource.FromVisual(this) as HwndSource;
            if (source != null)
            {
                source.AddHook(_viewModel.WndProcCallback);
            }

            // ViewModel 초기화 로직 실행
            _viewModel.Initialize(windowHandle);
        }

        private void MainWindow_Closed(object sender, EventArgs e)
        {
            // 종료 전 리소스 해제 처리 위임
            _viewModel.Cleanup();
        }
    }
}