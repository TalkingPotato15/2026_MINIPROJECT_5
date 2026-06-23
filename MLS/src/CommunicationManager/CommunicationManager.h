#pragma once
#include <nFramework/mec/MECComponent.h>
#include <nFramework/comm/NCommInterface.h>
#include "CommMessageHandler.h"
#include <nFramework/nom/NOMParser.h>
using namespace std;
using namespace nframework;
using namespace nom;
using namespace ncomm;

class BASEMGRDLL_API CommunicationManager : public BaseManager
{
public:
	CommunicationManager(void);
	~CommunicationManager(void);

public:
	// inherited from the BaseManager class
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

public:
	void processRecvMessage(unsigned char* data, int size);
	unsigned int getObjectInstanceID(shared_ptr<NOM> nomMsg);

private:
	void init();
	void release();
	void sendInnerMsg(shared_ptr<NOM> nomMsg);
	void funcMapInit();

private:
	void recvSendScenario(shared_ptr<NOM> nomMsg);
	void recvStartSimulation(shared_ptr<NOM> nomMsg);
	void recvStopSimulation(shared_ptr<NOM> nomMsg);
	void recvLaunchCommand(shared_ptr<NOM> nomMsg);
	void recvInnerMLSStatus(shared_ptr<NOM> nomMsg);
	void recvInnerIgnitionCommand(shared_ptr<NOM> nomMsg);
	
public:
	std::unique_ptr<NOMParser> nomParser;

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	map<unsigned int, shared_ptr<NOM>> registeredMsg;
	map<unsigned int, shared_ptr<NOM>> discoveredMsg;
	map<tstring, function<void(shared_ptr<NOM>)>> funcMap;

	CommunicationInterface* commInterface;
	CommunicationConfig* commConfig;
	CommMessageHandler commMsgHandler;
};

