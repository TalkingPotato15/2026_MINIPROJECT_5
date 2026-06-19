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
