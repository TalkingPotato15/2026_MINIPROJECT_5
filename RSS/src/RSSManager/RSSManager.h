#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <nFramework/nTimer/NTimer.h>
#include <set>

using namespace nframework;
using namespace nom;
using namespace nlinestream;

class BASEMGRDLL_API RSSManager : public BaseManager
{
public:
	RSSManager(void);
	~RSSManager(void);

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
	void sendRSSStatus();
	void recvInnerATSInformationToRSS(std::shared_ptr<NOM> nomMsg);
	void recvInnerMSSInformationToRSS(std::shared_ptr<NOM> nomMsg);
	void sendTargetDetection(uint32_t targetID, uint32_t success);
	void sendTargetDestroyed(uint32_t targetID, uint32_t missionFlag);

	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> funcMap;
	std::set<uint32_t> detectedTargetIds;
	std::set<uint32_t> destroyedTargetIds;

	std::function<void(void*)> periodicFunc;
	NTimer* nTimer;
	int timerHandle;

	std::shared_ptr<NOM> rssStatusNOM;

	NLineTstream ntcout{ Level::COUT };
};
