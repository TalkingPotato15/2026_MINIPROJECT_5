#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nTimer/NTimer.h>
#include <nFramework/Log4nF/Loggable.h>
#include <sstream>
#include <chrono>


using namespace nframework;
using namespace nom;
using namespace log4nf;


class BASEMGRDLL_API CommandManager : public BaseManager
{
public:
	CommandManager(void);
	~CommandManager(void);

public:
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
	void processStartResume(std::shared_ptr<NOM>);
	
private:
	void init();
	void release();

	void testSend();
	void testSendArgs(wchar_t*);

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsg;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsg;

	std::shared_ptr<NOM> testObjNOM;
	NTimer* nTimer;

	std::vector<tstring> weapons;

	static inline Loggable l{ L"CommandManager" };
	
};

