#include <nFramework/util/IniHandler.h>
#include "RSSManager.h"

namespace
{
	void copyUIntValue(const std::shared_ptr<NOM>& src, const tstring& srcName, const std::shared_ptr<NOM>& dst, const tstring& dstName)
	{
		if (auto value = src->getValue(srcName))
		{
			NUInteger v(value->toUInt());
			dst->setValue(dstName, &v);
		}
	}

	void copyDoubleValue(const std::shared_ptr<NOM>& src, const tstring& srcName, const std::shared_ptr<NOM>& dst, const tstring& dstName)
	{
		if (auto value = src->getValue(srcName))
		{
			NDouble v(value->toDouble());
			dst->setValue(dstName, &v);
		}
	}

	void copyATSInformation(const std::shared_ptr<NOM>& src, const tstring& srcPrefix, const std::shared_ptr<NOM>& dst, const tstring& dstPrefix)
	{
		copyDoubleValue(src, srcPrefix + _T(".ATSPos.x"), dst, dstPrefix + _T(".ATSPos.x"));
		copyDoubleValue(src, srcPrefix + _T(".ATSPos.y"), dst, dstPrefix + _T(".ATSPos.y"));
		copyDoubleValue(src, srcPrefix + _T(".ATSPos.z"), dst, dstPrefix + _T(".ATSPos.z"));
		copyUIntValue(src, srcPrefix + _T(".speed"), dst, dstPrefix + _T(".speed"));
		copyUIntValue(src, srcPrefix + _T(".targetId"), dst, dstPrefix + _T(".targetId"));
		copyUIntValue(src, srcPrefix + _T(".atsStatus"), dst, dstPrefix + _T(".atsStatus"));
	}
}

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
	detectedTargetIds.clear();
	destroyedTargetIds.clear();
}

void RSSManager::funcMapInit()
{
	std::function<void(std::shared_ptr<NOM>)> msgProc;

	msgProc = std::bind(&RSSManager::recvInnerATSInformationToRSS, this, std::placeholders::_1);
	funcMap.insert({ _T("InnerATSInformationToRSS"), msgProc });

	msgProc = std::bind(&RSSManager::recvInnerMSSInformationToRSS, this, std::placeholders::_1);
	funcMap.insert({ _T("InnerMSSInformationToRSS"), msgProc });
}

void RSSManager::sendRSSStatus()
{
	rssStatusNOM = meb->getNOMInstance(name, _T("InnerRSSStatusToComm"));
	if (!rssStatusNOM.get())
	{
		ntcout << _T("[RSSManager] InnerRSSStatusToComm NOM is undefined.") << std::endl;
		return;
	}

	NInteger status(1);
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

void RSSManager::recvInnerATSInformationToRSS(std::shared_ptr<NOM> nomMsg)
{
	for (int i = 0; i < 4; ++i)
	{
		tstring prefix = _T("targetInfo[") + to_tstring(i) + _T("]");
		auto targetIDValue = nomMsg->getValue(prefix + _T(".targetId"));
		if (!targetIDValue)
		{
			continue;
		}

		uint32_t targetID = targetIDValue->toUInt();
		if (targetID == 0)
		{
			continue;
		}

		uint32_t success = 1;
		if (auto atsStatusValue = nomMsg->getValue(prefix + _T(".atsStatus")))
		{
			success = atsStatusValue->toUInt() == 0 ? 0 : 1;
		}

		if (success != 0)
		{
			sendATSInformationUplink(nomMsg, prefix);
		}

		if (detectedTargetIds.find(targetID) != detectedTargetIds.end())
		{
			continue;
		}

		sendTargetDetection(targetID, success);
		detectedTargetIds.insert(targetID);
	}
}

void RSSManager::recvInnerMSSInformationToRSS(std::shared_ptr<NOM> nomMsg)
{
	for (int i = 0; i < 4; ++i)
	{
		tstring prefix = _T("missileInfo[") + to_tstring(i) + _T("]");
		auto targetIDValue = nomMsg->getValue(prefix + _T(".targetId"));
		auto mssStatusValue = nomMsg->getValue(prefix + _T(".mssStatus"));
		if (!targetIDValue || !mssStatusValue)
		{
			continue;
		}

		uint32_t targetID = targetIDValue->toUInt();
		uint32_t missionFlag = mssStatusValue->toUInt() == 0 ? 0 : 1;
		if (targetID == 0 || missionFlag == 0 || destroyedTargetIds.find(targetID) != destroyedTargetIds.end())
		{
			continue;
		}

		sendTargetDestroyed(targetID, missionFlag);
		destroyedTargetIds.insert(targetID);
	}
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

void RSSManager::sendATSInformationUplink(std::shared_ptr<NOM> nomMsg, const tstring& targetPrefix)
{
	auto uplinkMsg = meb->getNOMInstance(name, _T("InnerATSInformationUplinkToComm"));
	if (!uplinkMsg.get())
	{
		ntcout << _T("[RSSManager] InnerATSInformationUplinkToComm NOM is undefined.") << std::endl;
		return;
	}

	copyATSInformation(nomMsg, targetPrefix, uplinkMsg, _T("matchedTarget"));
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
