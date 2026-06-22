#include "ManeuverManager.h"

#include <array>
#include <sstream>
#include <utility>

namespace
{
constexpr int kStatusPeriodMilliseconds = 1000;
constexpr std::uint32_t kMissionSuccess = 0;

tstring makeScenePath(std::size_t targetIndex, std::size_t pointIndex, const TCHAR* field)
{
    std::basic_ostringstream<TCHAR> path;
    path << _T("sceneInfo[") << targetIndex << _T("].ATSPos[")
         << pointIndex << _T("].") << field;
    return path.str();
}

tstring makeSceneSpeedPath(std::size_t targetIndex)
{
    std::basic_ostringstream<TCHAR> path;
    path << _T("sceneInfo[") << targetIndex << _T("].speed");
    return path.str();
}

tstring makeTargetPath(std::size_t targetIndex, const TCHAR* field)
{
    std::basic_ostringstream<TCHAR> path;
    path << _T("targetInfo[") << targetIndex << _T("].") << field;
    return path.str();
}
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
    setUserName(_T("ManeuverManager"));
    mec_ = new MECComponent;
    mec_->setUser(this);
    initializeMessageHandlers();

    for (std::size_t index = 0; index < airThreats_.size(); ++index)
    {
        airThreats_[index].reset(static_cast<std::uint32_t>(index));
    }
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

    publishATSStatus();
    return timerHandle_ != -1;
}

bool ManeuverManager::stop()
{
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        operationalStatus_ = ATSOperationalStatus::Idle;
        for (auto& airThreat : airThreats_)
        {
            airThreat.stop();
        }
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
    std::array<std::array<Position, kAirThreatRoutePointCount>, kATSMaxAirThreatCount> routes{};
    std::array<std::uint32_t, kATSMaxAirThreatCount> speeds{};

    for (std::size_t targetIndex = 0; targetIndex < kATSMaxAirThreatCount; ++targetIndex)
    {
        if (const auto value = nomMsg->getValue(makeSceneSpeedPath(targetIndex)))
        {
            speeds[targetIndex] = value->toUInt();
        }

        for (std::size_t pointIndex = 0; pointIndex < kAirThreatRoutePointCount; ++pointIndex)
        {
            auto& point = routes[targetIndex][pointIndex];
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

    bool hasConfiguredTarget = false;
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        for (std::size_t targetIndex = 0; targetIndex < airThreats_.size(); ++targetIndex)
        {
            if (speeds[targetIndex] > 0)
            {
                hasConfiguredTarget = airThreats_[targetIndex].initialize(
                    static_cast<std::uint32_t>(targetIndex),
                    speeds[targetIndex],
                    routes[targetIndex]) || hasConfiguredTarget;
            }
            else
            {
                airThreats_[targetIndex].reset(static_cast<std::uint32_t>(targetIndex));
            }
        }
        hasValidScenario_ = hasConfiguredTarget;
        operationalStatus_ = ATSOperationalStatus::Ready;
    }

    publishATSStatus();
}

void ManeuverManager::receiveStart(std::shared_ptr<NOM>)
{
    bool started = false;
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        if (hasValidScenario_)
        {
            for (auto& airThreat : airThreats_)
            {
                airThreat.start();
                started = airThreat.isFlying() || started;
            }
        }
        if (started)
        {
            operationalStatus_ = ATSOperationalStatus::Running;
        }
    }

    if (!started)
    {
        ntcout << _T("[ManeuverManager] Start ignored: no configured air threat.") << std::endl;
        return;
    }
    publishATSStatus();
}

void ManeuverManager::receiveStop(std::shared_ptr<NOM>)
{
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        for (auto& airThreat : airThreats_)
        {
            airThreat.stop();
        }
        operationalStatus_ = ATSOperationalStatus::Ready;
    }
    publishATSStatus();
}

void ManeuverManager::receiveInterception(std::shared_ptr<NOM> nomMsg)
{
    const auto targetValue = nomMsg->getValue(_T("targetID"));
    const auto missionValue = nomMsg->getValue(_T("missionFlag"));
    if (!targetValue || !missionValue)
    {
        return;
    }

    const std::uint32_t targetId = targetValue->toUInt();
    const std::uint32_t missionFlag = missionValue->toUInt();
    if (missionFlag != kMissionSuccess || targetId >= airThreats_.size())
    {
        return;
    }

    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        airThreats_[targetId].destroy();
    }
    publishATSStatus();
}

void ManeuverManager::periodicUpdate()
{
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        if (operationalStatus_ == ATSOperationalStatus::Running)
        {
            for (auto& airThreat : airThreats_)
            {
                airThreat.advance(1.0);
            }
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

    ATSOperationalStatus systemStatus;
    std::array<std::uint32_t, kATSMaxAirThreatCount> ids{};
    std::array<std::uint32_t, kATSMaxAirThreatCount> speeds{};
    std::array<std::uint32_t, kATSMaxAirThreatCount> statuses{};
    std::array<Position, kATSMaxAirThreatCount> positions{};

    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        systemStatus = operationalStatus_;
        for (std::size_t index = 0; index < airThreats_.size(); ++index)
        {
            ids[index] = airThreats_[index].targetId();
            speeds[index] = airThreats_[index].speed();
            statuses[index] = static_cast<std::uint32_t>(airThreats_[index].status());
            positions[index] = airThreats_[index].position();
        }
    }

    NUInteger status(static_cast<std::uint32_t>(systemStatus));
    statusMessage->setValue(_T("status"), &status);

    for (std::size_t index = 0; index < kATSMaxAirThreatCount; ++index)
    {
        NDouble x(positions[index].x);
        NDouble y(positions[index].y);
        NDouble z(positions[index].z);
        NUInteger speed(speeds[index]);
        NUInteger targetId(ids[index]);
        NUInteger atsStatus(statuses[index]);

        statusMessage->setValue(makeTargetPath(index, _T("ATSPos.x")), &x);
        statusMessage->setValue(makeTargetPath(index, _T("ATSPos.y")), &y);
        statusMessage->setValue(makeTargetPath(index, _T("ATSPos.z")), &z);
        statusMessage->setValue(makeTargetPath(index, _T("speed")), &speed);
        statusMessage->setValue(makeTargetPath(index, _T("targetId")), &targetId);
        statusMessage->setValue(makeTargetPath(index, _T("atsStatus")), &atsStatus);
    }
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
