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
        public string StatusText { get; set; } = "\uAE30\uB3D9\uC911";
    }

    public class OcMssMissileItem
    {
        public uint MissileId { get; set; }
        public uint TargetId { get; set; }
        public double PosX { get; set; }
        public double PosY { get; set; }
        public double PosZ { get; set; }
        public string LauncherStatusText { get; set; } = "\uB300\uAE30";
        public string FlightStatusText { get; set; } = "";
        public bool HasFlightStatus { get; set; }
        public string StatusText { get; set; } = "\uB300\uAE30";
        public string SummaryText => HasFlightStatus
            ? $"{MissileId}\uBC88 \uC720\uB3C4\uD0C4: {StatusText}  X:{PosX:F0} Y:{PosY:F0} Z:{PosZ:F0}"
            : $"{MissileId}\uBC88 \uC720\uB3C4\uD0C4: {StatusText}";
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
        private static readonly (string X, string Y, string Z)[] FirstThreatDefaultRoute =
        {
            ("-160", "300", "10"),
            ("140", "160", "10"),
            ("-100", "20", "10"),
            ("80", "-120", "10")
        };

        private static readonly (string X, string Y, string Z)[] SecondThreatDefaultRoute =
        {
            ("-250", "40", "10"),
            ("-90", "35", "10"),
            ("90", "-30", "10"),
            ("245", "-80", "10")
        };

        private static readonly (string X, string Y, string Z)[] ThirdThreatDefaultRoute =
        {
            ("40", "40", "10"),
            ("110", "70", "10"),
            ("185", "115", "10"),
            ("245", "150", "10")
        };

        private static readonly (string X, string Y, string Z)[] FourthThreatDefaultRoute =
        {
            ("-245", "220", "10"),
            ("-230", "260", "10"),
            ("210", "300", "10"),
            ("255", "340", "10")
        };

        public OcAirThreatInput(int index)
        {
            Index = index;
            Name = $"\uACF5\uC911\uC704\uD611 {index}";
            _isEnabled = true;
            _targetId = (index - 1).ToString();
            _speed = "300";

            var defaultRoute = GetDefaultRoute(index);
            var startPoint = defaultRoute[0];
            var endPoint = defaultRoute[defaultRoute.Length - 1];
            Points.Add(new OcScenarioPointInput("\uC2DC\uC791\uC810", startPoint.X, startPoint.Y, startPoint.Z));
            Points.Add(new OcScenarioPointInput("\uC885\uB8CC\uC810", endPoint.X, endPoint.Y, endPoint.Z));
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
            var insertionIndex = Points.Count;

            var defaultWaypoint = GetDefaultWaypoint(insertionIndex);
            Points.Add(defaultWaypoint.HasValue
                ? new OcScenarioPointInput("", defaultWaypoint.Value.X, defaultWaypoint.Value.Y, defaultWaypoint.Value.Z)
                : new OcScenarioPointInput(
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
                    0 => "\uC2DC\uC791\uC810",
                    var last when last == Points.Count - 1 => "\uC885\uB8CC\uC810",
                    _ => $"\uACBD\uC720\uC810{i}"
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

        private static (string X, string Y, string Z)[] GetDefaultRoute(int index)
        {
            return index switch
            {
                1 => FirstThreatDefaultRoute,
                2 => SecondThreatDefaultRoute,
                3 => ThirdThreatDefaultRoute,
                4 => FourthThreatDefaultRoute,
                _ => FirstThreatDefaultRoute
            };
        }

        private (string X, string Y, string Z)? GetDefaultWaypoint(int insertionIndex)
        {
            var defaultRoute = GetDefaultRoute(Index);
            if (insertionIndex > 0 && insertionIndex < defaultRoute.Length - 1)
            {
                return defaultRoute[insertionIndex];
            }

            return null;
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
        public Visibility LaunchButtonVisibility { get; set; } = Visibility.Collapsed;
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

    public class OcAircraftMarkerItem
    {
        public double Left { get; set; }
        public double Top { get; set; }
        public double Angle { get; set; }
        public string Label { get; set; } = "";
        public Brush Fill { get; set; } = Brushes.Gray;
    }

    public class OcMissileMarkerItem
    {
        public double Left { get; set; }
        public double Top { get; set; }
        public double Angle { get; set; }
        public string Label { get; set; } = "";
        public Brush Fill { get; set; } = Brushes.OrangeRed;
    }

    public class OcExplosionMarkerItem
    {
        public double Left { get; set; }
        public double Top { get; set; }
        public double Size { get; set; } = 84;
    }

    public class OcMapPathItem
    {
        public PointCollection Points { get; set; } = new();
        public Brush Stroke { get; set; } = Brushes.Lime;
    }

    internal readonly struct OcAtsStatusSlot
    {
        public OcAtsStatusSlot(
            uint slotIndex,
            bool hasTargetId,
            uint rawTargetId,
            double posX,
            double posY,
            double posZ,
            uint speed,
            uint atsStatus)
        {
            SlotIndex = slotIndex;
            HasTargetId = hasTargetId;
            RawTargetId = rawTargetId;
            PosX = posX;
            PosY = posY;
            PosZ = posZ;
            Speed = speed;
            AtsStatus = atsStatus;
        }

        public uint SlotIndex { get; }
        public bool HasTargetId { get; }
        public uint RawTargetId { get; }
        public double PosX { get; }
        public double PosY { get; }
        public double PosZ { get; }
        public uint Speed { get; }
        public uint AtsStatus { get; }
        public bool HasSignal =>
            Speed != 0 ||
            AtsStatus != 0 ||
            Math.Abs(PosX) > 0.000001 ||
            Math.Abs(PosY) > 0.000001 ||
            Math.Abs(PosZ) > 0.000001;
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
        private const double ThreatEndReachTolerance = 5.0;
        private const double ThreatEndPathTolerance = 25.0;

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
        private readonly HashSet<uint> failedTargetIds = new();
        private readonly HashSet<uint> failedMissileIds = new();
        private readonly Dictionary<uint, uint> sentInterceptionResultFlags = new();
        private readonly Dictionary<uint, (double X, double Y, double Z)> latestTargetPositions = new();
        private readonly Dictionary<uint, double> latestTargetHeadings = new();
        private readonly Dictionary<uint, OcMssMissileItem> missileDisplays = new();
        private readonly Dictionary<uint, uint> reportedHitMissileByTargetId = new();
        private readonly Dictionary<uint, uint> successfulMissileByTargetId = new();

        [ObservableProperty] private bool _isPlugInEnabled = false;
        [ObservableProperty] private bool _isPlugOutEnabled = false;
        [ObservableProperty] private bool _isStartEnabled = false;
        [ObservableProperty] private bool _isStopEnabled = false;
        [ObservableProperty] private bool _isLaunchEnabled = false;

        [ObservableProperty] private string _rssPosX = "0";
        [ObservableProperty] private string _rssPosY = "0";
        [ObservableProperty] private string _rssPosZ = "0";
        [ObservableProperty] private string _rssRadius = "175";
        [ObservableProperty] private string _mlsPosX = "100";
        [ObservableProperty] private string _mlsPosY = "0";
        [ObservableProperty] private string _mlsPosZ = "0";
        [ObservableProperty] private string _targetCount = "0";
        [ObservableProperty] private string _launchTargetId = "0";

        [ObservableProperty] private string _atsStatusText = "ATS \uBBF8\uC5F0\uACB0";
        [ObservableProperty] private string _rssStatusText = "RSS \uBBF8\uC5F0\uACB0";
        [ObservableProperty] private string _mlsStatusText = "MLS \uBBF8\uC5F0\uACB0";
        [ObservableProperty] private string _mssStatusText = "MSS \uBBF8\uC5F0\uACB0";

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
        [ObservableProperty] private ObservableCollection<OcAircraftMarkerItem> _mapAircraftMarkers = new();
        [ObservableProperty] private ObservableCollection<OcMissileMarkerItem> _mapMissileMarkers = new();
        [ObservableProperty] private ObservableCollection<OcExplosionMarkerItem> _mapExplosionMarkers = new();
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
        [ObservableProperty] private string _remainingMissileCountText = "-";

        [ObservableProperty] private string _interceptionResultText = "\uC694\uACA9 \uB300\uAE30";
        [ObservableProperty] private string _interceptionResultDetail = "\uD310\uC815 \uB300\uAE30";
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
                AddLog("[SYSTEM] nFramework connected.");
            }
            else
            {
                IsPlugInEnabled = true;
                AddLog("[WARN] nFramework connection failed. Use Plug In to retry.");
                MessageBox.Show("nFramework connection failed.");
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
                AddLog("[SYSTEM] Plug In succeeded.");
            }
            else
            {
                IsPlugInEnabled = true;
                AddLog("[WARN] Plug In failed.");
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
            AddLog("[SYSTEM] Plug Out.");
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
                    AddLog("[ERR] Scenario NOM not found");
                    return;
                }

                var threats = ScenarioThreats.Take(4).ToList();
                var count = (uint)threats.Count;

                nom.setValue("Header.MessageID", new NUShort(0x01));
                nom.setValue("Header.MessageLength", new NUShort(452));

                var threatsBySlot = new OcAirThreatInput?[4];
                var slotSummary = new List<string>();
                foreach (var threat in threats)
                {
                    var targetId = ParseUInt(threat.TargetId, (uint)(threat.Index - 1));
                    var slot = GetScenarioTransportSlot(targetId);
                    threatsBySlot[slot] = threat;
                    slotSummary.Add($"{targetId}->sceneInfo[{slot}]");
                }

                for (var i = 0; i < 4; i++)
                {
                    var prefix = $"sceneInfo[{i}]";
                    var threat = threatsBySlot[i];
                    var points = threat?.Points.ToList() ?? new List<OcScenarioPointInput>();
                    var speed = threat != null ? ParseUInt(threat.Speed, 300) : 0;

                    for (var pointIndex = 0; pointIndex < 4; pointIndex++)
                    {
                        var point = pointIndex < points.Count ? points[pointIndex] : points.LastOrDefault();
                        nom.setValue($"{prefix}.ATSPos[{pointIndex}].x", new NDouble(ParseDouble(point?.X ?? "0", 0)));
                        nom.setValue($"{prefix}.ATSPos[{pointIndex}].y", new NDouble(ParseDouble(point?.Y ?? "0", 0)));
                        nom.setValue($"{prefix}.ATSPos[{pointIndex}].z", new NDouble(ParseDouble(point?.Z ?? "0", 0)));
                    }

                    nom.setValue($"{prefix}.speed", new NUInteger(speed));
                }

                nom.setValue("rssPos.x", new NDouble(ParseDouble(RssPosX, 0)));
                nom.setValue("rssPos.y", new NDouble(ParseDouble(RssPosY, 0)));
                nom.setValue("rssPos.z", new NDouble(ParseDouble(RssPosZ, 0)));
                nom.setValue("rssRadius", new NUInteger(ToUInt(ParseDouble(RssRadius, 175))));

                nom.setValue("mlsPos.x", new NDouble(ParseDouble(MlsPosX, 0)));
                nom.setValue("mlsPos.y", new NDouble(ParseDouble(MlsPosY, 0)));
                nom.setValue("mlsPos.z", new NDouble(ParseDouble(MlsPosZ, 0)));

                nomHandler.SendNOMMessage(nom);
                AddLog($"[TX] Scenario distributed - targetCount={count}, slots={string.Join(", ", slotSummary)}");
            }
            catch (Exception ex)
            {
                AddLog($"[ERR] Scenario distribution failed: {ex.Message}");
            }
        }

        [RelayCommand]
        private void StartSimulation()
        {
            try
            {
                var nom = nomHandler.GetNMessage("StartSimulation")?.createNOMInstance();
                if (nom == null) { AddLog("[ERR] StartSimulation NOM not found"); return; }

                nom.setValue("Header.MessageID", new NUShort(0x06));
                nom.setValue("Header.MessageLength", new NUShort(4));
                nom.setValue("startFlag", new NUInteger(1));
                nomHandler.SendNOMMessage(nom);

                IsStartEnabled = false;
                IsStopEnabled = true;
                IsLaunchEnabled = true;
                isSimulationRunning = true;
                RefreshScenarioPreview();
                AddLog("[TX] StartSimulation - startFlag=1");
            }
            catch (Exception ex)
            {
                AddLog($"[ERR] StartSimulation failed: {ex.Message}");
            }
        }

        [RelayCommand]
        private void StopSimulation()
        {
            try
            {
                var nom = nomHandler.GetNMessage("Stop")?.createNOMInstance();
                if (nom == null) { AddLog("[ERR] Stop NOM not found"); return; }

                nom.setValue("Header.MessageID", new NUShort(0x10));
                nom.setValue("Header.MessageLength", new NUShort(4));
                nom.setValue("stopFlag", new NUInteger(1));
                nomHandler.SendNOMMessage(nom);

                IsStartEnabled = true;
                IsStopEnabled = false;
                IsLaunchEnabled = false;
                ClearAppliedScenarioState();
                AddLog("[TX] Stop - stopFlag=1");
            }
            catch (Exception ex)
            {
                AddLog($"[ERR] Stop failed: {ex.Message}");
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
            MapAircraftMarkers.Clear();
            MapThreatPaths.Clear();

            var threatPanelHeight = GetThreatPanelHeight(activeThreats.Count);
            var threatNameFontSize = activeThreats.Count >= 4 ? 18 : 20;
            var threatCoordinateFontSize = activeThreats.Count >= 4 ? 14 : 16;
            var showScenarioRoutes = !isSimulationRunning;

            foreach (var threat in activeThreats)
            {
                var firstPoint = threat.Points.FirstOrDefault();
                var targetId = ParseUInt(threat.TargetId, (uint)(threat.Index - 1));
                var position = GetThreatPosition(targetId, firstPoint);
                var aircraftPoint = ToMapPoint(position.X, position.Y);
                var brush = GetThreatStateBrush(targetId);
                var modelBrush = GetThreatModelBrush(targetId);
                var canLaunch = detectedTargetIds.Contains(targetId) && !destroyedTargetIds.Contains(targetId);
                var aircraftHeading = GetThreatHeading(targetId, threat);

                ScenarioThreatDisplays.Add(new OcAirThreatDisplay
                {
                    Name = threat.Name,
                    TargetId = threat.TargetId,
                    PosX = FormatCoordinate(position.X),
                    PosY = FormatCoordinate(position.Y),
                    PosZ = FormatCoordinate(position.Z),
                    NameBrush = brush,
                    LaunchButtonVisibility = canLaunch ? Visibility.Visible : Visibility.Collapsed,
                    PanelHeight = threatPanelHeight,
                    NameFontSize = threatNameFontSize,
                    CoordinateFontSize = threatCoordinateFontSize
                });

                if (showScenarioRoutes)
                {
                    var pathBrush = ThreatBrushes[Math.Max(0, threat.Index - 1) % ThreatBrushes.Length];
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

                if (!destroyedTargetIds.Contains(targetId))
                {
                    MapAircraftMarkers.Add(new OcAircraftMarkerItem
                    {
                        Left = aircraftPoint.X - 19,
                        Top = aircraftPoint.Y - 19,
                        Angle = aircraftHeading,
                        Label = threat.Index.ToString(),
                        Fill = modelBrush
                    });
                }
            }

            RebuildMissileMapMarkers();
        }

        private void ClearAppliedScenarioState()
        {
            isScenarioApplied = false;
            ResetThreatRuntimeStates();
            ClearScenarioDisplay();
            DetectionEventList.Clear();
            EngagementResultList.Clear();
            LaunchTargetId = "0";
            InterceptionResultText = "\uC694\uACA9 \uB300\uAE30";
            InterceptionResultDetail = "\uD310\uC815 \uB300\uAE30";
            InterceptionResultColor = new SolidColorBrush(Color.FromRgb(37, 40, 64));
        }

        private void ClearScenarioDisplay()
        {
            TargetCount = "0";
            ScenarioThreatDisplays.Clear();
            MapThreatMarkers.Clear();
            MapAircraftMarkers.Clear();
            MapMissileMarkers.Clear();
            MapExplosionMarkers.Clear();
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
            failedTargetIds.Clear();
            failedMissileIds.Clear();
            sentInterceptionResultFlags.Clear();
            reportedHitMissileByTargetId.Clear();
            successfulMissileByTargetId.Clear();
            latestTargetPositions.Clear();
            latestTargetHeadings.Clear();
            AtsTargetList.Clear();
            MapExplosionMarkers.Clear();
            ResetMissileDisplays();
        }

        private bool ShouldApplyRuntimeUpdates()
        {
            return isScenarioApplied && isSimulationRunning;
        }

        private HashSet<uint> GetActiveScenarioTargetIds()
        {
            return ScenarioThreats
                .Take(4)
                .Select((threat, index) => ParseUInt(threat.TargetId, (uint)index))
                .Where(targetId => targetId <= 3)
                .ToHashSet();
        }

        private static int GetScenarioTransportSlot(uint targetId)
        {
            return Math.Clamp((int)targetId, 0, 3);
        }

        private static List<OcAtsStatusSlot> ReadAtsStatusSlots(NOM nom)
        {
            var slots = new List<OcAtsStatusSlot>(4);

            for (uint i = 0; i < 4; i++)
            {
                var prefix = $"targetInfo[{i}]";
                var id = nom.getValue($"{prefix}.targetId");
                var px = nom.getValue($"{prefix}.ATSPos.x");
                var py = nom.getValue($"{prefix}.ATSPos.y");
                var pz = nom.getValue($"{prefix}.ATSPos.z");
                var spd = nom.getValue($"{prefix}.speed");
                var status = nom.getValue($"{prefix}.atsStatus");

                slots.Add(new OcAtsStatusSlot(
                    i,
                    id != null,
                    id != null ? id.toUInt() : 0,
                    px != null ? px.toDouble() : 0,
                    py != null ? py.toDouble() : 0,
                    pz != null ? pz.toDouble() : 0,
                    spd != null ? spd.toUInt() : 0,
                    status != null ? status.toUInt() : 0));
            }

            return slots;
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

        private OcAirThreatInput? FindScenarioThreat(uint targetId)
        {
            return ScenarioThreats
                .Take(4)
                .FirstOrDefault(threat => ParseUInt(threat.TargetId, (uint)(threat.Index - 1)) == targetId);
        }

        private bool HasThreatReachedEnd(uint targetId, double posX, double posY)
        {
            var threat = FindScenarioThreat(targetId);
            if (threat == null || threat.Points.Count < 2) return false;

            var end = threat.Points[^1];
            var beforeEnd = threat.Points[^2];
            var endX = ParseDouble(end.X, 0);
            var endY = ParseDouble(end.Y, 0);
            if (Distance2D(posX, posY, endX, endY) <= ThreatEndReachTolerance)
            {
                return true;
            }

            var startX = ParseDouble(beforeEnd.X, 0);
            var startY = ParseDouble(beforeEnd.Y, 0);
            var vx = endX - startX;
            var vy = endY - startY;
            var lengthSquared = vx * vx + vy * vy;
            if (lengthSquared < 0.0001) return false;

            var projection = ((posX - startX) * vx + (posY - startY) * vy) / lengthSquared;
            if (projection < 1.0) return false;

            var projectedX = startX + projection * vx;
            var projectedY = startY + projection * vy;
            return Distance2D(posX, posY, projectedX, projectedY) <= ThreatEndPathTolerance;
        }

        private static double Distance2D(double ax, double ay, double bx, double by)
        {
            var dx = ax - bx;
            var dy = ay - by;
            return Math.Sqrt(dx * dx + dy * dy);
        }

        private Brush GetThreatStateBrush(uint targetId)
        {
            if (destroyedTargetIds.Contains(targetId)) return Brushes.Gray;
            if (detectedTargetIds.Contains(targetId)) return Brushes.Red;
            return Brushes.Yellow;
        }

        private Brush GetThreatModelBrush(uint targetId)
        {
            if (failedTargetIds.Contains(targetId)) return Brushes.Gray;
            return detectedTargetIds.Contains(targetId) ? Brushes.Red : Brushes.Yellow;
        }

        private double GetThreatHeading(uint targetId, OcAirThreatInput threat)
        {
            if (latestTargetHeadings.TryGetValue(targetId, out var heading))
            {
                return heading;
            }

            if (threat.Points.Count >= 2)
            {
                var from = threat.Points[0];
                var to = threat.Points[1];
                return CalculateHeading(
                    ParseDouble(from.X, 0),
                    ParseDouble(from.Y, 0),
                    ParseDouble(to.X, 0),
                    ParseDouble(to.Y, 0));
            }

            return 0;
        }

        private static double CalculateHeading(double fromX, double fromY, double toX, double toY)
        {
            var dx = NormalizeCoordinate(toX) - NormalizeCoordinate(fromX);
            var dy = NormalizeCoordinate(toY) - NormalizeCoordinate(fromY);
            if (Math.Abs(dx) < 0.001 && Math.Abs(dy) < 0.001)
            {
                return 0;
            }

            return Math.Atan2(dx, dy) * 180.0 / Math.PI;
        }

        private static string FormatCoordinate(double value)
        {
            return NormalizeCoordinate(value).ToString("F0");
        }

        private static double NormalizeCoordinate(double value)
        {
            return value;
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
            ScenarioThreats.Add(threat);
        }

        private void UpdateScenarioThreatCommandState()
        {
            OnPropertyChanged(nameof(CanAddScenarioThreat));
            OnPropertyChanged(nameof(CanRemoveScenarioThreat));
        }

        private static Point ToMapPoint(double x, double y)
        {
            return new Point(MapCenterX + NormalizeCoordinate(x) * MapScale, MapCenterY - NormalizeCoordinate(y) * MapScale);
        }

        private void RefreshMapGeometry()
        {
            var radarCenter = ToMapPoint(ParseDouble(RssPosX, 0), ParseDouble(RssPosY, 0));
            var radarRadius = Math.Max(6, NormalizeCoordinate(ParseDouble(RssRadius, 175)) * MapScale);
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
                if (nom == null) { AddLog("[ERR] LaunchCommand NOM not found"); return; }

                var targetId = ParseUInt(targetIdText, 0);
                nom.setValue("Header.MessageID", new NUShort(0x09));
                nom.setValue("Header.MessageLength", new NUShort(4));
                nom.setValue("targetID", new NUInteger(targetId));
                nomHandler.SendNOMMessage(nom);

                lastEngagedTargetId = targetId;
                AddLog($"[TX] LaunchCommand - targetID={targetId}");
            }
            catch (Exception ex)
            {
                AddLog($"[ERR] LaunchCommand failed: {ex.Message}");
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
                    AddLog($"[ERR] Receive processing exception: {ex.Message}");
                }
            });
        }

        private void RouteReceivedMessage(NOM nom)
        {
            MarkSimulatorConnectedByMessageId(nom);

            var messageId = nom.getValue("Header.MessageID")?.toUInt();
            if (messageId == 0x0d)
            {
                HandleTargetDestroyed(nom);
                return;
            }

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

            if (!ShouldApplyRuntimeUpdates()) return;

            var slots = ReadAtsStatusSlots(nom);
            var activeTargetIds = GetActiveScenarioTargetIds();

            AtsTargetList.Clear();
            foreach (var slot in slots)
            {
                var targetId = slot.HasTargetId ? slot.RawTargetId : slot.SlotIndex;
                if (!slot.HasTargetId && !slot.HasSignal)
                {
                    continue;
                }

                if (targetId != slot.SlotIndex) continue;
                if (!activeTargetIds.Contains(targetId)) continue;

                var posX = NormalizeCoordinate(slot.PosX);
                var posY = NormalizeCoordinate(slot.PosY);
                var posZ = NormalizeCoordinate(slot.PosZ);
                var atsStatus = slot.AtsStatus;
                var isFailed = failedTargetIds.Contains(targetId);
                var isDestroyed = atsStatus == 2 && !isFailed;

                if (latestTargetPositions.TryGetValue(targetId, out var previousPosition))
                {
                    latestTargetHeadings[targetId] = CalculateHeading(previousPosition.X, previousPosition.Y, posX, posY);
                }

                latestTargetPositions[targetId] = (posX, posY, posZ);
                if (isDestroyed)
                {
                    destroyedTargetIds.Add(targetId);
                }
                else if (!failedTargetIds.Contains(targetId) && HasThreatReachedEnd(targetId, posX, posY))
                {
                    RegisterInterceptionFailure(targetId, "ATS reached endpoint");
                    isFailed = true;
                }

                AtsTargetList.Add(new OcAtsTargetItem
                {
                    TargetId = targetId,
                    PosX = posX,
                    PosY = posY,
                    PosZ = posZ,
                    Speed = slot.Speed,
                    StatusText = isFailed ? "\uC694\uACA9\uC2E4\uD328" : isDestroyed ? "\uACA9\uCD94" : atsStatus == 0 ? "\uB300\uAE30" : "\uAE30\uB3D9\uC911"
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
            var stockText = stock != null ? stock.toUInt().ToString() : "-";
            MlsStock = stockText;
            RemainingMissileCountText = stockText;

            UpdateMissileLauncherStatus(1, MlsMissile1);
            UpdateMissileLauncherStatus(2, MlsMissile2);
            UpdateMissileLauncherStatus(3, MlsMissile3);
            UpdateMissileLauncherStatus(4, MlsMissile4);
            RebuildMissileDisplayList();
        }

        private void HandleMSSStatus(NOM nom)
        {
            MarkSimulatorConnected("MSS");

            if (!ShouldApplyRuntimeUpdates()) return;

            for (uint i = 0; i < 4; i++)
            {
                var prefix = $"missileInfo[{i}]";
                var mid = nom.getValue($"{prefix}.missileId");
                var tid = nom.getValue($"{prefix}.targetId");
                var px = nom.getValue($"{prefix}.MSSPos.x");
                var py = nom.getValue($"{prefix}.MSSPos.y");
                var pz = nom.getValue($"{prefix}.MSSPos.z");
                var st = nom.getValue($"{prefix}.mssStatus");
                var missileId = mid != null ? mid.toUInt() : i + 1;
                var rawTargetId = tid != null ? tid.toUInt() : (lastEngagedTargetId ?? ParseUInt(LaunchTargetId, 0));
                var mssStatus = st != null ? st.toUInt() : 0;

                var missile = GetOrCreateMissileDisplay(missileId);
                missile.TargetId = ResolveInterceptionTargetId(rawTargetId);
                missile.PosX = px != null ? NormalizeCoordinate(px.toDouble()) : 0;
                missile.PosY = py != null ? NormalizeCoordinate(py.toDouble()) : 0;
                missile.PosZ = pz != null ? NormalizeCoordinate(pz.toDouble()) : 0;

                if (failedMissileIds.Contains(missileId))
                {
                    MarkMissileAsFailed(missile);
                    continue;
                }

                if (failedTargetIds.Contains(missile.TargetId) && (missile.HasFlightStatus || mssStatus == 1 || mssStatus == 2 || mssStatus == 3))
                {
                    MarkMissileAsFailed(missile);
                    continue;
                }

                if (successfulMissileByTargetId.TryGetValue(missile.TargetId, out var winnerMissileId))
                {
                    if (winnerMissileId == missileId)
                    {
                        MarkMissileAsSucceeded(missile);
                    }
                    else if (missile.HasFlightStatus || mssStatus == 1 || mssStatus == 2)
                    {
                        MarkMissileAsFailed(missile);
                    }

                    continue;
                }

                if (mssStatus == 2)
                {
                    reportedHitMissileByTargetId[missile.TargetId] = missileId;
                    missile.FlightStatusText = GetMssFlightStatusText(mssStatus);
                    missile.HasFlightStatus = true;
                    RefreshMissileDisplayStatus(missile);
                    AddLog($"[RX] MSSStatus - missileID={missileId}, targetID={missile.TargetId}, waiting RSS decision");
                }
                else if (mssStatus == 1)
                {
                    missile.FlightStatusText = GetMssFlightStatusText(mssStatus);
                    missile.HasFlightStatus = true;
                    RefreshMissileDisplayStatus(missile);
                }
                else if (mssStatus == 3)
                {
                    MarkMissileAsFailed(missile);
                }
                else
                {
                    RefreshMissileDisplayStatus(missile);
                }
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
                    LauncherStatusText = "\uB300\uAE30",
                    FlightStatusText = "",
                    HasFlightStatus = false,
                    StatusText = "\uB300\uAE30"
                };
            }

            MlsStock = "-";
            RemainingMissileCountText = "-";
            RebuildMissileDisplayList();
        }

        private OcMssMissileItem GetOrCreateMissileDisplay(uint missileId)
        {
            if (!missileDisplays.TryGetValue(missileId, out var missile))
            {
                missile = new OcMssMissileItem
                {
                    MissileId = missileId,
                    LauncherStatusText = "\uB300\uAE30",
                    FlightStatusText = "",
                    HasFlightStatus = false,
                    StatusText = "\uB300\uAE30"
                };
                missileDisplays[missileId] = missile;
            }

            return missile;
        }

        private void UpdateMissileLauncherStatus(uint missileId, string statusText)
        {
            var missile = GetOrCreateMissileDisplay(missileId);
            missile.LauncherStatusText = statusText;
            RefreshMissileDisplayStatus(missile);
        }

        private static void RefreshMissileDisplayStatus(OcMssMissileItem missile)
        {
            missile.StatusText = missile.HasFlightStatus
                ? missile.FlightStatusText
                : missile.LauncherStatusText;
        }

        private void RebuildMissileDisplayList()
        {
            MssMissileList = new ObservableCollection<OcMssMissileItem>(
                missileDisplays
                    .OrderBy(item => item.Key)
                    .Take(4)
                    .Select(item => item.Value));
            RebuildMissileMapMarkers();
        }

        private void RebuildMissileMapMarkers()
        {
            MapMissileMarkers.Clear();
            if (!isScenarioApplied || !isSimulationRunning) return;

            foreach (var missile in missileDisplays
                         .OrderBy(item => item.Key)
                         .Take(4)
                         .Select(item => item.Value))
            {
                if (!missile.HasFlightStatus) continue;
                if (IsTerminalMissileStatus(missile.StatusText)) continue;

                var point = ToMapPoint(missile.PosX, missile.PosY);
                MapMissileMarkers.Add(new OcMissileMarkerItem
                {
                    Left = point.X - 14,
                    Top = point.Y - 22,
                    Angle = GetMissileHeading(missile),
                    Label = missile.MissileId.ToString(),
                    Fill = Brushes.Lime
                });
            }
        }

        private double GetMissileHeading(OcMssMissileItem missile)
        {
            if (latestTargetPositions.TryGetValue(missile.TargetId, out var targetPosition))
            {
                return CalculateHeading(missile.PosX, missile.PosY, targetPosition.X, targetPosition.Y);
            }

            return CalculateHeading(
                NormalizeCoordinate(ParseDouble(MlsPosX, 0)),
                NormalizeCoordinate(ParseDouble(MlsPosY, 0)),
                missile.PosX,
                missile.PosY);
        }


        private void HandleTargetDetection(NOM nom)
        {
            if (!ShouldApplyRuntimeUpdates()) return;

            var idVal = nom.getValue("targetID");
            var sucVal = nom.getValue("targetDetectonSuccess") ?? nom.getValue("targetDetectionSuccess");

            var targetId = idVal != null ? idVal.toUInt() : 0;
            var success = sucVal != null && sucVal.toUInt() != 0;

            DetectionEventList.Add(new OcDetectionEventItem
            {
                TimeStr = DateTime.Now.ToString("HH:mm:ss"),
                TargetId = targetId,
                Success = success ? "\uD0D0\uC9C0 \uC131\uACF5" : "\uD0D0\uC9C0 \uC2E4\uD328"
            });

            AddLog($"[RX] TargetDetection - targetID={targetId}, detected={success}");

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
            if (!ShouldApplyRuntimeUpdates()) return;

            var idVal = nom.getValue("targetID");
            var missionFlagVal = nom.getValue("missionFlag");
            var targetIdFromMessage = ResolveInterceptionTargetId(idVal != null ? idVal.toUInt() : (lastEngagedTargetId ?? ParseUInt(LaunchTargetId, 0)));

            if (missionFlagVal == null)
            {
                AddLog("[ERR] TargetDestroyed missionFlag field missing");
                return;
            }

            var missionFlag = missionFlagVal.toUInt();
            var success = missionFlag == 0;

            if (success)
            {
                RegisterInterceptionSuccess(targetIdFromMessage, "TargetDestroyed");
            }
            else
            {
                RegisterInterceptionFailure(targetIdFromMessage, "TargetDestroyed");
            }

            AddLog($"[RX] TargetDestroyed - targetID={targetIdFromMessage}, missionFlag={missionFlag}, success={success}");
            RefreshScenarioPreview();
        }

        private void RegisterInterceptionSuccess(uint targetId, string source, uint? winningMissileId = null)
        {
            targetId = ResolveInterceptionTargetId(targetId);
            failedTargetIds.Remove(targetId);

            var resolvedWinningMissileId = ResolveWinningMissileId(targetId, winningMissileId);
            if (resolvedWinningMissileId.HasValue)
            {
                successfulMissileByTargetId[targetId] = resolvedWinningMissileId.Value;
            }

            var firstSuccess = destroyedTargetIds.Add(targetId);
            detectedTargetIds.Remove(targetId);
            lastEngagedTargetId = targetId;

            InterceptionResultText = "\uC694\uACA9 \uC131\uACF5";
            InterceptionResultDetail = DateTime.Now.ToString("HH:mm:ss") + " \uC784\uBB34 \uC644\uB8CC";
            InterceptionResultColor = new SolidColorBrush(Color.FromRgb(29, 92, 56));

            if (firstSuccess)
            {
                EngagementResultList.Add(new OcEngagementResultItem
                {
                    TimeStr = DateTime.Now.ToString("HH:mm:ss"),
                    Result = "\uC694\uACA9 \uC131\uACF5"
                });

                ShowInterceptionExplosion(targetId);
            }

            if (resolvedWinningMissileId.HasValue)
            {
                var winner = GetOrCreateMissileDisplay(resolvedWinningMissileId.Value);
                winner.TargetId = targetId;
                MarkMissileAsSucceeded(winner);
                MarkFlyingMissilesAsFailed(targetId, resolvedWinningMissileId.Value);
            }

            SendInterceptionResultToSimulatorsIfChanged(targetId, 0, source);

            RefreshInterceptionUiState();
        }

        private uint? ResolveWinningMissileId(uint targetId, uint? explicitMissileId)
        {
            if (explicitMissileId.HasValue)
            {
                return explicitMissileId.Value;
            }

            if (reportedHitMissileByTargetId.TryGetValue(targetId, out var reportedMissileId))
            {
                return reportedMissileId;
            }

            return missileDisplays.Values
                .Where(missile => missile.TargetId == targetId && missile.HasFlightStatus && !IsTerminalMissileStatus(missile.StatusText))
                .OrderBy(missile => missile.MissileId)
                .Select(missile => (uint?)missile.MissileId)
                .FirstOrDefault();
        }

        private void RegisterInterceptionFailure(uint targetId, string source)
        {
            targetId = ResolveInterceptionTargetId(targetId);
            if (destroyedTargetIds.Contains(targetId)) return;

            var firstFailure = failedTargetIds.Add(targetId);
            lastEngagedTargetId = targetId;
            MarkFlyingMissilesAsFailed(targetId, null);

            InterceptionResultText = "\uC694\uACA9 \uC2E4\uD328";
            InterceptionResultDetail = DateTime.Now.ToString("HH:mm:ss") + " \uD45C\uC801 \uD1B5\uACFC";
            InterceptionResultColor = new SolidColorBrush(Color.FromRgb(122, 26, 26));

            if (firstFailure)
            {
                EngagementResultList.Add(new OcEngagementResultItem
                {
                    TimeStr = DateTime.Now.ToString("HH:mm:ss"),
                    Result = "\uC694\uACA9 \uC2E4\uD328"
                });
            }

            SendInterceptionResultToSimulatorsIfChanged(targetId, 1, source);

            RefreshInterceptionUiState();
        }

        private void RefreshInterceptionUiState()
        {
            RebuildMissileDisplayList();
            RefreshScenarioPreview();
        }

        private void ShowInterceptionExplosion(uint targetId)
        {
            var fallbackPoint = FindScenarioThreat(targetId)?.Points.FirstOrDefault();
            var position = GetThreatPosition(targetId, fallbackPoint);
            var point = ToMapPoint(position.X, position.Y);
            var explosion = new OcExplosionMarkerItem
            {
                Left = point.X - 42,
                Top = point.Y - 42,
                Size = 84
            };

            MapExplosionMarkers.Add(explosion);

            var timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromMilliseconds(950)
            };
            timer.Tick += (_, _) =>
            {
                timer.Stop();
                MapExplosionMarkers.Remove(explosion);
            };
            timer.Start();
        }

        private void MarkFlyingMissilesAsFailed(uint targetId, uint? excludedMissileId)
        {
            foreach (var missile in missileDisplays.Values)
            {
                if (excludedMissileId.HasValue && missile.MissileId == excludedMissileId.Value) continue;
                if (missile.TargetId != targetId) continue;
                if (!missile.HasFlightStatus) continue;
                if (IsTerminalMissileStatus(missile.StatusText)) continue;

                MarkMissileAsFailed(missile);
            }
        }

        private void MarkMissileAsSucceeded(OcMssMissileItem missile)
        {
            missile.FlightStatusText = "\uC694\uACA9\uC131\uACF5";
            missile.HasFlightStatus = true;
            RefreshMissileDisplayStatus(missile);
        }

        private void MarkMissileAsFailed(OcMssMissileItem missile)
        {
            failedMissileIds.Add(missile.MissileId);
            missile.FlightStatusText = "\uC694\uACA9\uC2E4\uD328";
            missile.HasFlightStatus = true;
            RefreshMissileDisplayStatus(missile);
        }

        private static bool IsTerminalMissileStatus(string statusText)
        {
            return statusText == "\uC694\uACA9\uC131\uACF5" || statusText == "\uC694\uACA9\uC2E4\uD328";
        }

        private uint ResolveInterceptionTargetId(uint candidateTargetId)
        {
            var activeTargetIds = GetActiveScenarioTargetIds();
            if (activeTargetIds.Contains(candidateTargetId))
            {
                return candidateTargetId;
            }

            if (lastEngagedTargetId.HasValue && activeTargetIds.Contains(lastEngagedTargetId.Value))
            {
                return lastEngagedTargetId.Value;
            }

            return activeTargetIds.Count == 1 ? activeTargetIds.First() : candidateTargetId;
        }

        private void SendInterceptionResultToSimulatorsIfChanged(uint targetId, uint missionFlag, string source)
        {
            if (sentInterceptionResultFlags.TryGetValue(targetId, out var sentFlag) && sentFlag == missionFlag)
            {
                return;
            }

            sentInterceptionResultFlags[targetId] = missionFlag;
            SendInterceptionResultToSimulators(targetId, missionFlag, source);
        }

        private void SendInterceptionResultToSimulators(uint targetId, uint missionFlag, string source)
        {
            SendInterceptionResultMessage("ATSInterceptionResult", 0x0e, targetId, missionFlag);
            SendInterceptionResultMessage("MSSInterceptionResult", 0x0f, targetId, missionFlag);
            AddLog($"[TX] Interception result - targetID={targetId}, missionFlag={missionFlag}, source={source}");
        }

        private void SendInterceptionResultMessage(string messageName, ushort messageId, uint targetId, uint missionFlag)
        {
            try
            {
                var nom = nomHandler.GetNMessage(messageName)?.createNOMInstance();
                if (nom == null)
                {
                    AddLog($"[ERR] {messageName} NOM not found");
                    return;
                }

                nom.setValue("Header.MessageID", new NUShort(messageId));
                nom.setValue("Header.MessageLength", new NUShort(8));
                nom.setValue("targetID", new NUInteger(targetId));
                nom.setValue("missionFlag", new NUInteger(missionFlag));
                nomHandler.SendNOMMessage(nom);
            }
            catch (Exception ex)
            {
                AddLog($"[ERR] {messageName} send failed: {ex.Message}");
            }
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
                    AtsStatusText = "ATS \uC5F0\uACB0\uB428";
                    AtsStatusColor = ConnectedColor;
                    break;
                case "RSS":
                    lastRssStatusAt = now;
                    RssStatusText = "RSS \uC5F0\uACB0\uB428";
                    RssStatusColor = ConnectedColor;
                    break;
                case "MLS":
                    lastMlsStatusAt = now;
                    MlsStatusText = "MLS \uC5F0\uACB0\uB428";
                    MlsStatusColor = ConnectedColor;
                    break;
                case "MSS":
                    lastMssStatusAt = now;
                    MssStatusText = "MSS \uC5F0\uACB0\uB428";
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
                AtsStatusText = "ATS \uBBF8\uC5F0\uACB0";
                AtsStatusColor = DisconnectedColor;
            }

            if (IsTimedOut(now, lastRssStatusAt))
            {
                RssStatusText = "RSS \uBBF8\uC5F0\uACB0";
                RssStatusColor = DisconnectedColor;
            }

            if (IsTimedOut(now, lastMlsStatusAt))
            {
                MlsStatusText = "MLS \uBBF8\uC5F0\uACB0";
                MlsStatusColor = DisconnectedColor;
            }

            if (IsTimedOut(now, lastMssStatusAt))
            {
                MssStatusText = "MSS \uBBF8\uC5F0\uACB0";
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
                0 => "\uC7A5\uC785",
                1 => "\uB300\uAE30",
                2 => "\uBC1C\uC0AC",
                _ => val.toUInt().ToString()
            };
        }

        private static string GetMssFlightStatusText(uint status)
        {
            return status switch
            {
                1 => "\uCD94\uC801\uC911",
                2 => "\uD310\uC815\uB300\uAE30",
                3 => "\uC694\uACA9\uC2E4\uD328",
                _ => ""
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

        private static uint ToUInt(double value)
        {
            if (double.IsNaN(value) || value <= 0) return 0;
            if (value >= uint.MaxValue) return uint.MaxValue;
            return (uint)Math.Round(value);
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

