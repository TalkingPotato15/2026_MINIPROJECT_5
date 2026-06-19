using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using nframework.nom;
using NOMHandlerLib.Concrete;
using NOMHandlerLib.Core;
using nframework.log4nf;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Media;
using System.Windows.Threading;

namespace MiniProject_GUI
{
    // ===================================================================
    // 상태 표시 Model
    // ===================================================================
    public class AtsTargetItem
    {
        public uint TargetId   { get; set; }
        public double PosX     { get; set; }
        public double PosY     { get; set; }
        public double PosZ     { get; set; }
        public uint Speed      { get; set; }
        public string StatusText { get; set; } = "기동중";
    }

    public class MssMissileItem
    {
        public uint MissileId  { get; set; }
        public uint TargetId   { get; set; }
        public double PosX     { get; set; }
        public double PosY     { get; set; }
        public double PosZ     { get; set; }
        public string StatusText { get; set; } = "대기";
    }

    public class DetectionEventItem
    {
        public string TimeStr  { get; set; } = "";
        public uint TargetId   { get; set; }
        public string Success  { get; set; } = "";
    }

    public class EngagementResultItem
    {
        public string TimeStr  { get; set; } = "";
        public string Result   { get; set; } = "";
    }

    // ===================================================================
    // MainViewModel
    // ===================================================================
    public partial class MainViewModel : ObservableObject
    {
        private readonly NOMHandler nomHandler;
        private static readonly LoggableCS l = new LoggableCS("MainViewModel");

        // ---------------------------------------------------------------
        // NOMHandler 연결 상태
        // ---------------------------------------------------------------
        [ObservableProperty] private bool _isPlugInEnabled  = false;
        [ObservableProperty] private bool _isPlugOutEnabled = false;
        [ObservableProperty] private bool _isStartEnabled   = false;
        [ObservableProperty] private bool _isStopEnabled    = false;
        [ObservableProperty] private bool _isLaunchEnabled  = false;

        // ---------------------------------------------------------------
        // 시나리오 설정 입력 값
        // ---------------------------------------------------------------
        [ObservableProperty] private string _rssPosX    = "0";
        [ObservableProperty] private string _rssPosY    = "0";
        [ObservableProperty] private string _rssPosZ    = "0";
        [ObservableProperty] private string _rssRadius  = "50000";
        [ObservableProperty] private string _mlsPosX    = "1000";
        [ObservableProperty] private string _mlsPosY    = "1000";
        [ObservableProperty] private string _mlsPosZ    = "0";
        [ObservableProperty] private string _targetCount = "1";
        [ObservableProperty] private string _target1StartX = "100000";
        [ObservableProperty] private string _target1StartY = "100000";
        [ObservableProperty] private string _target1StartZ = "10000";
        [ObservableProperty] private string _target1Speed   = "300";
        [ObservableProperty] private string _launchTargetId = "1";

        // ---------------------------------------------------------------
        // CSC 연결 상태 표시
        // ---------------------------------------------------------------
        [ObservableProperty] private string _atsStatusText  = "ATS 미연결";
        [ObservableProperty] private string _rssStatusText  = "RSS 미연결";
        [ObservableProperty] private string _mlsStatusText  = "MLS 미연결";
        [ObservableProperty] private string _mssStatusText  = "MSS 미연결";

        [ObservableProperty] private SolidColorBrush _atsStatusColor = new SolidColorBrush(Color.FromRgb(80, 30, 30));
        [ObservableProperty] private SolidColorBrush _rssStatusColor = new SolidColorBrush(Color.FromRgb(80, 30, 30));
        [ObservableProperty] private SolidColorBrush _mlsStatusColor = new SolidColorBrush(Color.FromRgb(80, 30, 30));
        [ObservableProperty] private SolidColorBrush _mssStatusColor = new SolidColorBrush(Color.FromRgb(80, 30, 30));

        private static readonly TimeSpan SimulatorConnectionTimeout = TimeSpan.FromSeconds(5);
        private readonly DispatcherTimer simulatorConnectionTimer;
        private DateTime? lastAtsStatusAt;
        private DateTime? lastRssStatusAt;
        private DateTime? lastMlsStatusAt;
        private DateTime? lastMssStatusAt;

        // ---------------------------------------------------------------
        // 상태 데이터 컬렉션
        // ---------------------------------------------------------------
        [ObservableProperty] private ObservableCollection<AtsTargetItem>      _atsTargetList      = new();
        [ObservableProperty] private ObservableCollection<MssMissileItem>     _mssMissileList     = new();
        [ObservableProperty] private ObservableCollection<DetectionEventItem> _detectionEventList = new();
        [ObservableProperty] private ObservableCollection<EngagementResultItem> _engagementResultList = new();
        [ObservableProperty] private ObservableCollection<string>             _eventLogList       = new();

        // ---------------------------------------------------------------
        // MLS 발사대 상태
        // ---------------------------------------------------------------
        [ObservableProperty] private string _mlsMissile1 = "-";
        [ObservableProperty] private string _mlsMissile2 = "-";
        [ObservableProperty] private string _mlsMissile3 = "-";
        [ObservableProperty] private string _mlsMissile4 = "-";
        [ObservableProperty] private string _mlsStock    = "-";

        // ---------------------------------------------------------------
        // 요격 결과 표시
        // ---------------------------------------------------------------
        [ObservableProperty] private string _interceptionResultText   = "대기중";
        [ObservableProperty] private string _interceptionResultDetail = "모의 시작 후 표적 탐지 대기";
        [ObservableProperty] private SolidColorBrush _interceptionResultColor =
            new SolidColorBrush(Color.FromRgb(37, 40, 64));

        // ---------------------------------------------------------------
        // NOM MessageList (디버그용, 기존 호환)
        // ---------------------------------------------------------------
        [ObservableProperty] private ObservableCollection<NMessage> _nomMessageList = new();

        // ---------------------------------------------------------------
        // 생성자
        // ---------------------------------------------------------------
        public MainViewModel()
        {
            // GUI는 UIManager 역할의 NOM만 직접 로드한다.
            var nomFilePaths = new List<string>
            {
                Environment.CurrentDirectory + @"\UIManager\UIManager.xml",
            };

            nomHandler = new NOMHandler(nomFilePaths);
            nomHandler.MessageReceived += OnNOMMessageReceived;
            nomHandler.MessageSent     += OnNOMMessageSent;

            simulatorConnectionTimer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(1)
            };
            simulatorConnectionTimer.Tick += (_, _) => RefreshSimulatorConnectionStates();
            simulatorConnectionTimer.Start();
        }

        public void Initialize(IntPtr windowHandle)
        {
            NomMessageList = new ObservableCollection<NMessage>(nomHandler.NOMMessageList);

            if (nomHandler.CreateNFConnect())
            {
                nomHandler.DoPlugIn();
                nomHandler.SetWindowHandle(windowHandle);
                nomHandler.ExecStart();

                IsPlugOutEnabled = true;
                IsStartEnabled   = true;
                AddLog("[시스템] nFramework 연결 성공.");
            }
            else
            {
                IsPlugInEnabled = true;
                AddLog("[오류] nFramework 연결 실패. Plug In을 눌러 재시도하세요.");
                MessageBox.Show("nFramework 연결에 실패했습니다.");
            }
        }

        public void Cleanup()
        {
            nomHandler.ExecStop();
            nomHandler.DoPlugOut();
            nomHandler.DestroyNFConnect();
            System.Diagnostics.Process.GetCurrentProcess().Kill();
        }

        public System.Windows.Interop.HwndSourceHook WndProcCallback => nomHandler.WndProcCallback;

        // ---------------------------------------------------------------
        // Commands
        // ---------------------------------------------------------------
        [RelayCommand]
        private void PlugIn()
        {
            IsPlugInEnabled = false;
            if (nomHandler.CreateNFConnect())
            {
                nomHandler.DoPlugIn();
                nomHandler.ExecStart();
                IsPlugOutEnabled = true;
                IsStartEnabled   = true;
                AddLog("[시스템] Plug In 완료.");
            }
            else
            {
                IsPlugInEnabled = true;
                AddLog("[오류] Plug In 실패.");
            }
        }

        [RelayCommand]
        private void PlugOut()
        {
            nomHandler.ExecStop();
            nomHandler.DoPlugOut();
            IsPlugOutEnabled = false;
            IsStartEnabled   = false;
            IsStopEnabled    = false;
            IsLaunchEnabled  = false;
            IsPlugInEnabled  = true;
            ResetSimulatorConnectionStates();
            AddLog("[시스템] Plug Out.");
        }

        [RelayCommand]
        private void SendScenario()
        {
            try
            {
                var nom = nomHandler.GetNMessage("Scenario")?.createNOMInstance();
                if (nom == null) { AddLog("[오류] Scenario NOM 인스턴스 없음"); return; }

                nom.setValue("Header.MessageID", new NUShort(0x01));
                nom.setValue("Header.MessageLength", new NUShort(2));

                // 표적 수
                uint count = uint.TryParse(TargetCount, out var c) ? c : 1;
                nom.setValue("targetCount", new NUInteger(count));

                // 표적 1 정보
                nom.setValue("scenarioInfo.targetID",        new NUInteger(1),       0);
                nom.setValue("scenarioInfo.speed",           new NUInteger(uint.TryParse(Target1Speed, out var spd) ? spd : 300), 0);
                nom.setValue("scenarioInfo.pointCount",      new NUInteger(1),       0);
                nom.setValue("scenarioInfo.point.x",         new NDouble(double.TryParse(Target1StartX, out var x) ? x : 0), 0);
                nom.setValue("scenarioInfo.point.y",         new NDouble(double.TryParse(Target1StartY, out var y) ? y : 0), 0);
                nom.setValue("scenarioInfo.point.z",         new NDouble(double.TryParse(Target1StartZ, out var z) ? z : 0), 0);

                // RSS 위치/반경
                nom.setValue("rssPos.x",  new NDouble(double.TryParse(RssPosX, out var rx) ? rx : 0));
                nom.setValue("rssPos.y",  new NDouble(double.TryParse(RssPosY, out var ry) ? ry : 0));
                nom.setValue("rssPos.z",  new NDouble(double.TryParse(RssPosZ, out var rz) ? rz : 0));
                nom.setValue("radius",    new NDouble(double.TryParse(RssRadius, out var rad) ? rad : 50000));

                // MLS 위치
                nom.setValue("mlsPos.x",  new NDouble(double.TryParse(MlsPosX, out var mx) ? mx : 0));
                nom.setValue("mlsPos.y",  new NDouble(double.TryParse(MlsPosY, out var my) ? my : 0));
                nom.setValue("mlsPos.z",  new NDouble(double.TryParse(MlsPosZ, out var mz) ? mz : 0));

                nomHandler.SendNOMMessage(nom);
                AddLog($"[송신] Scenario 배포 완료. 표적 수={count}");
            }
            catch (Exception ex)
            {
                AddLog($"[오류] Scenario 송신 실패: {ex.Message}");
            }
        }

        [RelayCommand]
        private void StartSimulation()
        {
            try
            {
                var nom = nomHandler.GetNMessage("StartSimulation")?.createNOMInstance();
                if (nom == null) { AddLog("[오류] StartSimulation NOM 없음"); return; }

                nom.setValue("Header.MessageID",    new NUShort(0x06));
                nom.setValue("Header.MessageLength", new NUShort(2));
                nom.setValue("simulationStatus",    new NBool(true));
                nomHandler.SendNOMMessage(nom);

                IsStartEnabled  = false;
                IsStopEnabled   = true;
                IsLaunchEnabled = true;
                AddLog("[송신] StartSimulation → 모의 시작.");
            }
            catch (Exception ex)
            {
                AddLog($"[오류] StartSimulation 실패: {ex.Message}");
            }
        }

        [RelayCommand]
        private void StopSimulation()
        {
            try
            {
                var nom = nomHandler.GetNMessage("Stop")?.createNOMInstance();
                if (nom == null) { AddLog("[오류] Stop NOM 없음"); return; }

                nom.setValue("Header.MessageID", new NUShort(0x10));
                nom.setValue("Header.MessageLength", new NUShort(2));
                nom.setValue("stopFlag",         new NBool(true));
                nomHandler.SendNOMMessage(nom);

                IsStartEnabled  = true;
                IsStopEnabled   = false;
                IsLaunchEnabled = false;
                AddLog("[송신] Stop → 모의 중지.");
            }
            catch (Exception ex)
            {
                AddLog($"[오류] Stop 실패: {ex.Message}");
            }
        }

        [RelayCommand]
        private void SendLaunchCommand()
        {
            try
            {
                var nom = nomHandler.GetNMessage("LaunchCommand")?.createNOMInstance();
                if (nom == null) { AddLog("[오류] LaunchCommand NOM 없음"); return; }

                uint tID = uint.TryParse(LaunchTargetId, out var tid) ? tid : 1;
                nom.setValue("Header.MessageID", new NUShort(0x09));
                nom.setValue("Header.MessageLength", new NUShort(2));
                nom.setValue("targetID",         new NUInteger(tID));
                nomHandler.SendNOMMessage(nom);

                AddLog($"[송신] LaunchCommand → targetID={tID}");
            }
            catch (Exception ex)
            {
                AddLog($"[오류] LaunchCommand 실패: {ex.Message}");
            }
        }

        [RelayCommand]
        private void ClearLog()
        {
            EventLogList.Clear();
        }

        // ---------------------------------------------------------------
        // NOM 수신 처리
        // ---------------------------------------------------------------
        private void OnNOMMessageSent(NOM nomInstance, EMessageOperation operation)
        {
            // 송신 로그는 각 Command에서 직접 처리
        }

        private void OnNOMMessageReceived(NOM nomInstance, EMessageOperation operation)
        {
            Application.Current.Dispatcher.InvokeAsync(() =>
            {
                try
                {
                    var nom = nomInstance.clone();
                    RouteReceivedMessage(nom);
                }
                catch (Exception ex)
                {
                    AddLog($"[오류] 수신 처리 예외: {ex.Message}");
                }
            });
        }

        /// <summary>
        /// 수신된 NOM을 메시지명 기준으로 분기 처리
        /// </summary>
        private void RouteReceivedMessage(NOM nom)
        {
            MarkSimulatorConnectedByMessageId(nom);

            switch (nom.name)
            {
                case "ATSStatus":      HandleATSStatus(nom);      break;
                case "RSSStatus":      HandleRSSStatus(nom);      break;
                case "MLSStatus":      HandleMLSStatus(nom);      break;
                case "MSSStatus":      HandleMSSStatus(nom);      break;
                case "TargetDetection": HandleTargetDetection(nom); break;
                case "TargetDestroyed": HandleTargetDestroyed(nom); break;
                default:
                    l.Warn($"[MainViewModel] Unhandled message: {nom.name}");
                    break;
            }
        }

        // ---------------------------------------------------------------
        // 개별 메시지 핸들러
        // ---------------------------------------------------------------
        private void HandleATSStatus(NOM nom)
        {
            MarkSimulatorConnected("ATS");

            uint count = 0;
            var countVal = nom.getValue("targetCount");
            if (countVal != null) count = countVal.toUInt();

            AtsTargetList.Clear();
            for (uint i = 0; i < count && i < 20; i++)
            {
                var id    = nom.getValue("targetInfo.targetID",         (int)i);
                var px    = nom.getValue("targetInfo.pos.x",            (int)i);
                var py    = nom.getValue("targetInfo.pos.y",            (int)i);
                var pz    = nom.getValue("targetInfo.pos.z",            (int)i);
                var spd   = nom.getValue("targetInfo.speed",            (int)i);
                var flag  = nom.getValue("targetInfo.interceptionFlag", (int)i);

                AtsTargetList.Add(new AtsTargetItem
                {
                    TargetId   = id   != null ? id.toUInt()  : i + 1,
                    PosX       = px   != null ? px.toDouble()         : 0,
                    PosY       = py   != null ? py.toDouble()         : 0,
                    PosZ       = pz   != null ? pz.toDouble()         : 0,
                    Speed      = spd  != null ? spd.toUInt() : 0,
                    StatusText = (flag != null && flag.toUInt() != 0) ? "격추" : "기동중"
                });
            }
        }

        private void HandleRSSStatus(NOM nom)
        {
            MarkSimulatorConnected("RSS");
        }

        private void HandleMLSStatus(NOM nom)
        {
            MarkSimulatorConnected("MLS");

            var li = nom.getValue("launcherInfo.missileStatus1");
            MlsMissile1 = GetMissileStatusText(nom.getValue("launcherInfo.missileStatus1"));
            MlsMissile2 = GetMissileStatusText(nom.getValue("launcherInfo.missileStatus2"));
            MlsMissile3 = GetMissileStatusText(nom.getValue("launcherInfo.missileStatus3"));
            MlsMissile4 = GetMissileStatusText(nom.getValue("launcherInfo.missileStatus4"));
            var stock   = nom.getValue("launcherInfo.missileStock");
            MlsStock    = stock != null ? stock.toUInt().ToString() : "-";
        }

        private void HandleMSSStatus(NOM nom)
        {
            MarkSimulatorConnected("MSS");

            uint count = 0;
            var countVal = nom.getValue("missileCount");
            if (countVal != null) count = countVal.toUInt();

            MssMissileList.Clear();
            for (uint i = 0; i < count && i < 4; i++)
            {
                var mid   = nom.getValue("missileInfo.missileID",    (int)i);
                var tid   = nom.getValue("missileInfo.targetID",     (int)i);
                var px    = nom.getValue("missileInfo.pos.x",        (int)i);
                var py    = nom.getValue("missileInfo.pos.y",        (int)i);
                var pz    = nom.getValue("missileInfo.pos.z",        (int)i);
                var st    = nom.getValue("missileInfo.mssStatus",    (int)i);
                var flag  = nom.getValue("missileInfo.isIntercepted", (int)i);

                MssMissileList.Add(new MssMissileItem
                {
                    MissileId  = mid  != null ? mid.toUInt() : i + 1,
                    TargetId   = tid  != null ? tid.toUInt() : 0,
                    PosX       = px   != null ? px.toDouble()         : 0,
                    PosY       = py   != null ? py.toDouble()         : 0,
                    PosZ       = pz   != null ? pz.toDouble()         : 0,
                    StatusText = (flag != null && flag.toUInt() != 0) ? "요격성공" :
                                 (st  != null && st.toInt() > 0)  ? "추적중" : "대기"
                });
            }
        }

        private void HandleTargetDetection(NOM nom)
        {
            var idVal  = nom.getValue("targetID");
            var sucVal = nom.getValue("targetDetectionSuccess");

            uint   tID     = idVal  != null ? idVal.toUInt()  : 0;
            bool   success = sucVal != null ? sucVal.toUInt() != 0 : false;

            DetectionEventList.Add(new DetectionEventItem
            {
                TimeStr = DateTime.Now.ToString("HH:mm:ss"),
                TargetId = tID,
                Success  = success ? "탐지 성공" : "탐지 실패"
            });

            AddLog($"[수신] TargetDetection — targetID={tID}, 탐지={success}");

            if (success)
            {
                LaunchTargetId = tID.ToString();
            }
        }

        private void HandleTargetDestroyed(NOM nom)
        {
            var sucVal = nom.getValue("missionSuccess");
            bool success = sucVal != null ? sucVal.toUInt() != 0 : false;

            if (success)
            {
                InterceptionResultText   = "요격 성공!";
                InterceptionResultDetail = DateTime.Now.ToString("HH:mm:ss") + " 임무 완료";
                InterceptionResultColor  = new SolidColorBrush(Color.FromRgb(29, 92, 56));
            }
            else
            {
                InterceptionResultText   = "임무 실패";
                InterceptionResultDetail = DateTime.Now.ToString("HH:mm:ss") + " 표적 통과";
                InterceptionResultColor  = new SolidColorBrush(Color.FromRgb(122, 26, 26));
            }

            EngagementResultList.Add(new EngagementResultItem
            {
                TimeStr = DateTime.Now.ToString("HH:mm:ss"),
                Result  = success ? "요격 성공" : "임무 실패"
            });

            AddLog($"[수신] TargetDestroyed — missionSuccess={success}");
        }

        // ---------------------------------------------------------------
        // 헬퍼
        // ---------------------------------------------------------------
        private static readonly SolidColorBrush ConnectedColor =
            new SolidColorBrush(Color.FromRgb(29, 92, 56));

        private static readonly SolidColorBrush DisconnectedColor =
            new SolidColorBrush(Color.FromRgb(80, 30, 30));

        private void MarkSimulatorConnected(string simulator)
        {
            var now = DateTime.UtcNow;

            switch (simulator)
            {
                case "ATS":
                    lastAtsStatusAt = now;
                    AtsStatusText = "ATS 연결됨";
                    AtsStatusColor = ConnectedColor;
                    break;
                case "RSS":
                    lastRssStatusAt = now;
                    RssStatusText = "RSS 연결됨";
                    RssStatusColor = ConnectedColor;
                    break;
                case "MLS":
                    lastMlsStatusAt = now;
                    MlsStatusText = "MLS 연결됨";
                    MlsStatusColor = ConnectedColor;
                    break;
                case "MSS":
                    lastMssStatusAt = now;
                    MssStatusText = "MSS 연결됨";
                    MssStatusColor = ConnectedColor;
                    break;
            }
        }

        private void MarkSimulatorConnectedByMessageId(NOM nom)
        {
            var messageIdValue = nom.getValue("Header.MessageID");
            if (messageIdValue == null) return;

            switch (messageIdValue.toUInt())
            {
                case 0x02:
                    MarkSimulatorConnected("ATS");
                    break;
                case 0x03:
                    MarkSimulatorConnected("RSS");
                    break;
                case 0x04:
                    MarkSimulatorConnected("MSS");
                    break;
                case 0x05:
                    MarkSimulatorConnected("MLS");
                    break;
            }
        }

        private void RefreshSimulatorConnectionStates()
        {
            var now = DateTime.UtcNow;

            if (IsTimedOut(now, lastAtsStatusAt))
            {
                AtsStatusText = "ATS 미연결";
                AtsStatusColor = DisconnectedColor;
            }

            if (IsTimedOut(now, lastRssStatusAt))
            {
                RssStatusText = "RSS 미연결";
                RssStatusColor = DisconnectedColor;
            }

            if (IsTimedOut(now, lastMlsStatusAt))
            {
                MlsStatusText = "MLS 미연결";
                MlsStatusColor = DisconnectedColor;
            }

            if (IsTimedOut(now, lastMssStatusAt))
            {
                MssStatusText = "MSS 미연결";
                MssStatusColor = DisconnectedColor;
            }
        }

        private static bool IsTimedOut(DateTime now, DateTime? lastStatusAt)
        {
            return !lastStatusAt.HasValue || now - lastStatusAt.Value > SimulatorConnectionTimeout;
        }

        private void ResetSimulatorConnectionStates()
        {
            lastAtsStatusAt = null;
            lastRssStatusAt = null;
            lastMlsStatusAt = null;
            lastMssStatusAt = null;
            RefreshSimulatorConnectionStates();
        }

        private string GetMissileStatusText(NValueType val)
        {
            if (val == null) return "-";
            return val.toUInt() switch
            {
                0 => "장입",
                1 => "준비",
                2 => "발사",
                _ => val.toUInt().ToString()
            };
        }

        private void AddLog(string message)
        {
            if (Application.Current?.Dispatcher.CheckAccess() == true)
            {
                EventLogList.Add(message);
                if (EventLogList.Count > 200) EventLogList.RemoveAt(0);
            }
            else
            {
                Application.Current?.Dispatcher.InvokeAsync(() =>
                {
                    EventLogList.Add(message);
                    if (EventLogList.Count > 200) EventLogList.RemoveAt(0);
                });
            }
        }
    }
}
