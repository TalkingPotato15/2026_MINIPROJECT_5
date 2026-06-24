#pragma once
/**
 * @file RSSManager.h
 * @brief RSS의 탐지 상태 관리, ATS/MSS 정보 처리, 요격 판정 메시지 송신을 담당하는 매니저를 정의한다.
 */

#include "DetectionManager.h"
#include "DetonationManager.h"
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <nFramework/nTimer/NTimer.h>
#include <map>

using namespace nframework;
using namespace nom;
using namespace nlinestream;

/**
 * @brief RSS(Radar Sensor System) 핵심 제어 매니저.
 *
 * RSSManager는 내부 NOM 메시지를 수신하여 레이다 탐지 영역, 공중위협 탐지 상태,
 * 유도탄 위치 기반 요격 판정을 관리한다. 탐지된 표적은 MSS로 uplink하고,
 * 탐지 상태 변화 및 요격 성공 결과를 UDPCommunicationManager로 전달한다.
 */
class BASEMGRDLL_API RSSManager : public BaseManager
{
public:
	/**
	 * @brief RSSManager 객체를 생성하고 내부 상태를 초기화한다.
	 */
	RSSManager(void);

	/**
	 * @brief RSSManager 객체를 해제한다.
	 */
	~RSSManager(void);

	/** @name BaseManager interface */
	/** @{ */
	virtual std::shared_ptr<NOM> registerMsg(tstring) override;
	virtual void discoverMsg(std::shared_ptr<NOM>) override;
	virtual void updateMsg(std::shared_ptr<NOM>) override;
	virtual void reflectMsg(std::shared_ptr<NOM>) override;
	virtual void deleteMsg(std::shared_ptr<NOM>) override;
	virtual void removeMsg(std::shared_ptr<NOM>) override;
	virtual void sendMsg(std::shared_ptr<NOM>) override;
	virtual void recvMsg(std::shared_ptr<NOM>) override;
	virtual void setUserName(tstring) override;
	virtual tstring getUserName() override;
	virtual void setData(void*) override;
	virtual bool start() override;
	virtual bool stop() override;
	virtual void setMEBComponent(IMEBComponent*) override;
	/** @} */

private:
	/**
	 * @brief 멤버 변수, 타이머, 메시지 처리 테이블 등 RSSManager 내부 자원을 초기화한다.
	 */
	void initialize();

	/**
	 * @brief RSSManager에서 보유한 내부 자원을 해제한다.
	 */
	void release();

	/**
	 * @brief 수신 NOM 이름과 처리 함수의 매핑 테이블을 구성한다.
	 */
	void funcMapInit();

	/**
	 * @brief 탐지 상태, 요격 상태, 레이다 탐지 영역 캐시를 초기화한다.
	 */
	void resetDetectionState();

	/**
	 * @brief RSS 상태 정보를 내부 통신 매니저로 주기 송신한다.
	 */
	void sendRSSStatus();

	/**
	 * @brief 모의 시작 내부 메시지를 처리하고 탐지 로직을 활성화한다.
	 * @param nomMsg 수신한 InnerStartSimulation NOM 메시지.
	 */
	void recvInnerStartSimulation(std::shared_ptr<NOM> nomMsg);

	/**
	 * @brief 모의 종료 내부 메시지를 처리하고 탐지/요격 상태를 초기화한다.
	 * @param nomMsg 수신한 InnerStopSimulation NOM 메시지.
	 */
	void recvInnerStopSimulation(std::shared_ptr<NOM> nomMsg);

	/**
	 * @brief RSS 레이다 위치와 탐지 반경 설정 메시지를 처리한다.
	 * @param nomMsg 수신한 InnerRSSDetectionAreaToRSS NOM 메시지.
	 */
	void recvInnerRSSDetectionAreaToRSS(std::shared_ptr<NOM> nomMsg);

	/**
	 * @brief ATS 공중위협 정보를 처리하여 탐지/미탐지 상태 전이를 수행한다.
	 * @param nomMsg 수신한 InnerATSInformationToRSS NOM 메시지.
	 *
	 * atsStatus가 active인 표적만 탐지 대상으로 삼는다. 표적이 탐지 반경 안으로
	 * 진입하면 TargetDetection 성공과 ATSInformationUplink를 송신하고, 탐지 중인
	 * 표적이 범위 밖으로 나가면 마지막 위치를 uplink한 뒤 미탐지 이벤트를 송신한다.
	 */
	void recvInnerATSInformationToRSS(std::shared_ptr<NOM> nomMsg);

	/**
	 * @brief MSS 유도탄 정보를 처리하여 탐지 중인 표적에 대한 거리 기반 요격 판정을 수행한다.
	 * @param nomMsg 수신한 InnerMSSInformationToRSS NOM 메시지.
	 *
	 * mssStatus가 0인 미발사 유도탄은 무시한다. targetId가 0이어도 유효한 표적일 수 있으므로
	 * ID 값이 아닌 mssStatus와 탐지 상태를 기준으로 처리한다. 현재 탐지 중인 표적에 대해서만
	 * ATS-MSS 거리를 계산하고, 요격 거리 조건을 만족하면 TargetDestroyed를 송신한다.
	 */
	void recvInnerMSSInformationToRSS(std::shared_ptr<NOM> nomMsg);

	/**
	 * @brief NOM 메시지에서 공중위협 정보를 읽어 캐시 구조체로 변환한다.
	 * @param nomMsg ATS 정보가 포함된 NOM 메시지.
	 * @param targetPrefix targetInfo 배열 항목 prefix.
	 * @param atsInfo 읽은 값을 저장할 공중위협 캐시 구조체.
	 * @return 필수 필드를 모두 읽으면 true, 누락 필드가 있으면 false.
	 */
	bool tryReadATSInfo(std::shared_ptr<NOM> nomMsg, const tstring& targetPrefix, CachedATSInfo& atsInfo) const;

	/**
	 * @brief NOM 메시지에서 유도탄 정보를 읽어 캐시 구조체로 변환한다.
	 * @param nomMsg MSS 정보가 포함된 NOM 메시지.
	 * @param missilePrefix missileInfo 배열 항목 prefix.
	 * @param mssInfo 읽은 값을 저장할 유도탄 캐시 구조체.
	 * @return 필수 필드를 모두 읽으면 true, 누락 필드가 있으면 false.
	 */
	bool tryReadMSSInfo(std::shared_ptr<NOM> nomMsg, const tstring& missilePrefix, CachedMSSInfo& mssInfo) const;

	/**
	 * @brief 표적 탐지 상태 변경 결과를 통신 매니저로 송신한다.
	 * @param targetID 탐지 상태가 변경된 공중위협 ID.
	 * @param success 1이면 탐지, 0이면 미탐지.
	 */
	void sendTargetDetection(uint32_t targetID, uint32_t success);

	/**
	 * @brief 요격 결과를 통신 매니저로 송신한다.
	 * @param targetID 요격 대상 공중위협 ID.
	 * @param missionFlag 0이면 요격 성공, 1이면 실패.
	 */
	void sendTargetDestroyed(uint32_t targetID, uint32_t missionFlag);

	/**
	 * @brief 탐지 중인 공중위협 정보를 MSS로 전달하기 위해 통신 매니저로 송신한다.
	 * @param atsInfo 송신할 공중위협 정보.
	 */
	void sendATSInformationUplink(const CachedATSInfo& atsInfo);

	/** @brief NOM 메시지 생성을 위한 MEB 컴포넌트 포인터. */
	IMEBComponent* meb;
	/** @brief NOM 메시지 송수신을 위한 MEC 컴포넌트 포인터. */
	MECComponent* mec;
	/** @brief 매니저 사용자 이름. */
	tstring name;
	/** @brief 등록된 NOM 메시지 맵. */
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	/** @brief discover된 NOM 메시지 맵. */
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
	/** @brief 수신 메시지 이름별 처리 함수 맵. */
	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> funcMap;
	/** @brief 레이다 탐지 영역과 탐지 표적 캐시 관리자. */
	DetectionManager detectionManager;
	/** @brief ATS-MSS 거리 기반 요격 판정 관리자. */
	DetonationManager detonationManager;
	/** @brief 모의 시작 후 탐지 처리가 활성화되었는지 나타내는 플래그. */
	bool detectionActive = false;

	/** @brief RSS 상태 주기 송신용 타이머 콜백. */
	std::function<void(void*)> periodicFunc;
	/** @brief nFramework 타이머 객체. */
	NTimer* nTimer;
	/** @brief RSS 상태 주기 송신 타이머 핸들. */
	int timerHandle;

	/** @brief RSSStatus 송신에 재사용하는 NOM 메시지 인스턴스. */
	std::shared_ptr<NOM> rssStatusNOM;

	/** @brief RSSManager 콘솔 로그 스트림. */
	NLineTstream ntcout{ Level::COUT };
};
