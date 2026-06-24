#pragma once
/**
 * @file UDPCommunicationManager.h
 * @brief UDP ICD 메시지와 내부 NOM 메시지 간 변환을 담당하는 통신 매니저를 정의한다.
 */

#include <nFramework/mec/MECComponent.h>
#include <nFramework/comm/NCommInterface.h>
#include "CommMessageHandler.h"
#include <nFramework/nom/NOMParser.h>
#include <nFramework/nLineStream/NLineStreamMain.h>

#include "MFRSHeader.h"

using namespace std;
using namespace nframework;
using namespace nom;
using namespace ncomm;

/**
 * @brief OC와 RSS 내부 매니저 사이의 UDP 통신 브리지.
 *
 * 외부 UDP 메시지를 수신해 NOM 메시지로 파싱하고 내부 매니저가 구독하는
 * Inner 메시지로 변환한다. 반대로 RSSManager에서 송신한 내부 결과 메시지를
 * OC ICD 형식의 외부 메시지로 변환하여 UDP로 송신한다.
 */
class BASEMGRDLL_API UDPCommunicationManager : public BaseManager
{
public:
	/**
	 * @brief UDPCommunicationManager 객체를 생성하고 통신 자원을 초기화한다.
	 */
	UDPCommunicationManager(void);

	/**
	 * @brief UDPCommunicationManager 객체를 해제한다.
	 */
	~UDPCommunicationManager(void);

public:
	/** @name BaseManager interface */
	/** @{ */
	virtual shared_ptr<NOM> registerMsg(tstring) override;
	virtual void discoverMsg(shared_ptr<NOM>) override;
	virtual void updateMsg(shared_ptr<NOM>) override;
	virtual void reflectMsg(shared_ptr<NOM>) override;
	virtual void deleteMsg(shared_ptr<NOM>) override;
	virtual void removeMsg(shared_ptr<NOM>) override;
	virtual void sendMsg(shared_ptr<NOM>) override;
	virtual void recvMsg(shared_ptr<NOM>) override;
	virtual void setUserName(tstring) override;
	virtual tstring getUserName() override;
	virtual void setData(void*) override;
	virtual bool start() override;
	virtual bool stop() override;
	virtual void setMEBComponent(IMEBComponent*) override;
	/** @} */
	
public:
	/**
	 * @brief UDP로 수신한 직렬화 버퍼를 NOM 메시지로 변환하여 처리한다.
	 * @param data 수신한 UDP payload 버퍼.
	 * @param size payload 크기.
	 */
	void processRecvMessage(unsigned char* data, int size);

	/**
	 * @brief NOM 메시지에서 객체 인스턴스 ID를 조회한다.
	 * @param nomMsg 객체 인스턴스 ID를 포함한 NOM 메시지.
	 * @return 객체 인스턴스 ID.
	 */
	unsigned int getObjectInstanceID(shared_ptr<NOM> nomMsg);
	
private:
	/**
	 * @brief 통신 인터페이스, NOM 파서, 메시지 처리 테이블을 초기화한다.
	 */
	void init();

	/**
	 * @brief 통신 인터페이스와 내부 자원을 해제한다.
	 */
	void release();

	/**
	 * @brief 외부에서 수신한 메시지를 내부 NOM 메시지로 송신한다.
	 * @param nomMsg 내부로 전달할 NOM 메시지.
	 */
	void sendInnerMsg(shared_ptr<NOM> nomMsg);

	/**
	 * @brief NOM 메시지 이름과 수신 처리 함수 매핑을 구성한다.
	 */
	void funcMapInit();

private:
	/** @brief 시나리오 생성 메시지를 처리한다. */
	void recvScenario(shared_ptr<NOM> nomMsg);

	/** @brief 시나리오 배포 메시지를 내부 시나리오 배포 메시지로 변환한다. */
	void recvSendScenario(shared_ptr<NOM> nomMsg);

	/** @brief 모의 시작 메시지를 내부 모의 시작 메시지로 변환한다. */
	void recvStartSimulation(shared_ptr<NOM> nomMsg);

	/** @brief 모의 중지 요청 메시지를 처리한다. */
	void recvStop(shared_ptr<NOM> nomMsg);

	/** @brief ATS 요격 결과 메시지를 처리한다. */
	void recvATSInterceptionResult(shared_ptr<NOM> nomMsg);

	/** @brief 임무 실패 메시지를 처리한다. */
	void recvMissionFailed(shared_ptr<NOM> nomMsg);

	/** @brief 모의 종료 메시지를 내부 모의 종료 메시지로 변환한다. */
	void recvStopSimulation(shared_ptr<NOM> nomMsg);

	/** @brief 내부 시나리오 배포 ACK를 외부 통신 이벤트로 처리한다. */
	void recvInnerSendScenarioAck(shared_ptr<NOM> nomMsg);

	/** @brief 내부 모의 시작 ACK를 외부 통신 이벤트로 처리한다. */
	void recvInnerStartSimulationAck(shared_ptr<NOM> nomMsg);

	/** @brief 내부 모의 종료 ACK를 외부 통신 이벤트로 처리한다. */
	void recvInnerStopSimulationAck(shared_ptr<NOM> nomMsg);

	/** @brief 내부 시뮬레이터 상태 메시지를 외부 상태 메시지로 변환한다. */
	void recvInnerSimulatorStateComm(shared_ptr<NOM> nomMsg);

	/** @brief RSS 상태 내부 메시지를 외부 RSSStatus 메시지로 변환한다. */
	void recvInnerRSSStatusToComm(shared_ptr<NOM> nomMsg);

	/** @brief 외부 ATSInformationToRSS 메시지를 내부 InnerATSInformationToRSS 메시지로 변환한다. */
	void recvATSInformationToRSS(shared_ptr<NOM> nomMsg);

	/** @brief 외부 MSSInformationDownlinkToRSS 메시지를 내부 InnerMSSInformationToRSS 메시지로 변환한다. */
	void recvMSSInformationDownlinkToRSS(shared_ptr<NOM> nomMsg);

	/** @brief 내부 표적 탐지 결과를 외부 TargetDetection 메시지로 변환한다. */
	void recvInnerTargetDetectionToComm(shared_ptr<NOM> nomMsg);

	/** @brief 내부 표적 파괴 결과를 외부 TargetDestroyed 메시지로 변환한다. */
	void recvInnerTargetDestroyedToComm(shared_ptr<NOM> nomMsg);

	/** @brief 내부 ATS uplink 정보를 외부 ATSInformationUplink 메시지로 변환한다. */
	void recvInnerATSInformationUplinkToComm(shared_ptr<NOM> nomMsg);

	/** @brief 내부 경로 정보를 외부 통신 메시지로 변환한다. */
	void recvInnerRouteToComm(shared_ptr<NOM> nomMsg);

	/** @brief 내부 공중위협 정보를 외부 통신 메시지로 변환한다. */
	void recvInnerAirThreatInfo(shared_ptr<NOM> nomMsg);

	/** @brief 유도탄 폭발 메시지를 처리한다. */
	void recvMissileDetonation(shared_ptr<NOM> nomMsg);
	
public:
	/** @brief UDP payload와 NOM 메시지 간 직렬화/역직렬화를 수행하는 파서. */
	std::unique_ptr<NOMParser> nomParser;

private:
	/** @brief NOM 메시지 생성을 위한 MEB 컴포넌트 포인터. */
	IMEBComponent* meb;

	/** @brief NOM 메시지 송수신을 위한 MEC 컴포넌트 포인터. */
	MECComponent* mec;

	/** @brief 매니저 사용자 이름. */
	tstring name;

	/** @brief 등록된 NOM 메시지 맵. */
	map<unsigned int, shared_ptr<NOM>> registeredMsg;

	/** @brief discover된 NOM 메시지 맵. */
	map<unsigned int, shared_ptr<NOM>> discoveredMsg;

	/** @brief 수신 메시지 이름별 처리 함수 맵. */
	map<tstring, function<void(shared_ptr<NOM>)>> funcMap;

	/** @brief UDP 송수신을 수행하는 통신 인터페이스. */
	CommunicationInterface* commInterface;

	/** @brief UDP 통신 설정 정보. */
	CommunicationConfig* commConfig;

	/** @brief ICD 메시지 ID와 NOM 메시지 이름 매핑 관리자. */
	CommMessageHandler commMsgHandler;

	/** @brief UI/모델로 전달할 경로 문자열 캐시. */
	tstring routeString;
};

