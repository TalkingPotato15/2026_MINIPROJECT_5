#pragma once

#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <nFramework/nTimer/NTimer.h>

#include <functional>
#include <map>
#include <memory>
#include <mutex>

#include "AirThreat.h"

using namespace nframework;
using namespace nom;
using namespace nlinestream;

enum class ATSOperationalStatus : int
{
    Idle = 0,
    Ready = 1,
    Running = 2
};

class BASEMGRDLL_API ManeuverManager : public BaseManager
{
public:
    ManeuverManager();
    ~ManeuverManager() override;

    std::shared_ptr<NOM> registerMsg(tstring msgName) override;
    void discoverMsg(std::shared_ptr<NOM> nomMsg) override;
    void updateMsg(std::shared_ptr<NOM> nomMsg) override;
    void reflectMsg(std::shared_ptr<NOM> nomMsg) override;
    void deleteMsg(std::shared_ptr<NOM> nomMsg) override;
    void removeMsg(std::shared_ptr<NOM> nomMsg) override;
    void sendMsg(std::shared_ptr<NOM> nomMsg) override;
    void recvMsg(std::shared_ptr<NOM> nomMsg) override;
    void setUserName(tstring userName) override;
    tstring getUserName() override;
    void setData(void* data) override;
    bool start() override;
    bool stop() override;
    void setMEBComponent(IMEBComponent* realMEB) override;

private:
    void initialize();
    void release();
    void initializeMessageHandlers();
    void receiveScenario(std::shared_ptr<NOM> nomMsg);
    void receiveStart(std::shared_ptr<NOM> nomMsg);
    void receiveStop(std::shared_ptr<NOM> nomMsg);
    void receiveInterception(std::shared_ptr<NOM> nomMsg);
    void periodicUpdate();
    void publishATSStatus();
    void removePeriodicTask();

    IMEBComponent* meb_{ nullptr };
    MECComponent* mec_{ nullptr };
    tstring name_;
    std::map<unsigned int, std::shared_ptr<NOM>> registeredMessages_;
    std::map<unsigned int, std::shared_ptr<NOM>> discoveredMessages_;
    std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> messageHandlers_;

    AirThreat airThreat_;
    ATSOperationalStatus operationalStatus_{ ATSOperationalStatus::Idle };
    NTimer* timer_{ nullptr };
    int timerHandle_{ -1 };
    std::function<void(void*)> periodicCallback_;
    std::mutex stateMutex_;

    NLineTstream ntcout{ Level::COUT };
};
