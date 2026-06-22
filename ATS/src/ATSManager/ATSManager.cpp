#include "ATSManager.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

namespace
{
constexpr int kStatusPeriodMilliseconds = 1000;
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

ManeuverManager::ManeuverManager()
{
    initialize();
}

ManeuverManager::~ManeuverManager()
{
    release();
}

void ManeuverManager::initialize()
{
    setUserName(_T("ATSManager"));
    mec_ = new MECComponent;
    mec_->setUser(this);
    initializeMessageHandlers();
}

void ManeuverManager::release()
{
    removePeriodicTask();
    delete mec_;
    mec_ = nullptr;
    meb_ = nullptr;
    messageHandlers_.clear();
}

void ManeuverManager::initializeMessageHandlers()
{
    messageHandlers_.emplace(
        _T("InnerSendScenarioToModel"),
        std::bind(&ManeuverManager::receiveScenario, this, std::placeholders::_1));
    messageHandlers_.emplace(
        _T("InnerStartSimulationToModel"),
        std::bind(&ManeuverManager::receiveStart, this, std::placeholders::_1));
    messageHandlers_.emplace(
        _T("InnerStopSimulationToModel"),
        std::bind(&ManeuverManager::receiveStop, this, std::placeholders::_1));
    messageHandlers_.emplace(
        _T("InnerAirThreatDetonationToATM"),
        std::bind(&ManeuverManager::receiveInterception, this, std::placeholders::_1));
}

std::shared_ptr<NOM> ManeuverManager::registerMsg(tstring msgName)
{
    auto nomMsg = mec_->registerMsg(msgName);
    registeredMessages_.emplace(nomMsg->getInstanceID(), nomMsg);
    return nomMsg;
}

void ManeuverManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
    discoveredMessages_.emplace(nomMsg->getInstanceID(), nomMsg);
}

void ManeuverManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
    mec_->updateMsg(nomMsg);
}

void ManeuverManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
    ntcout << _T("[ManeuverManager::reflectMsg] ") << nomMsg->getName() << std::endl;
}

void ManeuverManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
    mec_->deleteMsg(nomMsg);
    registeredMessages_.erase(nomMsg->getInstanceID());
}

void ManeuverManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
    discoveredMessages_.erase(nomMsg->getInstanceID());
}

void ManeuverManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
    mec_->sendMsg(nomMsg);
}

void ManeuverManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
    const auto handler = messageHandlers_.find(nomMsg->getName());
    if (handler != messageHandlers_.end())
    {
        handler->second(nomMsg);
    }
}

void ManeuverManager::setUserName(tstring userName)
{
    name_ = std::move(userName);
}

tstring ManeuverManager::getUserName()
{
    return name_;
}

void ManeuverManager::setData(void*)
{
}

bool ManeuverManager::start()
{
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        operationalStatus_ = ATSOperationalStatus::Ready;
    }

    timer_ = &NTimer::getInstance();
    periodicCallback_ = [this](void*) { periodicUpdate(); };
    timerHandle_ = timer_->addPeriodicTask(kStatusPeriodMilliseconds, periodicCallback_);

    ntcout << _T("[ManeuverManager] READY, ATSStatus period = 1000 ms") << std::endl;
    publishATSStatus();
    return timerHandle_ != -1;
}

bool ManeuverManager::stop()
{
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        operationalStatus_ = ATSOperationalStatus::Idle;
        airThreat_.stop();
    }

    publishATSStatus();
    removePeriodicTask();
    return true;
}

void ManeuverManager::setMEBComponent(IMEBComponent* realMEB)
{
    meb_ = realMEB;
    mec_->setMEB(meb_);
}

void ManeuverManager::receiveScenario(std::shared_ptr<NOM> nomMsg)
{
    std::uint32_t targetId = 0;
    std::uint32_t speed = 0;
    std::uint32_t pointCount = 0;

    if (const auto value = nomMsg->getValue(_T("Scenario.TargetID")))
    {
        targetId = value->toUInt();
    }
    if (const auto value = nomMsg->getValue(_T("Scenario.Speed")))
    {
        speed = value->toUInt();
    }
    if (const auto value = nomMsg->getValue(_T("Scenario.PointCount")))
    {
        pointCount = value->toUInt();
    }

    pointCount = std::min<std::uint32_t>(pointCount, static_cast<std::uint32_t>(kMaximumWayPointCount));
    std::vector<Position> route;
    route.reserve(pointCount);

    for (std::size_t index = 0; index < pointCount; ++index)
    {
        Position point;
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
        route.push_back(point);
    }

    const bool initialized = [&]()
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        operationalStatus_ = ATSOperationalStatus::Ready;
        return airThreat_.initialize(targetId, static_cast<double>(speed), route);
    }();

    if (!initialized)
    {
        ntcout << _T("[ManeuverManager] Invalid scenario: at least 2 points and speed > 0 are required.") << std::endl;
        return;
    }

    ntcout << _T("[ManeuverManager] Air threat initialized. targetID=")
           << targetId << _T(", points=") << pointCount << std::endl;
    publishATSStatus();
}

void ManeuverManager::receiveStart(std::shared_ptr<NOM>)
{
    bool started = false;
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        if (airThreat_.isInitialized())
        {
            airThreat_.start();
            operationalStatus_ = ATSOperationalStatus::Running;
            started = true;
        }
    }

    if (!started)
    {
        ntcout << _T("[ManeuverManager] Start ignored because no valid scenario is loaded.") << std::endl;
        return;
    }

    publishATSStatus();
}

void ManeuverManager::receiveStop(std::shared_ptr<NOM>)
{
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        airThreat_.stop();
        operationalStatus_ = ATSOperationalStatus::Ready;
    }
    publishATSStatus();
}

void ManeuverManager::receiveInterception(std::shared_ptr<NOM>)
{
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        airThreat_.markIntercepted();
    }
    publishATSStatus();
}

void ManeuverManager::periodicUpdate()
{
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        if (operationalStatus_ == ATSOperationalStatus::Running)
        {
            airThreat_.advance(1.0);
        }
    }
    publishATSStatus();
}

void ManeuverManager::publishATSStatus()
{
    if (meb_ == nullptr)
    {
        return;
    }

    auto statusMessage = meb_->getNOMInstance(name_, _T("InnerAirThreatInfoToComm"));
    if (!statusMessage)
    {
        ntcout << _T("[ManeuverManager] InnerAirThreatInfoToComm NOM is unavailable.") << std::endl;
        return;
    }

    ATSOperationalStatus status;
    bool hasTarget;
    std::uint32_t targetId;
    double speed;
    Position position;
    Position velocity;
    bool intercepted;

    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        status = operationalStatus_;
        hasTarget = airThreat_.isInitialized();
        targetId = hasTarget ? airThreat_.targetId() : 0;
        speed = hasTarget ? airThreat_.speed() : 0.0;
        position = hasTarget ? airThreat_.position() : Position{};
        velocity = hasTarget ? airThreat_.velocity() : Position{};
        intercepted = hasTarget && airThreat_.isIntercepted();
    }

    NInteger systemStatus(static_cast<int>(status));
    NUInteger targetCount(hasTarget ? 1U : 0U);
    NUInteger objectId(targetId);
    NUShort objectState(intercepted ? 1U : 0U);
    NDouble positionX(position.x);
    NDouble positionY(position.y);
    NDouble positionZ(position.z);
    NDouble velocityX(velocity.x);
    NDouble velocityY(velocity.y);
    NUInteger targetSpeed(static_cast<std::uint32_t>(speed));
    NBool interceptionFlag(intercepted);

    statusMessage->setValue(_T("AirThreatInfo.SystemStatus"), &systemStatus);
    statusMessage->setValue(_T("AirThreatInfo.TargetCount"), &targetCount);
    statusMessage->setValue(_T("AirThreatInfo.ObjectID"), &objectId);
    statusMessage->setValue(_T("AirThreatInfo.ObjectState"), &objectState);
    statusMessage->setValue(_T("AirThreatInfo.PositionX"), &positionX);
    statusMessage->setValue(_T("AirThreatInfo.PositionY"), &positionY);
    statusMessage->setValue(_T("AirThreatInfo.PositionZ"), &positionZ);
    statusMessage->setValue(_T("AirThreatInfo.VelocityX"), &velocityX);
    statusMessage->setValue(_T("AirThreatInfo.VelocityY"), &velocityY);
    statusMessage->setValue(_T("AirThreatInfo.Speed"), &targetSpeed);
    statusMessage->setValue(_T("AirThreatInfo.InterceptionFlag"), &interceptionFlag);
    mec_->sendMsg(statusMessage);
}

void ManeuverManager::removePeriodicTask()
{
    if (timer_ != nullptr && timerHandle_ != -1)
    {
        timer_->removeTask(timerHandle_);
        timerHandle_ = -1;
    }
}

extern "C" BASEMGRDLL_API BaseManager* createObject()
{
    return new ManeuverManager;
}

extern "C" BASEMGRDLL_API void deleteObject(BaseManager* userManager)
{
    delete userManager;
}
