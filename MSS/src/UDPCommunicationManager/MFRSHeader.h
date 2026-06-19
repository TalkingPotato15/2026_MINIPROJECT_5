#pragma once

enum class ICD_MessageID
{
	// OC SAMS ICD
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
	SimulatorState,
	MSSInformationDownlinkToRSS,
	TargetDestroyed,
	ATSInterceptionResult,
	MSSInterceptionResult,
	Stop,
	MissionFailed,
};

enum class InnerICD_MessageID
{
	// 공용 ICD 내부 메시지
	InnerSimulatorStateToComm = 0x20,
	InnerSendScenario,
	InnerSendScenarioAck,
	InnerSendScenarioToModel,
	InnerStartSimulation,
	InnerStartSimulationAck,
	InnerStartSimulationToModel,
	InnerStopSimulation,
	InnerStopSimulationAck,
	InnerStopSimulationToModel = 0x29,

	// ATS ICD 내부 메시지
	InnerAirThreatDetonationToATM = 0x40,
	InnerAirThreatInfoToComm,

	// MSS ICD 내부 메시지
	InnerMissileInfoToComm = 0x60,    // MSS 상태 → Comm 전달 (MSSStatus 0x04 발행)
	InnerMissileInfoToDeto,           // MSS 상태 → 격폭 모듈 전달
	InnerUplinkInfoToMiss,            // ATS 표적 위치 → 유도탄 전달 (SimulatorState 0x0b 수신)
	InnerUplinkInfoToDeto,            // ATS 표적 위치 → 격폭 모듈 전달
	InnerMissileDetonationToMiss,     // 요격 결과 → 유도탄 전달 (MSSInterceptionResult 0x0f 수신)
	InnerMissileDetonationToComm,     // 요격 결과 → Comm 전달
	InnerFireMissileToMiss,           // 발사 명령 → 유도탄 전달 (IgnitionCommand 0x0a 수신)
};

enum class SimulatorID
{
	TCC = 100,
	LCS,
	ATS,
	MSS,
	MFRS,
};

enum class TrackState
{
	// ATS
	ATS_Flight = 0,
	ATS_Detonation,

	// MSS
	MSS_Flight = 10,
	MSS_Detonation,
	MSS_EmergencyDetonation,
};