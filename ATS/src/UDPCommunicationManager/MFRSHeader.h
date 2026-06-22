#pragma once

enum class ICD_MessageID
{
    Scenario = 0x01,
    ATSStatus,
    RSSStatus,
    MSSStatus,
    MLSStatus,
    StartSimulation,
    ATSInformationToRSS,
    TargetDetection,
    LaunchCommand,
    IgnitionCommand = 0x0A,
    ATSInformationUplink,
    MSSInformationDownlinkToRSS,
    TargetDestroyed,
    ATSInterceptionResult,
    MSSInterceptionResult,
    Stop
};

enum class InnerICD_MessageID
{
    InnerSendScenario = 0x21,
    InnerSendScenarioToModel = 0x23,
    InnerStartSimulation = 0x24,
    InnerStartSimulationToModel = 0x26,
    InnerStopSimulation = 0x27,
    InnerStopSimulationToModel = 0x29,
    InnerAirThreatDetonationToATM = 0x40,
    InnerAirThreatInfoToComm = 0x41
};
