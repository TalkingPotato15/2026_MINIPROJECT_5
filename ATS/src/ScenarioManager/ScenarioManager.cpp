#include "ScenarioManager.h"

#include <sstream>
#include <utility>

namespace
{
tstring makeScenePath(std::size_t targetIndex, std::size_t pointIndex, const TCHAR* field)
{
    std::basic_ostringstream<TCHAR> path;
    path << _T("sceneInfo[") << targetIndex << _T("].ATSPos[")
         << pointIndex << _T("].") << field;
    return path.str();
}

tstring makeSpeedPath(std::size_t targetIndex)
{
    std::basic_ostringstream<TCHAR> path;
    path << _T("sceneInfo[") << targetIndex << _T("].speed");
    return path.str();
}
}

ScenarioManager::ScenarioManager()
{
    initialize();
}

ScenarioManager::~ScenarioManager()
{
    release();
}

void ScenarioManager::initialize()
{
    setUserName(_T("ScenarioManager"));
    mec_ = new MECComponent;
    mec_->setUser(this);
    initializeMessageHandlers();
}

void ScenarioManager::release()
{
    delete mec_;
    mec_ = nullptr;
    meb_ = nullptr;
    messageHandlers_.clear();
}

void ScenarioManager::initializeMessageHandlers()
{
    messageHandlers_.emplace(
        _T("InnerSendScenario"),
        std::bind(&ScenarioManager::receiveScenario, this, std::placeholders::_1));
    messageHandlers_.emplace(
        _T("InnerStartSimulation"),
        std::bind(&ScenarioManager::receiveStart, this, std::placeholders::_1));
    messageHandlers_.emplace(
        _T("InnerStopSimulation"),
        std::bind(&ScenarioManager::receiveStop, this, std::placeholders::_1));
}

std::shared_ptr<NOM> ScenarioManager::registerMsg(tstring msgName)
{
    auto nomMsg = mec_->registerMsg(msgName);
    registeredMessages_.emplace(nomMsg->getInstanceID(), nomMsg);
    return nomMsg;
}

void ScenarioManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
    discoveredMessages_.emplace(nomMsg->getInstanceID(), nomMsg);
}

void ScenarioManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
    mec_->updateMsg(nomMsg);
}

void ScenarioManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[ScenarioManager::reflectMsg] ") << nomMsg->getName() << std::endl;
}

void ScenarioManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
    mec_->deleteMsg(nomMsg);
    registeredMessages_.erase(nomMsg->getInstanceID());
}

void ScenarioManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
    discoveredMessages_.erase(nomMsg->getInstanceID());
}

void ScenarioManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
    mec_->sendMsg(nomMsg);
}

void ScenarioManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
    const auto handler = messageHandlers_.find(nomMsg->getName());
    if (handler != messageHandlers_.end())
    {
        handler->second(nomMsg);
    }
}

void ScenarioManager::setUserName(tstring userName)
{
    name_ = std::move(userName);
}

tstring ScenarioManager::getUserName()
{
    return name_;
}

void ScenarioManager::setData(void*)
{
}

bool ScenarioManager::start()
{
    ntcout << _T("[ScenarioManager] Started") << std::endl;
    return true;
}

bool ScenarioManager::stop()
{
    hasValidScenario_ = false;
    currentScenario_ = Scenario{};
    return true;
}

void ScenarioManager::setMEBComponent(IMEBComponent* realMEB)
{
    meb_ = realMEB;
    mec_->setMEB(meb_);
}

void ScenarioManager::receiveScenario(std::shared_ptr<NOM> nomMsg)
{
    if (!loadScenario(nomMsg))
    {
        ntcout << _T("[ScenarioManager] Scenario validation failed.") << std::endl;
        return;
    }

    publishScenarioToManeuver();
}

void ScenarioManager::receiveStart(std::shared_ptr<NOM>)
{
    if (!hasValidScenario_)
    {
        ntcout << _T("[ScenarioManager] Start ignored: no valid scenario.") << std::endl;
        return;
    }
    publishControlMessage(_T("InnerStartSimulationToModel"));
}

void ScenarioManager::receiveStop(std::shared_ptr<NOM>)
{
    publishControlMessage(_T("InnerStopSimulationToModel"));
}

bool ScenarioManager::loadScenario(const std::shared_ptr<NOM>& nomMsg)
{
    Scenario parsed;

    for (std::size_t targetIndex = 0; targetIndex < kATSMaxTargetCount; ++targetIndex)
    {
        auto& target = parsed.targets[targetIndex];
        if (const auto value = nomMsg->getValue(makeSpeedPath(targetIndex)))
        {
            target.speed = value->toUInt();
        }

        for (std::size_t pointIndex = 0; pointIndex < kATSRoutePointCount; ++pointIndex)
        {
            auto& point = target.route[pointIndex];
            if (const auto value = nomMsg->getValue(makeScenePath(targetIndex, pointIndex, _T("x"))))
            {
                point.x = value->toDouble();
            }
            if (const auto value = nomMsg->getValue(makeScenePath(targetIndex, pointIndex, _T("y"))))
            {
                point.y = value->toDouble();
            }
            if (const auto value = nomMsg->getValue(makeScenePath(targetIndex, pointIndex, _T("z"))))
            {
                point.z = value->toDouble();
            }
        }
    }

    hasValidScenario_ = parsed.validate();
    if (hasValidScenario_)
    {
        currentScenario_ = std::move(parsed);
    }
    return hasValidScenario_;
}

void ScenarioManager::publishScenarioToManeuver()
{
    auto scenarioMessage = meb_->getNOMInstance(name_, _T("InnerSendScenarioToModel"));
    if (!scenarioMessage)
    {
        ntcout << _T("[ScenarioManager] InnerSendScenarioToModel NOM is unavailable.") << std::endl;
        return;
    }

    for (std::size_t targetIndex = 0; targetIndex < kATSMaxTargetCount; ++targetIndex)
    {
        const auto& target = currentScenario_.targets[targetIndex];
        NUInteger speed(target.speed);
        scenarioMessage->setValue(makeSpeedPath(targetIndex), &speed);

        for (std::size_t pointIndex = 0; pointIndex < kATSRoutePointCount; ++pointIndex)
        {
            const auto& point = target.route[pointIndex];
            NDouble x(point.x);
            NDouble y(point.y);
            NDouble z(point.z);
            scenarioMessage->setValue(makeScenePath(targetIndex, pointIndex, _T("x")), &x);
            scenarioMessage->setValue(makeScenePath(targetIndex, pointIndex, _T("y")), &y);
            scenarioMessage->setValue(makeScenePath(targetIndex, pointIndex, _T("z")), &z);
        }
    }

    mec_->sendMsg(scenarioMessage);
}

void ScenarioManager::publishControlMessage(const tstring& messageName)
{
    if (auto controlMessage = meb_->getNOMInstance(name_, messageName))
    {
        mec_->sendMsg(controlMessage);
    }
}

extern "C" BASEMGRDLL_API BaseManager* createObject()
{
    return new ScenarioManager;
}

extern "C" BASEMGRDLL_API void deleteObject(BaseManager* userManager)
{
    delete userManager;
}
