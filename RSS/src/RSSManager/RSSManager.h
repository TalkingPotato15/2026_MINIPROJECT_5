#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <nFramework/nTimer/NTimer.h>
#include <map>
#include <set>

using namespace nframework;
using namespace nom;
using namespace nlinestream;

class BASEMGRDLL_API RSSManager : public BaseManager
{
	struct CachedATSInfo
	{
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		uint32_t speed = 0;
		uint32_t targetId = 0;
		uint32_t atsStatus = 0;
	};

	struct CachedMSSInfo
	{
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		uint32_t targetId = 0;
		uint32_t missileId = 0;
	};

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
	void recvInnerRSSDetectionAreaToRSS(std::shared_ptr<NOM> nomMsg);
	void recvInnerATSInformationToRSS(std::shared_ptr<NOM> nomMsg);
	void recvInnerMSSInformationToRSS(std::shared_ptr<NOM> nomMsg);
	bool tryReadATSInfo(std::shared_ptr<NOM> nomMsg, const tstring& targetPrefix, CachedATSInfo& atsInfo) const;
	bool tryReadMSSInfo(std::shared_ptr<NOM> nomMsg, const tstring& missilePrefix, CachedMSSInfo& mssInfo) const;
	double getDistanceToRSS(const CachedATSInfo& atsInfo) const;
	double getDistance(const CachedATSInfo& atsInfo, const CachedMSSInfo& mssInfo) const;
	bool isInRSSRange(const CachedATSInfo& atsInfo) const;
	bool isIntercepted(const CachedATSInfo& atsInfo, const CachedMSSInfo& mssInfo) const;
	void sendTargetDetection(uint32_t targetID, uint32_t success);
	void sendTargetDestroyed(uint32_t targetID, uint32_t missionFlag);
	void sendATSInformationUplink(const CachedATSInfo& atsInfo);

	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> funcMap;
	std::set<uint32_t> detectedTargetIds;
	std::map<uint32_t, CachedATSInfo> detectedTargetInfoMap;
	std::set<uint32_t> destroyedTargetIds;

	bool hasRSSDetectionArea = false;
	double rssPosX = 0.0;
	double rssPosY = 0.0;
	double rssPosZ = 0.0;
	double rssRadius = 0.0;

	std::function<void(void*)> periodicFunc;
	NTimer* nTimer;
	int timerHandle;

	std::shared_ptr<NOM> rssStatusNOM;

	NLineTstream ntcout{ Level::COUT };
};
