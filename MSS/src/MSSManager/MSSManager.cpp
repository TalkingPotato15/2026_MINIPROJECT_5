#include <nFramework/util/IniHandler.h>
#include "MSSManager.h"

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

	periodicFunc = [this](void*) { this->sendMSSStatus(); };
	nTimer = &(NTimer::getInstance());
	timerHandle = -1;
	simulatorStatus = 0;
	resetMissiles();
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
		missileStates[i].missileId = i + 1;
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

	NUInteger status(simulatorStatus);
	statusNOM->setValue(_T("status"), &status);

	for (unsigned int i = 0; i < missileStates.size(); ++i)
	{
		const tstring prefix = _T("missileInfo[") + std::to_wstring(i) + _T("].");
		NUInteger targetId(missileStates[i].targetId);
		NUInteger missileId(missileStates[i].missileId);
		NDouble x(missileStates[i].x);
		NDouble y(missileStates[i].y);
		NDouble z(missileStates[i].z);
		NUInteger missileStatus(missileStates[i].status);

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
	if (!targetValue)
	{
		return;
	}

	const unsigned int targetId = targetValue->toUInt();
	for (auto& missile : missileStates)
	{
		if (missile.status == 1 && (missile.targetId == 0 || missile.targetId == targetId))
		{
			missile.targetId = targetId;
		}
	}
}

void MSSManager::recvIgnitionCommand(std::shared_ptr<NOM> nomMsg)
{
	auto missileIdValue = nomMsg->getValue(_T("missileID"));
	if (!missileIdValue)
	{
		return;
	}

	const unsigned int missileId = missileIdValue->toUInt();
	const unsigned int index = (missileId >= 1 && missileId <= missileStates.size())
		? missileId - 1 : missileId % missileStates.size();
	auto& missile = missileStates[index];
	missile.missileId = missileId;

	if (auto value = nomMsg->getValue(_T("targetID"))) missile.targetId = value->toUInt();
	if (auto value = nomMsg->getValue(_T("launchPos.x"))) missile.x = value->toDouble();
	if (auto value = nomMsg->getValue(_T("launchPos.y"))) missile.y = value->toDouble();
	if (auto value = nomMsg->getValue(_T("launchPos.z"))) missile.z = value->toDouble();

	missile.status = 1; // LAUNCHED
	simulatorStatus = 2; // RUNNING
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
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void MSSManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;

	if (nomMsg->getName() == _T("InnerATSInformationToMSS"))
	{
		recvATSInformation(nomMsg);
	}
	else if (nomMsg->getName() == _T("InnerIgnitionCommandToMSS"))
	{
		recvIgnitionCommand(nomMsg);
	}
	else if (nomMsg->getName() == _T("InnerStartSimulationToModel"))
	{
		simulatorStatus = 1; // READY
	}
	else if (nomMsg->getName() == _T("InnerStopSimulationToModel"))
	{
		simulatorStatus = 0; // IDLE
		resetMissiles();
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

	if (timerHandle == -1)
	{
		timerHandle = nTimer->addPeriodicTask(1000, periodicFunc);
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
