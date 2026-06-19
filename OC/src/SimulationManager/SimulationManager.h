#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nTimer/NTimer.h>
#include <map>
#include <functional>

using namespace nframework;
using namespace nom;

/**
 * @class  SimulationManager
 * @brief  모의 시작/중지 제어 및 각 CSC 상태 수신 Manager
 *         - StartSimulation(0x06), Stop(0x10) 발행
 *         - ATSStatus(0x02), RSSStatus(0x03), MSSStatus(0x04), MLSStatus(0x05) 수신
 */
class BASEMGRDLL_API SimulationManager : public BaseManager
{
public:
	SimulationManager(void);
	~SimulationManager(void);

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

	void onATSStatus(std::shared_ptr<NOM> nomMsg);
	void onRSSStatus(std::shared_ptr<NOM> nomMsg);
	void onMSSStatus(std::shared_ptr<NOM> nomMsg);
	void onMLSStatus(std::shared_ptr<NOM> nomMsg);

private:
	IMEBComponent* meb = nullptr;
	MECComponent*  mec = nullptr;
	tstring        name;

	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> funcMap;

	// 각 CSC 연결 상태 (마지막 수신 시각 등으로 관리 가능)
	bool atsConnected  = false;
	bool rssConnected  = false;
	bool mssConnected  = false;
	bool mlsConnected  = false;
	bool simRunning    = false;
};
