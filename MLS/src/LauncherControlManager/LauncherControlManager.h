#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nTimer/NTimer.h>
#include <functional>

#include "MLSBaseModel.h"

using namespace nframework;
using namespace nom;
using namespace std;

class BASEMGRDLL_API LauncherControlManager : public BaseManager
{
public:
	LauncherControlManager(void);
	~LauncherControlManager(void);

public:
	// inherited from the BaseManager class
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
	void stopPeriodicTask();

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;

private:
	void simulatePeriodic();
	void inputScenario(std::shared_ptr<NOM>);
	void startMLS(std::shared_ptr<NOM>);
	void stopMLS(std::shared_ptr<NOM>);
	void launchMLS(std::shared_ptr<NOM>);
	void sendInnerIgnitionCommand(unsigned int, unsigned int);


private:
	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> msgFuncMap;
	std::unique_ptr<MLSBaseModel> launcherModel;
	static constexpr double SIMULATION_TICK_SECONDS = 1.0;
	static constexpr int HEARTBEAT_INTERVAL_MS = 1000;
	NTimer* nTimer = nullptr;
	int timerHandle = 0;
};

