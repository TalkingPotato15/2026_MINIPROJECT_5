#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <nFramework/nTimer/NTimer.h>
#include <array>
#include <mutex>

using namespace nframework;
using namespace nom;
using namespace nlinestream;

class BASEMGRDLL_API MSSManager : public BaseManager
{
public:
	MSSManager(void);
	~MSSManager(void);

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
	void sendMSSStatus();
	void recvATSInformation(std::shared_ptr<NOM> nomMsg);
	void recvIgnitionCommand(std::shared_ptr<NOM> nomMsg);
	void recvMSSInterceptionResult(std::shared_ptr<NOM> nomMsg);
	void updateMissilePaths();
	void resetMissiles();
	void resetTargets();

	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;

	std::function<void(void*)> periodicFunc;
	NTimer* nTimer;
	int timerHandle;

	struct MissileState
	{
		unsigned int targetId = 0;
		unsigned int missileId = 0;
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		unsigned int status = 0;
	};

	struct TargetState
	{
		unsigned int targetId = 0;
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		double speed = 0.0;
		bool valid = false;
	};

	std::array<MissileState, 4> missileStates;
	std::array<TargetState, 4> targetStates;
	unsigned int simulatorStatus;
	unsigned int updateIntervalMs;
	double missileSpeedMultiplier;
	double targetSpeedMultiplier;
	double interceptDistance;
	std::mutex stateMutex;

	NLineTstream ntcout{ Level::COUT };
};
