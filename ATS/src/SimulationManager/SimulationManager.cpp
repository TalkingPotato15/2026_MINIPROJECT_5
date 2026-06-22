#include "SimulationManager.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <utility>

namespace
{
constexpr std::size_t kMaximumWayPointCount = 8;

const std::array<const TCHAR*, kMaximumWayPointCount> kWayPointXFields{
    _T("Scenario.WayPoint0_X"), _T("Scenario.WayPoint1_X"),
    _T("Scenario.WayPoint2_X"), _T("Scenario.WayPoint3_X"),
    _T("Scenario.WayPoint4_X"), _T("Scenario.WayPoint5_X"),
    _T("Scenario.WayPoint6_X"), _T("Scenario.WayPoint7_X")
};

const std::array<const TCHAR*, kMaximumWayPointCount> kWayPointYFields{
    _T("Scenario.WayPoint0_Y"), _T("Scenario.WayPoint1_Y"),
    _T("Scenario.WayPoint2_Y"), _T("Scenario.WayPoint3_Y"),
    _T("Scenario.WayPoint4_Y"), _T("Scenario.WayPoint5_Y"),
    _T("Scenario.WayPoint6_Y"), _T("Scenario.WayPoint7_Y")
};

const std::array<const TCHAR*, kMaximumWayPointCount> kWayPointZFields{
    _T("Scenario.WayPoint0_Z"), _T("Scenario.WayPoint1_Z"),
    _T("Scenario.WayPoint2_Z"), _T("Scenario.WayPoint3_Z"),
    _T("Scenario.WayPoint4_Z"), _T("Scenario.WayPoint5_Z"),
    _T("Scenario.WayPoint6_Z"), _T("Scenario.WayPoint7_Z")
};
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
    setUserName(_T("SimulationManager"));
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
    publishAck(_T("InnerSendScenarioAck"));
}

void ScenarioManager::receiveStart(std::shared_ptr<NOM>)
{
    if (!hasValidScenario_)
    {
        ntcout << _T("[ScenarioManager] Start ignored because no valid scenario is loaded.") << std::endl;
        return;
    }

    publishControlMessage(_T("InnerStartSimulationToModel"));
    publishAck(_T("InnerStartSimulationAck"));
}

void ScenarioManager::receiveStop(std::shared_ptr<NOM>)
{
    publishControlMessage(_T("InnerStopSimulationToModel"));
    publishAck(_T("InnerStopSimulationAck"));
}

bool ScenarioManager::loadScenario(const std::shared_ptr<NOM>& nomMsg)
{
    Scenario parsed;
    std::uint32_t pointCount = 0;

    if (const auto value = nomMsg->getValue(_T("Scenario.TargetID")))
    {
        parsed.targetId = value->toUInt();
    }
    if (const auto value = nomMsg->getValue(_T("Scenario.Speed")))
    {
        parsed.speed = value->toUInt();
    }
    if (const auto value = nomMsg->getValue(_T("Scenario.PointCount")))
    {
        pointCount = value->toUInt();
    }

    pointCount = std::min<std::uint32_t>(pointCount, static_cast<std::uint32_t>(kMaximumWayPointCount));
    parsed.route.reserve(pointCount);

    for (std::size_t index = 0; index < pointCount; ++index)
    {
        ScenarioPosition point;
        if (const auto value = nomMsg->getValue(kWayPointXFields[index]))
        {
            point.x = value->toDouble();
        }
        if (const auto value = nomMsg->getValue(kWayPointYFields[index]))
        {
            point.y = value->toDouble();
        }
        if (const auto value = nomMsg->getValue(kWayPointZFields[index]))
        {
            point.z = value->toDouble();
        }
        parsed.route.push_back(point);
    }

    if (const auto value = nomMsg->getValue(_T("Scenario.RadarPositionX")))
    {
        parsed.radarPosition.x = value->toDouble();
    }
    if (const auto value = nomMsg->getValue(_T("Scenario.RadarPositionY")))
    {
        parsed.radarPosition.y = value->toDouble();
    }
    if (const auto value = nomMsg->getValue(_T("Scenario.RadarRadius")))
    {
        parsed.radarRadius = value->toDouble();
    }
    if (const auto value = nomMsg->getValue(_T("Scenario.LauncherPositionX")))
    {
        parsed.launcherPosition.x = value->toDouble();
    }
    if (const auto value = nomMsg->getValue(_T("Scenario.LauncherPositionY")))
    {
        parsed.launcherPosition.y = value->toDouble();
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

    NUInteger targetId(currentScenario_.targetId);
    NUInteger speed(currentScenario_.speed);
    NUInteger pointCount(static_cast<std::uint32_t>(currentScenario_.route.size()));
    scenarioMessage->setValue(_T("Scenario.TargetID"), &targetId);
    scenarioMessage->setValue(_T("Scenario.Speed"), &speed);
    scenarioMessage->setValue(_T("Scenario.PointCount"), &pointCount);

    for (std::size_t index = 0; index < kMaximumWayPointCount; ++index)
    {
        const ScenarioPosition point = index < currentScenario_.route.size()
            ? currentScenario_.route[index]
            : ScenarioPosition{};
        NDouble x(point.x);
        NDouble y(point.y);
        NDouble z(point.z);
        scenarioMessage->setValue(kWayPointXFields[index], &x);
        scenarioMessage->setValue(kWayPointYFields[index], &y);
        scenarioMessage->setValue(kWayPointZFields[index], &z);
    }

    NDouble radarX(currentScenario_.radarPosition.x);
    NDouble radarY(currentScenario_.radarPosition.y);
    NDouble radarRadius(currentScenario_.radarRadius);
    NDouble launcherX(currentScenario_.launcherPosition.x);
    NDouble launcherY(currentScenario_.launcherPosition.y);
    scenarioMessage->setValue(_T("Scenario.RadarPositionX"), &radarX);
    scenarioMessage->setValue(_T("Scenario.RadarPositionY"), &radarY);
    scenarioMessage->setValue(_T("Scenario.RadarRadius"), &radarRadius);
    scenarioMessage->setValue(_T("Scenario.LauncherPositionX"), &launcherX);
    scenarioMessage->setValue(_T("Scenario.LauncherPositionY"), &launcherY);
    mec_->sendMsg(scenarioMessage);
}

void ScenarioManager::publishControlMessage(const tstring& messageName)
{
    if (auto controlMessage = meb_->getNOMInstance(name_, messageName))
    {
        mec_->sendMsg(controlMessage);
    }
}

void ScenarioManager::publishAck(const tstring& messageName)
{
    auto ackMessage = meb_->getNOMInstance(name_, messageName);
    if (!ackMessage)
    {
        return;
    }

    NUShort simulatorId(static_cast<ushort>(SimulatorID::ATS));
    ackMessage->setValue(_T("SimulatorID"), &simulatorId);
    mec_->sendMsg(ackMessage);
}

extern "C" BASEMGRDLL_API BaseManager* createObject()
{
    return new ScenarioManager;
}

extern "C" BASEMGRDLL_API void deleteObject(BaseManager* userManager)
{
    delete userManager;
}
