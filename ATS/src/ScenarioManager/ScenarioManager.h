#pragma once

#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nLineStream/NLineStreamMain.h>
#include <nFramework/nom/NOMMain.h>

#include <functional>
#include <map>
#include <memory>

#include "Scenario.h"

using namespace nframework;
using namespace nlinestream;
using namespace nom;

class BASEMGRDLL_API ScenarioManager : public BaseManager
{
public:
    ScenarioManager();
    ~ScenarioManager() override;

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
    bool loadScenario(const std::shared_ptr<NOM>& nomMsg);
    void publishScenarioToManeuver();
    void publishControlMessage(const tstring& messageName);

    IMEBComponent* meb_{ nullptr };
    MECComponent* mec_{ nullptr };
    tstring name_;
    std::map<unsigned int, std::shared_ptr<NOM>> registeredMessages_;
    std::map<unsigned int, std::shared_ptr<NOM>> discoveredMessages_;
    std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> messageHandlers_;
    Scenario currentScenario_;
    bool hasValidScenario_{ false };

    NLineTstream ntcout{ Level::COUT };
};
