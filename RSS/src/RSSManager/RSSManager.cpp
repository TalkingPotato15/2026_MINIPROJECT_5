#include <nFramework/util/IniHandler.h>
#include "RSSManager.h"

RSSManager::RSSManager(void)
{
	initialize();
}

RSSManager::~RSSManager(void)
{
	release();
}

void RSSManager::initialize(void)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;

	setUserName(_T("RSSManager"));

	mec = new MECComponent;
	mec->setUser(this);

	periodicFunc = [this](void*) { this->sendRSSStatus(); };
	nTimer = &(NTimer::getInstance());
	timerHandle = -1;

	funcMapInit();
}

void RSSManager::release()
{
	if (nTimer != nullptr && timerHandle != -1)
	{
		nTimer->removeTask(timerHandle);
		timerHandle = -1;
	}

	delete mec;
	mec = nullptr;
	meb = nullptr;
	funcMap.clear();
	resetDetectionState();
}

void RSSManager::funcMapInit()
{
	std::function<void(std::shared_ptr<NOM>)> msgProc;

	msgProc = std::bind(&RSSManager::recvInnerATSInformationToRSS, this, std::placeholders::_1);
	funcMap.insert({ _T("InnerATSInformationToRSS"), msgProc });

	msgProc = std::bind(&RSSManager::recvInnerMSSInformationToRSS, this, std::placeholders::_1);
	funcMap.insert({ _T("InnerMSSInformationToRSS"), msgProc });

	msgProc = std::bind(&RSSManager::recvInnerRSSDetectionAreaToRSS, this, std::placeholders::_1);
	funcMap.insert({ _T("InnerRSSDetectionAreaToRSS"), msgProc });

	msgProc = std::bind(&RSSManager::recvInnerStartSimulation, this, std::placeholders::_1);
	funcMap.insert({ _T("InnerStartSimulation"), msgProc });

	msgProc = std::bind(&RSSManager::recvInnerStopSimulation, this, std::placeholders::_1);
	funcMap.insert({ _T("InnerStopSimulation"), msgProc });
}

void RSSManager::resetDetectionState()
{
	detectionManager.reset();
	detonationManager.reset();
}

void RSSManager::sendRSSStatus()
{
	rssStatusNOM = meb->getNOMInstance(name, _T("InnerRSSStatusToComm"));
	if (!rssStatusNOM.get())
	{
		//ntcout << _T("[RSSManager] InnerRSSStatusToComm NOM is undefined.") << std::endl;
		return;
	}

	NUInteger status(1);
	rssStatusNOM->setValue(_T("status"), &status);

	sendMsg(rssStatusNOM);
}

std::shared_ptr<NOM> RSSManager::registerMsg(tstring msgName)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << msgName << std::endl;

	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
	return nomMsg;
}

void RSSManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void RSSManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->updateMsg(nomMsg);
}

void RSSManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
}

void RSSManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void RSSManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void RSSManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void RSSManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;

	if (auto iter = funcMap.find(nomMsg->getName()); iter != funcMap.end())
	{
		iter->second(nomMsg);
	}
}

void RSSManager::setUserName(tstring userName)
{
	name = userName;
}

tstring RSSManager::getUserName()
{
	return name;
}

void RSSManager::setData(void* data)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
}

bool RSSManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("RSSManager/RSSManager.ini"));

	if (timerHandle == -1)
	{
		timerHandle = nTimer->addPeriodicTask(1000, periodicFunc);
	}

	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
	return true;
}

bool RSSManager::stop()
{
	if (nTimer != nullptr && timerHandle != -1)
	{
		nTimer->removeTask(timerHandle);
		timerHandle = -1;
	}

	return true;
}

void RSSManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void RSSManager::recvInnerStartSimulation(std::shared_ptr<NOM> nomMsg)
{
	(void)nomMsg;
	detectionActive = true;
	ntcout << _T("[RSSManager] Detection started.") << std::endl;
}

void RSSManager::recvInnerStopSimulation(std::shared_ptr<NOM> nomMsg)
{
	(void)nomMsg;
	detectionActive = false;
	resetDetectionState();
	ntcout << _T("[RSSManager] Detection stopped. Detection/interception cache cleared.") << std::endl;
}

void RSSManager::recvInnerRSSDetectionAreaToRSS(std::shared_ptr<NOM> nomMsg)
{
	auto xValue = nomMsg->getValue(_T("rssPos.x"));
	auto yValue = nomMsg->getValue(_T("rssPos.y"));
	auto zValue = nomMsg->getValue(_T("rssPos.z"));
	auto radiusValue = nomMsg->getValue(_T("rssRadius"));
	if (!xValue || !yValue || !zValue || !radiusValue)
	{
		ntcout << _T("[RSSManager] RSS detection area is incomplete.") << std::endl;
		return;
	}

	detectionManager.setDetectionArea(
		xValue->toDouble(),
		yValue->toDouble(),
		zValue->toDouble(),
		static_cast<double>(radiusValue->toUInt()));
	detonationManager.reset();
}

void RSSManager::recvInnerATSInformationToRSS(std::shared_ptr<NOM> nomMsg)
{
	if (!detectionActive)
	{
		return;
	}

	for (int i = 0; i < 4; ++i)
	{
		tstring prefix = _T("targetInfo[") + to_tstring(i) + _T("]");
		CachedATSInfo atsInfo;
		if (!tryReadATSInfo(nomMsg, prefix, atsInfo))
		{
			continue;
		}

		bool wasDetected = detectionManager.isDetected(atsInfo.targetId);
		bool isCurrentlyInRange = detectionManager.isInRange(atsInfo);
		double distance = detectionManager.hasDetectionArea() ? detectionManager.getDistanceToRSS(atsInfo) : 0.0;
		ntcout << _T("[RSSManager] ATSInformation received: index=") << i
			<< _T(", targetId=") << atsInfo.targetId
			<< _T(", atsStatus=") << atsInfo.atsStatus
			<< _T(", pos=(") << atsInfo.x << _T(", ") << atsInfo.y << _T(", ") << atsInfo.z << _T(")")
			<< _T(", speed=") << atsInfo.speed;
		if (detectionManager.hasDetectionArea())
		{
			ntcout << _T(", distance=") << distance
				<< _T(", inRange=") << (isCurrentlyInRange ? 1 : 0);
		}
		else
		{
			ntcout << _T(", rssAreaReady=0");
		}
		ntcout << std::endl;

		if (atsInfo.atsStatus != 1)
		{
			if (atsInfo.atsStatus == 2)
			{
				detonationManager.markDestroyed(atsInfo.targetId);
				detectionManager.removeDetectedTarget(atsInfo.targetId);
			}
			continue;
		}

		if (!wasDetected)
		{
			if (!isCurrentlyInRange)
			{
				continue;
			}

			detectionManager.markDetected(atsInfo);
			ntcout << _T("[RSSManager] Target detected: targetId=") << atsInfo.targetId << std::endl;
			sendTargetDetection(atsInfo.targetId, 1);
			sendATSInformationUplink(atsInfo);
			continue;
		}

		if (!isCurrentlyInRange)
		{
			auto cachedTarget = detectionManager.findDetectedTarget(atsInfo.targetId);
			if (cachedTarget != nullptr)
			{
				CachedATSInfo lastDetectedTarget = *cachedTarget;
				lastDetectedTarget.atsStatus = 0;
				ntcout << _T("[RSSManager] Target left RSS range: targetId=") << atsInfo.targetId
					<< _T(", lastPos=(") << lastDetectedTarget.x << _T(", ")
					<< lastDetectedTarget.y << _T(", ") << lastDetectedTarget.z << _T(")") << std::endl;
				detectionManager.removeDetectedTarget(atsInfo.targetId);
				sendTargetDetection(atsInfo.targetId, 0);
				sendATSInformationUplink(lastDetectedTarget);
			}
			continue;
		}

		detectionManager.updateDetectedTarget(atsInfo);

		auto cachedTarget = detectionManager.findDetectedTarget(atsInfo.targetId);
		if (cachedTarget != nullptr)
		{
			sendATSInformationUplink(*cachedTarget);
		}
	}
}

void RSSManager::recvInnerMSSInformationToRSS(std::shared_ptr<NOM> nomMsg)
{
	if (!detectionActive)
	{
		return;
	}

	for (int i = 0; i < 4; ++i)
	{
		tstring prefix = _T("missileInfo[") + to_tstring(i) + _T("]");
		CachedMSSInfo mssInfo;
		if (!tryReadMSSInfo(nomMsg, prefix, mssInfo))
		{
			continue;
		}

		if (mssInfo.targetId == 0 || detonationManager.isDestroyed(mssInfo.targetId))
		{
			continue;
		}

		if (!detectionManager.isDetected(mssInfo.targetId))
		{
			continue;
		}

		auto atsInfo = detectionManager.findDetectedTarget(mssInfo.targetId);
		if (atsInfo == nullptr)
		{
			continue;
		}

		double distance = detonationManager.getDistance(*atsInfo, mssInfo);
		bool intercepted = detonationManager.isIntercepted(*atsInfo, mssInfo);
		ntcout << _T("[RSSManager] ATS-MSS distance: targetId=") << mssInfo.targetId
			<< _T(", missileId=") << mssInfo.missileId
			<< _T(", distance=") << distance
			<< _T(", intercepted=") << (intercepted ? 1 : 0) << std::endl;

		if (intercepted)
		{
			ntcout << _T("[RSSManager] Target intercepted: targetId=") << mssInfo.targetId
				<< _T(", missileId=") << mssInfo.missileId
				<< _T(", distance=") << distance << std::endl;
			sendTargetDestroyed(mssInfo.targetId, 0);
			detonationManager.markDestroyed(mssInfo.targetId);
			continue;
		}

		sendATSInformationUplink(*atsInfo);
	}
}

bool RSSManager::tryReadATSInfo(std::shared_ptr<NOM> nomMsg, const tstring& targetPrefix, CachedATSInfo& atsInfo) const
{
	auto xValue = nomMsg->getValue(targetPrefix + _T(".ATSPos.x"));
	auto yValue = nomMsg->getValue(targetPrefix + _T(".ATSPos.y"));
	auto zValue = nomMsg->getValue(targetPrefix + _T(".ATSPos.z"));
	auto speedValue = nomMsg->getValue(targetPrefix + _T(".speed"));
	auto targetIDValue = nomMsg->getValue(targetPrefix + _T(".targetId"));
	auto atsStatusValue = nomMsg->getValue(targetPrefix + _T(".atsStatus"));
	if (!xValue || !yValue || !zValue || !speedValue || !targetIDValue || !atsStatusValue)
	{
		return false;
	}

	atsInfo.x = xValue->toDouble();
	atsInfo.y = yValue->toDouble();
	atsInfo.z = zValue->toDouble();
	atsInfo.speed = speedValue->toUInt();
	atsInfo.targetId = targetIDValue->toUInt();
	atsInfo.atsStatus = atsStatusValue->toUInt();

	return true;
}

bool RSSManager::tryReadMSSInfo(std::shared_ptr<NOM> nomMsg, const tstring& missilePrefix, CachedMSSInfo& mssInfo) const
{
	auto targetIDValue = nomMsg->getValue(missilePrefix + _T(".targetId"));
	auto missileIDValue = nomMsg->getValue(missilePrefix + _T(".missileId"));
	auto xValue = nomMsg->getValue(missilePrefix + _T(".MSSPos.x"));
	auto yValue = nomMsg->getValue(missilePrefix + _T(".MSSPos.y"));
	auto zValue = nomMsg->getValue(missilePrefix + _T(".MSSPos.z"));
	if (!targetIDValue || !missileIDValue || !xValue || !yValue || !zValue)
	{
		return false;
	}

	mssInfo.targetId = targetIDValue->toUInt();
	mssInfo.missileId = missileIDValue->toUInt();
	mssInfo.x = xValue->toDouble();
	mssInfo.y = yValue->toDouble();
	mssInfo.z = zValue->toDouble();

	return true;
}

void RSSManager::sendTargetDetection(uint32_t targetID, uint32_t success)
{
	auto nomMsg = meb->getNOMInstance(name, _T("InnerTargetDetectionToComm"));
	if (!nomMsg.get())
	{
		ntcout << _T("[RSSManager] InnerTargetDetectionToComm NOM is undefined.") << std::endl;
		return;
	}

	NUInteger target(targetID);
	NUInteger result(success);
	nomMsg->setValue(_T("targetID"), &target);
	nomMsg->setValue(_T("targetDetectonSuccess"), &result);
	sendMsg(nomMsg);
}

void RSSManager::sendTargetDestroyed(uint32_t targetID, uint32_t missionFlag)
{
	auto nomMsg = meb->getNOMInstance(name, _T("InnerTargetDestroyedToComm"));
	if (!nomMsg.get())
	{
		ntcout << _T("[RSSManager] InnerTargetDestroyedToComm NOM is undefined.") << std::endl;
		return;
	}

	NUInteger target(targetID);
	NUInteger result(missionFlag);
	nomMsg->setValue(_T("targetID"), &target);
	nomMsg->setValue(_T("missionFlag"), &result);
	sendMsg(nomMsg);
}

void RSSManager::sendATSInformationUplink(const CachedATSInfo& atsInfo)
{
	auto uplinkMsg = meb->getNOMInstance(name, _T("InnerATSInformationUplinkToComm"));
	if (!uplinkMsg.get())
	{
		ntcout << _T("[RSSManager] InnerATSInformationUplinkToComm NOM is undefined.") << std::endl;
		return;
	}

	NDouble x(atsInfo.x);
	NDouble y(atsInfo.y);
	NDouble z(atsInfo.z);
	NUInteger speed(atsInfo.speed);
	NUInteger targetId(atsInfo.targetId);
	NUInteger atsStatus(atsInfo.atsStatus);

	uplinkMsg->setValue(_T("matchedTarget.ATSPos.x"), &x);
	uplinkMsg->setValue(_T("matchedTarget.ATSPos.y"), &y);
	uplinkMsg->setValue(_T("matchedTarget.ATSPos.z"), &z);
	uplinkMsg->setValue(_T("matchedTarget.speed"), &speed);
	uplinkMsg->setValue(_T("matchedTarget.targetId"), &targetId);
	uplinkMsg->setValue(_T("matchedTarget.atsStatus"), &atsStatus);
	ntcout << _T("[RSSManager] ATSInformationUplink sent: targetId=") << atsInfo.targetId
		<< _T(", atsStatus=") << atsInfo.atsStatus
		<< _T(", pos=(") << atsInfo.x << _T(", ") << atsInfo.y << _T(", ") << atsInfo.z << _T(")")
		<< _T(", speed=") << atsInfo.speed << std::endl;
	sendMsg(uplinkMsg);
}

extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new RSSManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
