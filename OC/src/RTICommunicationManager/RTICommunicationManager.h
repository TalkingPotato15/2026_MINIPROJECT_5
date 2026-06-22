#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/comm/HLACommInterface.h>
#include <nFramework/Log4nf/Loggable.h>
#include <sstream>
#include <vector>
#include <iostream>
#include <atomic>
#include <future>
#include <thread>

using namespace nframework;
using namespace nom;
using namespace nicelink;
using namespace log4nf;

class BASEMGRDLL_API RTICommunicationManager : public BaseManager
{
public:
	RTICommunicationManager(void);
	~RTICommunicationManager(void);

	// inherited from the BaseManager class
	std::shared_ptr<NOM> registerMsg(std::wstring) override;
	void discoverMsg(std::shared_ptr<NOM>) override;
	void updateMsg(std::shared_ptr<NOM>) override;
	void reflectMsg(std::shared_ptr<NOM>) override;
	void deleteMsg(std::shared_ptr<NOM>) override;
	void removeMsg(std::shared_ptr<NOM>) override;
	void sendMsg(std::shared_ptr<NOM>) override;
	void recvMsg(std::shared_ptr<NOM>) override;
	void setUserName(std::wstring) override;
	tstring getUserName() override;
	void setData(void*) override;
	bool start() override;
	bool stop() override;
	void setMEBComponent(IMEBComponent*) override;

private:
	void initialize();
	void release();
	void resignFed();
	void joinFed();

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsg;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsg;

	std::unique_ptr<CommunicationInterface> hlaCommunicator;
	CommunicationConfig* hlaCommConfig;

	std::mutex mut;

	std::shared_ptr<bool> isStarted = std::make_shared<bool>(false);

	std::atomic<bool> continueSimFlag;

	static inline Loggable l{ L"RTICommunicationManager" };
	
};


