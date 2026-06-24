#include <nFramework/util/IniHandler.h>
#include "MSSManager.h"
#include <cmath>

MSSManager::MSSManager(void)
{
	initialize();
}

MSSManager::~MSSManager(void)
{
	release();
}

void MSSManager::initialize(void)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;

	setUserName(_T("MSSManager"));

	mec = new MECComponent;
	mec->setUser(this);

	periodicFunc = [this](void*)
	{
		this->updateMissilePaths();
		this->sendMSSStatus();
	};
	nTimer = &(NTimer::getInstance());
	timerHandle = -1;
	simulatorStatus = 0;
	updateIntervalMs = 1000;
	missileSpeedMultiplier = 1.8;
	targetSpeedMultiplier = 0.03; //ATS = 0.05 화면이 작은데 속도가 너무 빨라 ATS측에서 multiply함.
	interceptDistance = 50.0;
	resetMissiles();
	resetTargets();
}

void MSSManager::release()
{
	if (nTimer != nullptr && timerHandle != -1)
	{
		nTimer->removeTask(timerHandle);
		timerHandle = -1;
	}

	delete mec;
	mec = nullptr;
	meb = nullptr;
}

void MSSManager::resetMissiles()
{
	for (unsigned int i = 0; i < missileStates.size(); ++i)
	{
		missileStates[i] = MissileState();
		missileStates[i].missileId = i;
	}
}

void MSSManager::resetTargets()
{
	for (auto& target : targetStates)
	{
		target = TargetState();
	}
}

void MSSManager::sendMSSStatus()
{
	auto statusNOM = meb->getNOMInstance(name, _T("InnerMSSStatusToComm"));
	if (!statusNOM.get())
	{
		ntcout << _T("[MSSManager] InnerMSSStatusToComm NOM is undefined.") << std::endl;
		return;
	}

	std::array<MissileState, 4> missileSnapshot;
	unsigned int statusSnapshot = 0;
	{
		std::lock_guard<std::mutex> lock(stateMutex);
		missileSnapshot = missileStates;
		statusSnapshot = simulatorStatus;
	}

	NUInteger status(statusSnapshot);
	statusNOM->setValue(_T("status"), &status);

	for (unsigned int i = 0; i < missileSnapshot.size(); ++i)
	{
		const tstring prefix = _T("missileInfo[") + std::to_wstring(i) + _T("].");
		NUInteger targetId(missileSnapshot[i].targetId);
		NUInteger missileId(missileSnapshot[i].missileId);
		NDouble x(missileSnapshot[i].x);
		NDouble y(missileSnapshot[i].y);
		NDouble z(missileSnapshot[i].z);
		NUInteger missileStatus(missileSnapshot[i].status);

		statusNOM->setValue(prefix + _T("targetId"), &targetId);
		statusNOM->setValue(prefix + _T("missileId"), &missileId);
		statusNOM->setValue(prefix + _T("MSSPos.x"), &x);
		statusNOM->setValue(prefix + _T("MSSPos.y"), &y);
		statusNOM->setValue(prefix + _T("MSSPos.z"), &z);
		statusNOM->setValue(prefix + _T("mssStatus"), &missileStatus);
	}

	sendMsg(statusNOM);
}

void MSSManager::recvATSInformation(std::shared_ptr<NOM> nomMsg)
{
	auto targetValue = nomMsg->getValue(_T("matchedTarget.targetId"));
	auto xValue = nomMsg->getValue(_T("matchedTarget.ATSPos.x"));
	auto yValue = nomMsg->getValue(_T("matchedTarget.ATSPos.y"));
	auto zValue = nomMsg->getValue(_T("matchedTarget.ATSPos.z"));
	auto speedValue = nomMsg->getValue(_T("matchedTarget.speed"));
	if (!targetValue || !xValue || !yValue || !zValue)
	{
		return;
	}

	const unsigned int targetId = targetValue->toUInt();
	const double targetX = xValue->toDouble();
	const double targetY = yValue->toDouble();
	const double targetZ = zValue->toDouble();
	const double targetSpeed = speedValue ? speedValue->toDouble() : 0.0;
	std::lock_guard<std::mutex> lock(stateMutex);

	TargetState* target = nullptr;
	for (auto& candidate : targetStates)
	{
		if (candidate.valid && candidate.targetId == targetId)
		{
			target = &candidate;
			break;
		}
	}
	if (target == nullptr)
	{
		for (auto& candidate : targetStates)
		{
			if (!candidate.valid)
			{
				target = &candidate;
				break;
			}
		}
	}
	if (target == nullptr)
	{
		target = &targetStates[targetId % targetStates.size()];
	}

	target->targetId = targetId;
	target->x = targetX;
	target->y = targetY;
	target->z = targetZ;
	target->speed = targetSpeed;
	target->valid = true;

	ntcout << _T("[MSS][RX] targetID=") << targetId
		<< _T(" pos=(") << targetX << _T(",") << targetY
		<< _T(",") << targetZ << _T(") speed=") << targetSpeed << std::endl;
}

void MSSManager::recvIgnitionCommand(std::shared_ptr<NOM> nomMsg)
{
	auto missileIdValue = nomMsg->getValue(_T("missileID"));
	auto targetIdValue = nomMsg->getValue(_T("targetID"));
	if (!missileIdValue || !targetIdValue)
	{
		ntcout << _T("[MSS][IGNITION][ERROR] missileID or targetID is missing") << std::endl;
		return;
	}

	const unsigned int missileId = missileIdValue->toUInt();
	const unsigned int targetId = targetIdValue->toUInt();
	if (missileId >= missileStates.size())
	{
		ntcout << _T("[MSS][IGNITION][ERROR] missileID must be 0..3: ")
			<< missileId << std::endl;
		return;
	}

	std::lock_guard<std::mutex> lock(stateMutex);
	auto& missile = missileStates[missileId];
	missile.missileId = missileId;
	missile.targetId = targetId;

	if (auto value = nomMsg->getValue(_T("launchPos.x"))) missile.x = value->toDouble();
	if (auto value = nomMsg->getValue(_T("launchPos.y"))) missile.y = value->toDouble();
	if (auto value = nomMsg->getValue(_T("launchPos.z"))) missile.z = value->toDouble();

	missile.status = 1; // LAUNCHED
	simulatorStatus = 2; // RUNNING

	ntcout << _T("[MSS][IGNITION] missileID=") << missileId
		<< _T(" targetID=") << targetId
		<< _T(" launchPos=(") << missile.x << _T(",") << missile.y
		<< _T(",") << missile.z << _T(")") << std::endl;
}

void MSSManager::recvMSSInterceptionResult(std::shared_ptr<NOM> nomMsg)
{
	auto targetIdValue = nomMsg->getValue(_T("targetID"));
	if (!targetIdValue || targetIdValue->toUInt() == 0)
	{
		ntcout << _T("[MSS][INTERCEPTION RESULT][ERROR] targetID is missing or zero") << std::endl;
		return;
	}

	const unsigned int targetId = targetIdValue->toUInt();
	auto missionFlagValue = nomMsg->getValue(_T("missionFlag"));
	const unsigned int missionFlag = missionFlagValue ? missionFlagValue->toUInt() : 0;
	std::lock_guard<std::mutex> lock(stateMutex);
	bool removed = false;

	for (unsigned int i = 0; i < missileStates.size(); ++i)
	{
		auto& missile = missileStates[i];
		if (missile.targetId != targetId)
		{
			continue;
		}

		const unsigned int missileId = missile.missileId;
		missile = MissileState();
		missile.missileId = i;
		removed = true;
		ntcout << _T("[MSS][INTERCEPTION RESULT] removed missileID=") << missileId
			<< _T(" targetID=") << targetId
			<< _T(" missionFlag=") << missionFlag << std::endl;
	}

	if (!removed)
	{
		ntcout << _T("[MSS][INTERCEPTION RESULT][WARN] no missile for targetID=")
			<< targetId << std::endl;
	}
}
void MSSManager::updateMissilePaths()
{
	std::lock_guard<std::mutex> lock(stateMutex);
	const double deltaTime = static_cast<double>(updateIntervalMs) / 1000.0;

	for (auto& missile : missileStates)
	{
		if (missile.status != 1)
		{
			continue;
		}

		const TargetState* target = nullptr;
		for (const auto& candidate : targetStates)
		{
			if (candidate.valid && candidate.targetId == missile.targetId)
			{
				target = &candidate;
				break;
			}
		}
		if (target == nullptr)
		{
			continue;
		}
		const double moveDistance = target->speed * targetSpeedMultiplier * missileSpeedMultiplier * deltaTime;
		if (moveDistance <= 0.0)
		{
			continue;
		}

		const double dx = target->x - missile.x;
		const double dy = target->y - missile.y;
		const double dz = target->z - missile.z;
		const double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
		if (distance <= interceptDistance || distance <= moveDistance)
		{
			missile.x = target->x;
			missile.y = target->y;
			missile.z = target->z;
			missile.status = 2; // DESTROYED
			continue;
		}

		const double ratio = moveDistance / distance;
		missile.x += dx * ratio;
		missile.y += dy * ratio;
		missile.z += dz * ratio;
	}
}

std::shared_ptr<NOM> MSSManager::registerMsg(tstring msgName)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << msgName << std::endl;

	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
	return nomMsg;
}

void MSSManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void MSSManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->updateMsg(nomMsg);
}

void MSSManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
}

void MSSManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void MSSManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void MSSManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->sendMsg(nomMsg);
}

void MSSManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	if (nomMsg->getName() == _T("InnerATSInformationToMSS"))
	{
		recvATSInformation(nomMsg);
	}
	else if (nomMsg->getName() == _T("InnerIgnitionCommandToMSS"))
	{
		recvIgnitionCommand(nomMsg);
	}
	else if (nomMsg->getName() == _T("InnerMSSInterceptionResultToMSS"))
	{
		recvMSSInterceptionResult(nomMsg);
	}
	else if (nomMsg->getName() == _T("InnerStartSimulationToModel"))
	{
		std::lock_guard<std::mutex> lock(stateMutex);
		simulatorStatus = 1; // READY
	}
	else if (nomMsg->getName() == _T("InnerStopSimulationToModel"))
	{
		std::lock_guard<std::mutex> lock(stateMutex);
		simulatorStatus = 0; // IDLE
		resetMissiles();
		resetTargets();
	}
}

void MSSManager::setUserName(tstring userName)
{
	name = userName;
}

tstring MSSManager::getUserName()
{
	return name;
}

void MSSManager::setData(void* data)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
}

bool MSSManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("MSSManager/MSSManager.ini"));
	const unsigned int configuredInterval = iniHandler.readUInteger(_T("MSSManager"), _T("UPDATE_INTERVAL_MS"));
	const double configuredMultiplier = iniHandler.readDouble(_T("MSSManager"), _T("MISSILE_SPEED_MULTIPLIER"));
	const double configuredDistance = iniHandler.readDouble(_T("MSSManager"), _T("INTERCEPT_DISTANCE"));
	if (configuredInterval > 0) updateIntervalMs = configuredInterval;
	if (configuredMultiplier > 0.0) missileSpeedMultiplier = configuredMultiplier;
	if (configuredDistance > 0.0) interceptDistance = configuredDistance;

	if (timerHandle == -1)
	{
		timerHandle = nTimer->addPeriodicTask(updateIntervalMs, periodicFunc);
	}

	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
	return true;
}

bool MSSManager::stop()
{
	if (nTimer != nullptr && timerHandle != -1)
	{
		nTimer->removeTask(timerHandle);
		timerHandle = -1;
	}

	return true;
}

void MSSManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new MSSManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
