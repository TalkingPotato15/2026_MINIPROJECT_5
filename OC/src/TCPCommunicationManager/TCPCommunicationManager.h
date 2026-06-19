#pragma once
#include <nFramework/mec/MECComponent.h>
#include <nFramework/comm/NCommInterface.h>
#include "CommMessageHandler.h"
#include <nFramework/nom/NOMParser.h>
#include <nFramework/Log4nF/Loggable.h>
using namespace std;
using namespace nframework;
using namespace nom;
using namespace ncomm;
using namespace log4nf;
class BASEMGRDLL_API TCPCommunicationManager : public BaseManager
{
public:
	TCPCommunicationManager(void);
	~TCPCommunicationManager(void);

public:
	// inherited from the BaseManager class
	virtual shared_ptr<NOM> registerMsg(std::wstring) override;
	virtual void discoverMsg(shared_ptr<NOM>) override;
	virtual void updateMsg(shared_ptr<NOM>) override;
	virtual void reflectMsg(shared_ptr<NOM>) override;
	virtual void deleteMsg(shared_ptr<NOM>) override;
	virtual void removeMsg(shared_ptr<NOM>) override;
	virtual void sendMsg(shared_ptr<NOM>) override;
	virtual void recvMsg(shared_ptr<NOM>) override;
	virtual void setUserName(std::wstring) override;
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
	
public:
	std::unique_ptr<NOMParser> nomParser;

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	map<unsigned int, shared_ptr<NOM>> registeredMsg;
	map<unsigned int, shared_ptr<NOM>> discoveredMsg;

	CommunicationInterface* commInterface;
	CommunicationConfig* commConfig;
	CommMessageHandler commMsgHandler;

	static inline Loggable l{ L"TCPCommunicationManager" };
};

