#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <map>
#include <functional>

using namespace nframework;
using namespace nom;

/**
 * @class  EngagementManager
 * @brief  교전 통제 Manager
 *         수신: TargetDetection(0x08), TargetDestroyed(0x0d), ATSStatus(0x02), MSSStatus(0x04)
 *         발행: ATSInformationToRSS(0x07), LaunchCommand(0x09), MSSInformationDownlinkToRSS(0x0c),
 *               ATSInterceptionResult(0x0e), MSSInterceptionResult(0x0f)
 */
class BASEMGRDLL_API EngagementManager : public BaseManager
{
public:
	EngagementManager(void);
	~EngagementManager(void);

public:
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

private:
	void initialize();
	void release();
	void funcMapInit();

	// 수신 핸들러
	void onATSStatus(std::shared_ptr<NOM> nomMsg);
	void onMSSStatus(std::shared_ptr<NOM> nomMsg);
	void onTargetDetection(std::shared_ptr<NOM> nomMsg);
	void onTargetDestroyed(std::shared_ptr<NOM> nomMsg);

	// 발행 헬퍼
	void sendATSInformationToRSS();
	void sendMSSInformationDownlinkToRSS();
	void sendLaunchCommand(unsigned int targetID);
	void sendInterceptionResult(unsigned int targetID, bool success);

private:
	IMEBComponent* meb = nullptr;
	MECComponent*  mec = nullptr;
	tstring        name;

	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> funcMap;

	// 최근 ATS/MSS 상태 캐시 (RSS 릴레이용)
	std::shared_ptr<NOM> lastATSStatus;
	std::shared_ptr<NOM> lastMSSStatus;

	bool missionInProgress = false;
};
