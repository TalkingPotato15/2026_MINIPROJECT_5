using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using nframework.log4nf;
using nframework.nom;
using NOMHandlerLib.Concrete;
using NOMHandlerLib.Core;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Media;
using System.Windows.Threading;

namespace MiniProject_GUI
{
    public class OcAtsTargetItem
    {
        public uint TargetId { get; set; }
        public double PosX { get; set; }
        public double PosY { get; set; }
        public double PosZ { get; set; }
        public uint Speed { get; set; }
        public string StatusText { get; set; } = "기동중";
    }

    public class OcMssMissileItem
    {
        public uint MissileId { get; set; }
        public uint TargetId { get; set; }
        public double PosX { get; set; }
        public double PosY { get; set; }
        public double PosZ { get; set; }
        public string StatusText { get; set; } = "대기";
        public string SummaryText => $"{MissileId}번 유도탄 : {StatusText}  X:{PosX:F0} Y:{PosY:F0} Z:{PosZ:F0}";
    }

    public class OcDetectionEventItem
    {
        public string TimeStr { get; set; } = "";
        public uint TargetId { get; set; }
        public string Success { get; set; } = "";
    }

    public class OcEngagementResultItem
    {
        public string TimeStr { get; set; } = "";
        public string Result { get; set; } = "";
    }

    public partial class OcScenarioPointInput : ObservableObject
    {
        public OcScenarioPointInput(string label, string x, string y, string z)
        {
            _label = label;
            _x = x;
            _y = y;
            _z = z;
        }

        [ObservableProperty] private string _label;
        [ObservableProperty] private string _x;
        [ObservableProperty] private string _y;
        [ObservableProperty] private string _z;
    }

    public partial class OcAirThreatInput : ObservableObject
    {
        public OcAirThreatInput(int index)
        {
            Index = index;
            Name = $"공중위협 {index}";
            _isEnabled = true;
            _targetId = index.ToString();
            _speed = "300";

            Points.Add(new OcScenarioPointInput("시작점", "120", "120", "10"));
            Points.Add(new OcScenarioPointInput("종료점", "0", "0", "10"));
        }

        public int Index { get; }
        public string Name { get; }
        public ObservableCollection<OcScenarioPointInput> Points { get; } = new();
        public bool CanAddPoint => Points.Count < 4;
        public bool CanRemovePoint => Points.Count > 2;

        [ObservableProperty] private bool _isEnabled;
        [ObservableProperty] private string _targetId;
        [ObservableProperty] private string _speed;

        public void AddWaypoint()
        {
            if (!CanAddPoint) return;

            var endPoint = Points[Points.Count - 1];
            var previousPoint = Points[Points.Count - 2];
            Points.RemoveAt(Points.Count - 1);

            Points.Add(new OcScenarioPointInput(
                "",
                Midpoint(previousPoint.X, endPoint.X),
                Midpoint(previousPoint.Y, endPoint.Y),
                Midpoint(previousPoint.Z, endPoint.Z)));
            Points.Add(endPoint);
            RenumberPoints();
        }

        public void RemoveWaypoint()
        {
            if (!CanRemovePoint) return;

            Points.RemoveAt(Points.Count - 2);
            RenumberPoints();
        }

        private void RenumberPoints()
        {
            for (var i = 0; i < Points.Count; i++)
            {
                Points[i].Label = i switch
                {
                    0 => "시작점",
                    var last when last == Points.Count - 1 => "종료점",
                    _ => $"경유점 {i}"
                };
            }

            OnPropertyChanged(nameof(CanAddPoint));
            OnPropertyChanged(nameof(CanRemovePoint));
        }

        private static string Midpoint(string a, string b)
        {
            var first = double.TryParse(a, out var parsedA) ? parsedA : 0;
            var second = double.TryParse(b, out var parsedB) ? parsedB : 0;
            return ((first + second) / 2).ToString("F0");
        }
    }

    public class OcAirThreatDisplay
    {
        public string Name { get; set; } = "";
        public string TargetId { get; set; } = "";
        public string PosX { get; set; } = "";
        public string PosY { get; set; } = "";
        public string PosZ { get; set; } = "";
        public string CoordinateText => $"X:{PosX}  Y:{PosY}  Z:{PosZ}";
        public Brush NameBrush { get; set; } = Brushes.Lime;
        public double PanelHeight { get; set; } = 118;
        public double NameFontSize { get; set; } = 20;
        public double CoordinateFontSize { get; set; } = 22;
    }

    public class OcMapMarkerItem
    {
        public double Left { get; set; }
        public double Top { get; set; }
        public string Label { get; set; } = "";
        public Brush Fill { get; set; } = Brushes.Lime;
    }

    public class OcMapPathItem
    {
        public PointCollection Points { get; set; } = new();
        public Brush Stroke { get; set; } = Brushes.Lime;
    }

    public partial class MainViewModel : ObservableObject
    {
        private readonly NOMHandler nomHandler;
        private static readonly LoggableCS l = new LoggableCS("MainViewModel");
        private static readonly Brush[] ThreatBrushes =
        {
            Brushes.Lime,
            Brushes.Yellow,
            Brushes.DeepSkyBlue,
            Brushes.Orange
        };

        private const double MapCenterX = 310;
        private const double MapCenterY = 405;
        private const double MapScale = 1.15;

        private static readonly TimeSpan SimulatorConnectionTimeout = TimeSpan.FromSeconds(5);
        private readonly DispatcherTimer simulatorConnectionTimer;
        private IntPtr windowHandle;
        private DateTime? lastAtsStatusAt;
        private DateTime? lastRssStatusAt;
        private DateTime? lastMlsStatusAt;
        private DateTime? lastMssStatusAt;
        private bool isScenarioApplied;
        private bool isSimulationRunning;
        private uint? lastEngagedTargetId;
        private readonly HashSet<uint> detectedTargetIds = new();
        private readonly HashSet<uint> destroyedTargetIds = new();
        private readonly Dictionary<uint, (double X, double Y, double Z)> latestTargetPositions = new();
        private readonly Dictionary<uint, OcMssMissileItem> missileDisplays = new();

        [ObservableProperty] private bool _isPlugInEnabled = false;
        [ObservableProperty] private bool _isPlugOutEnabled = false;
        [ObservableProperty] private bool _isStartEnabled = false;
        [ObservableProperty] private bool _isStopEnabled = false;
        [ObservableProperty] private bool _isLaunchEnabled = false;

        [ObservableProperty] private string _rssPosX = "0";
        [ObservableProperty] private string _rssPosY = "0";
        [ObservableProperty] private string _rssPosZ = "0";
        [ObservableProperty] private string _rssRadius = "50";
        [ObservableProperty] private string _mlsPosX = "50";
        [ObservableProperty] private string _mlsPosY = "0";
        [ObservableProperty] private string _mlsPosZ = "0";
        [ObservableProperty] private string _targetCount = "0";
        [ObservableProperty] private string _launchTargetId = "1";

        [ObservableProperty] private string _atsStatusText = "ATS 미연결";
        [ObservableProperty] private string _rssStatusText = "RSS 미연결";
        [ObservableProperty] private string _mlsStatusText = "MLS 미연결";
        [ObservableProperty] private string _mssStatusText = "MSS 미연결";

        [ObservableProperty] private SolidColorBrush _atsStatusColor = new SolidColorBrush(Color.FromRgb(255, 0, 0));
        [ObservableProperty] private SolidColorBrush _rssStatusColor = new SolidColorBrush(Color.FromRgb(255, 0, 0));
        [ObservableProperty] private SolidColorBrush _mlsStatusColor = new SolidColorBrush(Color.FromRgb(255, 0, 0));
        [ObservableProperty] private SolidColorBrush _mssStatusColor = new SolidColorBrush(Color.FromRgb(255, 0, 0));

        [ObservableProperty] private ObservableCollection<OcAtsTargetItem> _atsTargetList = new();
        [ObservableProperty] private ObservableCollection<OcMssMissileItem> _mssMissileList = new();
        [ObservableProperty] private ObservableCollection<OcDetectionEventItem> _detectionEventList = new();
        [ObservableProperty] private ObservableCollection<OcEngagementResultItem> _engagementResultList = new();
        [ObservableProperty] private ObservableCollection<string> _eventLogList = new();
        [ObservableProperty] private ObservableCollection<NMessage> _nomMessageList = new();

        [ObservableProperty] private ObservableCollection<OcAirThreatInput> _scenarioThreats = new();
        [ObservableProperty] private ObservableCollection<OcAirThreatDisplay> _scenarioThreatDisplays = new();
        [ObservableProperty] private ObservableCollection<OcMapMarkerItem> _mapThreatMarkers = new();
        [ObservableProperty] private ObservableCollection<OcMapPathItem> _mapThreatPaths = new();

        [ObservableProperty] private double _radarRangeLeft;
        [ObservableProperty] private double _radarRangeTop;
        [ObservableProperty] private double _radarRangeDiameter;
        [ObservableProperty] private double _radarIconLeft;
        [ObservableProperty] private double _radarIconTop;
        [ObservableProperty] private double _launcherIconLeft;
        [ObservableProperty] private double _launcherIconTop;

        [ObservableProperty] private string _mlsMissile1 = "-";
        [ObservableProperty] private string _mlsMissile2 = "-";
        [ObservableProperty] private string _mlsMissile3 = "-";
        [ObservableProperty] private string _mlsMissile4 = "-";
        [ObservableProperty] private string _mlsStock = "-";

        [ObservableProperty] private string _interceptionResultText = "대기중";
        [ObservableProperty] private string _interceptionResultDetail = "모의 시작 및 표적 탐지 대기";
        [ObservableProperty] private SolidColorBrush _interceptionResultColor =
            new SolidColorBrush(Color.FromRgb(37, 40, 64));

        public MainViewModel()
        {
            var nomFilePaths = new List<string>
            {
                Environment.CurrentDirectory + @"\UIManager\UIManager.xml",
            };

            nomHandler = new NOMHandler(nomFilePaths);
            nomHandler.MessageReceived += OnNOMMessageReceived;
            nomHandler.MessageSent += OnNOMMessageSent;

            InitializeScenarioInputs();
            ResetMissileDisplays();
            RefreshMapGeometry();

            simulatorConnectionTimer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(1)
            };
            simulatorConnectionTimer.Tick += (_, _) => RefreshSimulatorConnectionStates();
            simulatorConnectionTimer.Start();
        }

        public void Initialize(IntPtr nativeWindowHandle)
        {
            windowHandle = nativeWindowHandle;
            NomMessageList = new ObservableCollection<NMessage>(nomHandler.NOMMessageList);

            if (nomHandler.CreateNFConnect())
            {
                nomHandler.DoPlugIn();
                nomHandler.SetWindowHandle(windowHandle);
                nomHandler.ExecStart();

                IsPlugOutEnabled = true;
                IsStartEnabled = true;
                AddLog("[시스템] nFramework 연결 성공.");
            }
            else
            {
                IsPlugInEnabled = true;
                AddLog("[오류] nFramework 연결 실패. Plug In을 다시 시도하십시오.");
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

        [RelayCommand]
        private void PlugIn()
        {
            IsPlugInEnabled = false;
            if (nomHandler.CreateNFConnect())
            {
                nomHandler.DoPlugIn();
                if (windowHandle != IntPtr.Zero)
                {
                    nomHandler.SetWindowHandle(windowHandle);
                }
                nomHandler.ExecStart();
                IsPlugOutEnabled = true;
                IsStartEnabled = true;
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
            IsStartEnabled = false;
            IsStopEnabled = false;
            IsLaunchEnabled = false;
            IsPlugInEnabled = true;
            ResetSimulatorConnectionStates();
            AddLog("[시스템] Plug Out.");
        }

        [RelayCommand]
        private void OpenScenarioEditor()
        {
            var owner = Application.Current.Windows
                .OfType<Window>()
                .FirstOrDefault(w => w.IsActive) ?? Application.Current.MainWindow;

            var window = new ScenarioWindow
            {
                DataContext = this,
                Owner = owner
            };

            window.ShowDialog();
        }

        [RelayCommand]
        private void SendScenario()
        {
            try
            {
                ApplyScenarioPreview();

                var nom = nomHandler.GetNMessage("Scenario")?.createNOMInstance();
                if (nom == null)
                {
                    AddLog("[오류] Scenario NOM 인스턴스 없음");
                    return;
                }

                var threats = ScenarioThreats.Take(4).ToList();
                var count = (uint)threats.Count;

                nom.setValue("Header.MessageID", new NUShort(0x01));
                nom.setValue("Header.MessageLength", new NUShort(2));
                nom.setValue("targetCount", new NUInteger(count));

                for (var i = 0; i < threats.Count; i++)
                {
                    var threat = threats[i];
                    var prefix = $"scenarioInfo[{i}]";
                    var targetId = ParseUInt(threat.TargetId, (uint)(i + 1));
                    var speed = ParseUInt(threat.Speed, 300);
                    var points = threat.Points.Take(4).ToList();

                    nom.setValue($"{prefix}.targetID", new NUInteger(targetId));
                    nom.setValue($"{prefix}.speed", new NUInteger(speed));
                    nom.setValue($"{prefix}.pointCount", new NUInteger((uint)points.Count));

                    for (var pointIndex = 0; pointIndex < points.Count; pointIndex++)
                    {
                        var point = points[pointIndex];
                        var pointPrefix = $"{prefix}.point[{pointIndex}]";
                        nom.setValue($"{pointPrefix}.x", new NDouble(ParseDouble(point.X, 0)));
                        nom.setValue($"{pointPrefix}.y", new NDouble(ParseDouble(point.Y, 0)));
                        nom.setValue($"{pointPrefix}.z", new NDouble(ParseDouble(point.Z, 0)));
                    }
                }

                nom.setValue("rssPos.x", new NDouble(ParseDouble(RssPosX, 0)));
                nom.setValue("rssPos.y", new NDouble(ParseDouble(RssPosY, 0)));
                nom.setValue("rssPos.z", new NDouble(ParseDouble(RssPosZ, 0)));
                nom.setValue("radius", new NDouble(ParseDouble(RssRadius, 50)));

                nom.setValue("mlsPos.x", new NDouble(ParseDouble(MlsPosX, 0)));
                nom.setValue("mlsPos.y", new NDouble(ParseDouble(MlsPosY, 0)));
                nom.setValue("mlsPos.z", new NDouble(ParseDouble(MlsPosZ, 0)));

                nomHandler.SendNOMMessage(nom);
                AddLog($"[송신] Scenario 배포 완료. 공중위협 수={count}");
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

                nom.setValue("Header.MessageID", new NUShort(0x06));
                nom.setValue("Header.MessageLength", new NUShort(2));
                nom.setValue("simulationStatus", new NBool(true));
                nomHandler.SendNOMMessage(nom);

                IsStartEnabled = false;
                IsStopEnabled = true;
                IsLaunchEnabled = true;
                isSimulationRunning = true;
                RefreshScenarioPreview();
                AddLog("[송신] StartSimulation - 모의 시작.");
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
                nom.setValue("stopFlag", new NBool(true));
                nomHandler.SendNOMMessage(nom);

                IsStartEnabled = true;
                IsStopEnabled = false;
                IsLaunchEnabled = false;
                ClearAppliedScenarioState();
                AddLog("[송신] Stop - 모의 중지.");
            }
            catch (Exception ex)
            {
                AddLog($"[오류] Stop 실패: {ex.Message}");
            }
        }

        [RelayCommand]
        private void SendLaunchCommand()
        {
            SendLaunchCommandForTarget(LaunchTargetId);
        }

        [RelayCommand]
        private void LaunchThreat(string? targetId)
        {
            if (!string.IsNullOrWhiteSpace(targetId))
            {
                LaunchTargetId = targetId;
            }

            SendLaunchCommandForTarget(LaunchTargetId);
        }

        [RelayCommand]
        private void ClearLog()
        {
            EventLogList.Clear();
        }

        public bool CanAddScenarioThreat => ScenarioThreats.Count < 4;
        public bool CanRemoveScenarioThreat => ScenarioThreats.Count > 1;

        [RelayCommand]
        private void AddScenarioThreat()
        {
            if (!CanAddScenarioThreat) return;

            AddScenarioThreatCore();
            UpdateScenarioThreatCommandState();
        }

        [RelayCommand]
        private void RemoveScenarioThreat()
        {
            if (!CanRemoveScenarioThreat) return;

            ScenarioThreats.RemoveAt(ScenarioThreats.Count - 1);
            UpdateScenarioThreatCommandState();
        }

        [RelayCommand]
        private void AddScenarioWaypoint(OcAirThreatInput? threat)
        {
            threat?.AddWaypoint();
        }

        [RelayCommand]
        private void RemoveScenarioWaypoint(OcAirThreatInput? threat)
        {
            threat?.RemoveWaypoint();
        }

        public void ApplyScenarioPreview()
        {
            ResetThreatRuntimeStates();
            isScenarioApplied = true;
            RefreshScenarioPreview();
        }

        public void RefreshScenarioPreview()
        {
            if (!isScenarioApplied)
            {
                ClearScenarioDisplay();
                return;
            }

            var activeThreats = ScenarioThreats.Take(4).ToList();
            TargetCount = activeThreats.Count.ToString();

            ScenarioThreatDisplays.Clear();
            MapThreatMarkers.Clear();
            MapThreatPaths.Clear();

            var threatPanelHeight = GetThreatPanelHeight(activeThreats.Count);
            var threatNameFontSize = activeThreats.Count >= 4 ? 18 : 20;
            var threatCoordinateFontSize = activeThreats.Count >= 4 ? 14 : 16;

            foreach (var threat in activeThreats)
            {
                var firstPoint = threat.Points.FirstOrDefault();
                var targetId = ParseUInt(threat.TargetId, (uint)threat.Index);
                var position = GetThreatPosition(targetId, firstPoint);
                var brush = GetThreatStateBrush(targetId);
                var pathBrush = ThreatBrushes[Math.Max(0, threat.Index - 1) % ThreatBrushes.Length];

                ScenarioThreatDisplays.Add(new OcAirThreatDisplay
                {
                    Name = threat.Name,
                    TargetId = threat.TargetId,
                    PosX = FormatCoordinate(position.X),
                    PosY = FormatCoordinate(position.Y),
                    PosZ = FormatCoordinate(position.Z),
                    NameBrush = brush,
                    PanelHeight = threatPanelHeight,
                    NameFontSize = threatNameFontSize,
                    CoordinateFontSize = threatCoordinateFontSize
                });

                var path = new PointCollection();
                for (var p = 0; p < threat.Points.Count && p < 4; p++)
                {
                    var point = threat.Points[p];
                    var mapped = ToMapPoint(ParseDouble(point.X, 0), ParseDouble(point.Y, 0));
                    path.Add(mapped);
                    MapThreatMarkers.Add(new OcMapMarkerItem
                    {
                        Left = mapped.X - 7,
                        Top = mapped.Y - 7,
                        Label = $"{threat.Index}-{p + 1}",
                        Fill = pathBrush
                    });
                }

                MapThreatPaths.Add(new OcMapPathItem
                {
                    Points = path,
                    Stroke = pathBrush
                });
            }
        }

        private void ClearAppliedScenarioState()
        {
            isScenarioApplied = false;
            ResetThreatRuntimeStates();
            ClearScenarioDisplay();
            DetectionEventList.Clear();
            EngagementResultList.Clear();
            LaunchTargetId = "1";
            InterceptionResultText = "대기중";
            InterceptionResultDetail = "모의 시작 및 표적 탐지 대기";
            InterceptionResultColor = new SolidColorBrush(Color.FromRgb(37, 40, 64));
        }

        private void ClearScenarioDisplay()
        {
            TargetCount = "0";
            ScenarioThreatDisplays.Clear();
            MapThreatMarkers.Clear();
            MapThreatPaths.Clear();
        }

        private static double GetThreatPanelHeight(int threatCount)
        {
            return threatCount switch
            {
                <= 1 => 136,
                2 => 112,
                3 => 92,
                _ => 76
            };
        }

        private void ResetThreatRuntimeStates()
        {
            isSimulationRunning = false;
            lastEngagedTargetId = null;
            detectedTargetIds.Clear();
            destroyedTargetIds.Clear();
            latestTargetPositions.Clear();
            ResetMissileDisplays();
        }

        private (double X, double Y, double Z) GetThreatPosition(uint targetId, OcScenarioPointInput? fallbackPoint)
        {
            if (latestTargetPositions.TryGetValue(targetId, out var position))
            {
                return position;
            }

            return (
                ParseDouble(fallbackPoint?.X ?? "0", 0),
                ParseDouble(fallbackPoint?.Y ?? "0", 0),
                ParseDouble(fallbackPoint?.Z ?? "0", 0)
            );
        }

        private Brush GetThreatStateBrush(uint targetId)
        {
            if (destroyedTargetIds.Contains(targetId)) return Brushes.Red;
            if (detectedTargetIds.Contains(targetId)) return Brushes.Lime;
            if (isSimulationRunning) return Brushes.Yellow;
            return Brushes.Gray;
        }

        private static string FormatCoordinate(double value)
        {
            return NormalizeCoordinate(value).ToString("F0");
        }

        private static double NormalizeCoordinate(double value)
        {
            return Math.Abs(value) >= 1000 ? value / 1000.0 : value;
        }

        partial void OnRssPosXChanged(string value) => RefreshMapGeometry();
        partial void OnRssPosYChanged(string value) => RefreshMapGeometry();
        partial void OnRssPosZChanged(string value)
        {
            if (value != "0") RssPosZ = "0";
        }

        partial void OnRssRadiusChanged(string value) => RefreshMapGeometry();
        partial void OnMlsPosXChanged(string value) => RefreshMapGeometry();
        partial void OnMlsPosYChanged(string value) => RefreshMapGeometry();
        partial void OnMlsPosZChanged(string value)
        {
            if (value != "0") MlsPosZ = "0";
        }

        private void InitializeScenarioInputs()
        {
            ScenarioThreats.Clear();
            AddScenarioThreatCore();
            UpdateScenarioThreatCommandState();
        }

        private void AddScenarioThreatCore()
        {
            var index = ScenarioThreats.Count + 1;
            var threat = new OcAirThreatInput(index);
            OffsetDefaultThreatPath(threat, index);
            ScenarioThreats.Add(threat);
        }

        private void UpdateScenarioThreatCommandState()
        {
            OnPropertyChanged(nameof(CanAddScenarioThreat));
            OnPropertyChanged(nameof(CanRemoveScenarioThreat));
        }

        private void OffsetDefaultThreatPath(OcAirThreatInput threat, int index)
        {
            var xOffset = (index - 1) * 25;
            var yOffset = (index - 1) * -18;
            foreach (var point in threat.Points)
            {
                point.X = (ParseDouble(point.X, 0) - xOffset).ToString("F0");
                point.Y = (ParseDouble(point.Y, 0) + yOffset).ToString("F0");
            }
        }

        private static Point ToMapPoint(double x, double y)
        {
            return new Point(MapCenterX + NormalizeCoordinate(x) * MapScale, MapCenterY - NormalizeCoordinate(y) * MapScale);
        }

        private void RefreshMapGeometry()
        {
            var radarCenter = ToMapPoint(ParseDouble(RssPosX, 0), ParseDouble(RssPosY, 0));
            var radarRadius = Math.Max(6, NormalizeCoordinate(ParseDouble(RssRadius, 50)) * MapScale);
            RadarRangeDiameter = radarRadius * 2;
            RadarRangeLeft = radarCenter.X - radarRadius;
            RadarRangeTop = radarCenter.Y - radarRadius;
            RadarIconLeft = radarCenter.X - 31;
            RadarIconTop = radarCenter.Y - 31;

            var launcherCenter = ToMapPoint(ParseDouble(MlsPosX, 0), ParseDouble(MlsPosY, 0));
            LauncherIconLeft = launcherCenter.X - 42;
            LauncherIconTop = launcherCenter.Y - 29;
        }

        private void SendLaunchCommandForTarget(string targetIdText)
        {
            try
            {
                var nom = nomHandler.GetNMessage("LaunchCommand")?.createNOMInstance();
                if (nom == null) { AddLog("[오류] LaunchCommand NOM 없음"); return; }

                var targetId = ParseUInt(targetIdText, 1);
                nom.setValue("Header.MessageID", new NUShort(0x09));
                nom.setValue("Header.MessageLength", new NUShort(2));
                nom.setValue("targetID", new NUInteger(targetId));
                nomHandler.SendNOMMessage(nom);

                lastEngagedTargetId = targetId;
                AddLog($"[송신] LaunchCommand - targetID={targetId}");
            }
            catch (Exception ex)
            {
                AddLog($"[오류] LaunchCommand 실패: {ex.Message}");
            }
        }

        private void OnNOMMessageSent(NOM nomInstance, EMessageOperation operation)
        {
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

        private void RouteReceivedMessage(NOM nom)
        {
            MarkSimulatorConnectedByMessageId(nom);

            switch (nom.name)
            {
                case "ATSStatus": HandleATSStatus(nom); break;
                case "RSSStatus": HandleRSSStatus(nom); break;
                case "MLSStatus": HandleMLSStatus(nom); break;
                case "MSSStatus": HandleMSSStatus(nom); break;
                case "TargetDetection": HandleTargetDetection(nom); break;
                case "TargetDestroyed": HandleTargetDestroyed(nom); break;
                default:
                    l.Warn($"[MainViewModel] Unhandled message: {nom.name}");
                    break;
            }
        }

        private void HandleATSStatus(NOM nom)
        {
            MarkSimulatorConnected("ATS");

            uint count = 0;
            var countVal = nom.getValue("targetCount");
            if (countVal != null) count = countVal.toUInt();

            AtsTargetList.Clear();
            for (uint i = 0; i < count && i < 20; i++)
            {
                var id = nom.getValue("targetInfo.targetID", (int)i);
                var px = nom.getValue("targetInfo.pos.x", (int)i);
                var py = nom.getValue("targetInfo.pos.y", (int)i);
                var pz = nom.getValue("targetInfo.pos.z", (int)i);
                var spd = nom.getValue("targetInfo.speed", (int)i);
                var flag = nom.getValue("targetInfo.interceptionFlag", (int)i);
                var targetId = id != null ? id.toUInt() : i + 1;
                var posX = px != null ? NormalizeCoordinate(px.toDouble()) : 0;
                var posY = py != null ? NormalizeCoordinate(py.toDouble()) : 0;
                var posZ = pz != null ? NormalizeCoordinate(pz.toDouble()) : 0;
                var isDestroyed = flag != null && flag.toUInt() != 0;

                latestTargetPositions[targetId] = (posX, posY, posZ);
                isSimulationRunning = true;
                if (isDestroyed)
                {
                    destroyedTargetIds.Add(targetId);
                }

                AtsTargetList.Add(new OcAtsTargetItem
                {
                    TargetId = targetId,
                    PosX = posX,
                    PosY = posY,
                    PosZ = posZ,
                    Speed = spd != null ? spd.toUInt() : 0,
                    StatusText = isDestroyed ? "격추" : "기동중"
                });
            }

            RefreshScenarioPreview();
        }

        private void HandleRSSStatus(NOM nom)
        {
            MarkSimulatorConnected("RSS");
        }

        private void HandleMLSStatus(NOM nom)
        {
            MarkSimulatorConnected("MLS");

            MlsMissile1 = GetMissileStatusText(nom.getValue("launcherInfo.missileStatus1"));
            MlsMissile2 = GetMissileStatusText(nom.getValue("launcherInfo.missileStatus2"));
            MlsMissile3 = GetMissileStatusText(nom.getValue("launcherInfo.missileStatus3"));
            MlsMissile4 = GetMissileStatusText(nom.getValue("launcherInfo.missileStatus4"));
            var stock = nom.getValue("launcherInfo.missileStock");
            MlsStock = stock != null ? stock.toUInt().ToString() : "-";

            UpdateMissileDisplayStatus(1, MlsMissile1);
            UpdateMissileDisplayStatus(2, MlsMissile2);
            UpdateMissileDisplayStatus(3, MlsMissile3);
            UpdateMissileDisplayStatus(4, MlsMissile4);
            RebuildMissileDisplayList();
        }

        private void HandleMSSStatus(NOM nom)
        {
            MarkSimulatorConnected("MSS");

            uint count = 0;
            var countVal = nom.getValue("missileCount");
            if (countVal != null) count = countVal.toUInt();

            for (uint i = 0; i < count && i < 4; i++)
            {
                var mid = nom.getValue("missileInfo.missileID", (int)i);
                var tid = nom.getValue("missileInfo.targetID", (int)i);
                var px = nom.getValue("missileInfo.pos.x", (int)i);
                var py = nom.getValue("missileInfo.pos.y", (int)i);
                var pz = nom.getValue("missileInfo.pos.z", (int)i);
                var st = nom.getValue("missileInfo.mssStatus", (int)i);
                var flag = nom.getValue("missileInfo.isIntercepted", (int)i);
                var missileId = mid != null ? mid.toUInt() : i + 1;

                var missile = GetOrCreateMissileDisplay(missileId);
                missile.TargetId = tid != null ? tid.toUInt() : 0;
                missile.PosX = px != null ? NormalizeCoordinate(px.toDouble()) : 0;
                missile.PosY = py != null ? NormalizeCoordinate(py.toDouble()) : 0;
                missile.PosZ = pz != null ? NormalizeCoordinate(pz.toDouble()) : 0;
                missile.StatusText = (flag != null && flag.toUInt() != 0) ? "요격성공" :
                                     (st != null && st.toInt() > 0) ? "추적중" : "대기";
            }

            RebuildMissileDisplayList();
        }

        private void ResetMissileDisplays()
        {
            missileDisplays.Clear();
            var launchX = NormalizeCoordinate(ParseDouble(MlsPosX, 0));
            var launchY = NormalizeCoordinate(ParseDouble(MlsPosY, 0));
            var launchZ = NormalizeCoordinate(ParseDouble(MlsPosZ, 0));
            for (uint i = 1; i <= 4; i++)
            {
                missileDisplays[i] = new OcMssMissileItem
                {
                    MissileId = i,
                    PosX = launchX,
                    PosY = launchY,
                    PosZ = launchZ,
                    StatusText = "대기"
                };
            }

            RebuildMissileDisplayList();
        }

        private OcMssMissileItem GetOrCreateMissileDisplay(uint missileId)
        {
            if (!missileDisplays.TryGetValue(missileId, out var missile))
            {
                missile = new OcMssMissileItem
                {
                    MissileId = missileId,
                    StatusText = "대기"
                };
                missileDisplays[missileId] = missile;
            }

            return missile;
        }

        private void UpdateMissileDisplayStatus(uint missileId, string statusText)
        {
            GetOrCreateMissileDisplay(missileId).StatusText = statusText;
        }

        private void RebuildMissileDisplayList()
        {
            MssMissileList = new ObservableCollection<OcMssMissileItem>(
                missileDisplays
                    .OrderBy(item => item.Key)
                    .Take(4)
                    .Select(item => item.Value));
        }

        private void HandleTargetDetection(NOM nom)
        {
            var idVal = nom.getValue("targetID");
            var sucVal = nom.getValue("targetDetectionSuccess");

            var targetId = idVal != null ? idVal.toUInt() : 0;
            var success = sucVal != null && sucVal.toUInt() != 0;

            DetectionEventList.Add(new OcDetectionEventItem
            {
                TimeStr = DateTime.Now.ToString("HH:mm:ss"),
                TargetId = targetId,
                Success = success ? "탐지 성공" : "탐지 실패"
            });

            AddLog($"[수신] TargetDetection - targetID={targetId}, 탐지={success}");

            if (success)
            {
                LaunchTargetId = targetId.ToString();
                lastEngagedTargetId = targetId;
                detectedTargetIds.Add(targetId);
            }
            else
            {
                detectedTargetIds.Remove(targetId);
            }

            RefreshScenarioPreview();
        }

        private void HandleTargetDestroyed(NOM nom)
        {
            var sucVal = nom.getValue("missionSuccess");
            var success = sucVal != null && sucVal.toUInt() != 0;

            if (success)
            {
                var targetId = lastEngagedTargetId ?? ParseUInt(LaunchTargetId, 0);
                if (targetId != 0)
                {
                    destroyedTargetIds.Add(targetId);
                }
                else
                {
                    foreach (var id in detectedTargetIds)
                    {
                        destroyedTargetIds.Add(id);
                    }
                }

                InterceptionResultText = "요격 성공!";
                InterceptionResultDetail = DateTime.Now.ToString("HH:mm:ss") + " 임무 완료";
                InterceptionResultColor = new SolidColorBrush(Color.FromRgb(29, 92, 56));
            }
            else
            {
                InterceptionResultText = "임무 실패";
                InterceptionResultDetail = DateTime.Now.ToString("HH:mm:ss") + " 표적 통과";
                InterceptionResultColor = new SolidColorBrush(Color.FromRgb(122, 26, 26));
            }

            EngagementResultList.Add(new OcEngagementResultItem
            {
                TimeStr = DateTime.Now.ToString("HH:mm:ss"),
                Result = success ? "요격 성공" : "임무 실패"
            });

            AddLog($"[수신] TargetDestroyed - missionSuccess={success}");
            RefreshScenarioPreview();
        }

        private static readonly SolidColorBrush ConnectedColor =
            new SolidColorBrush(Color.FromRgb(0, 230, 35));

        private static readonly SolidColorBrush DisconnectedColor =
            new SolidColorBrush(Color.FromRgb(255, 0, 0));

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
                case 0x02: MarkSimulatorConnected("ATS"); break;
                case 0x03: MarkSimulatorConnected("RSS"); break;
                case 0x04: MarkSimulatorConnected("MSS"); break;
                case 0x05: MarkSimulatorConnected("MLS"); break;
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

        private static string GetMissileStatusText(NValueType? val)
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

        private static double ParseDouble(string value, double fallback)
        {
            return double.TryParse(value, out var parsed) ? parsed : fallback;
        }

        private static uint ParseUInt(string value, uint fallback)
        {
            return uint.TryParse(value, out var parsed) ? parsed : fallback;
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

