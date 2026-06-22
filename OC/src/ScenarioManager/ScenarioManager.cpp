#pragma once
#include "ScenarioManager.h"

/************************************************************************
	Constructor / Destructor
************************************************************************/
ScenarioManager::ScenarioManager(void)
{
	initialize();
}

ScenarioManager::~ScenarioManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void ScenarioManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("ScenarioManager"));

	mec = new MECComponent;
	mec->setUser(this);
}

void ScenarioManager::release(void)
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	BaseManager 구현
************************************************************************/
std::shared_ptr<NOM> ScenarioManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
	return nomMsg;
}

void ScenarioManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void ScenarioManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->updateMsg(nomMsg);
}

void ScenarioManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
}

void ScenarioManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void ScenarioManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

/**
 * @brief WPF에서 Scenario NOM 송신 요청 → MEC로 발행
 *        NOMHandler.SendNOMMessage() → UIManager.sendMsg() → ScenarioManager.sendMsg()
 */
void ScenarioManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] Scenario publish: " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void ScenarioManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void ScenarioManager::setUserName(tstring userName)
{
	name = userName;
}

tstring ScenarioManager::getUserName()
{
	return name;
}

void ScenarioManager::setData(void* data)
{
}

bool ScenarioManager::start()
{
	tcout << "[" << __FUNCTIONT__ << "] ScenarioManager started." << std::endl;
	return true;
}

bool ScenarioManager::stop()
{
	tcout << "[" << __FUNCTIONT__ << "] ScenarioManager stopped." << std::endl;
	return true;
}

void ScenarioManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new ScenarioManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
