#pragma once
/**
 * @file MFRSHeader.h
 * @brief OC-RSS 간 UDP ICD 메시지 ID와 내부 시뮬레이터 식별자 열거형을 정의한다.
 */

/**
 * @brief 외부 UDP ICD 메시지 식별자.
 *
 * UDPCommunicationManager가 OC 및 타 모의기와 송수신하는 외부 메시지 ID이다.
 */
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
	ATSInformationUplink,
	MSSInformationDownlinkToRSS,
	TargetDestroyed,
	ATSInterceptionResult,
	MSSInterceptionResult,
	Stop,
	MissionFailed,
};

/**
 * @brief 내부 NOM 메시지 식별자.
 *
 * UDPCommunicationManager와 RSS 내부 매니저 사이에서 사용되는 내부 메시지 ID이다.
 */
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

	// RSS ICD 내부 메시지
	InnerRSSStatusToComm = 0x30,

	// ATS ICD 내부 메시지
	InnerAirThreatDetonationToATM = 0x40,
	InnerAirThreatInfoToComm,

	// LCS ICD 내부 메시지
	InnerFireMissileAckToLCS = 0x50,
	InnerFireMissileToMSS,
	InnerSendMissileInfoToComm,

	// MSS ICD 내부 메시지
	InnerMissileInfoToComm = 0x60,
	InnerMissileInfoToDeto,
	InnerUplinkInfoToMiss,
	InnerUplinkInfoToDeto,
	InnerMissileDetonationToMiss,
	InnerMissileDetonationToComm,
	InnerFireMissileToMiss,
	
	// MFRS ICD 내부 메시지
	InnerAirThreatInfo = 0x70,
	InnerMissileInfo,
	InnerRadarDetectionInfo,
	InnerAirThreatDetonation,
};

/**
 * @brief 시뮬레이터 구성 요소 식별자.
 */
enum class SimulatorID
{
	TCC = 100,
	LCS,
	ATS,
	MSS,
	MFRS,
};

/**
 * @brief 전장 객체의 상태 구분값.
 */
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
