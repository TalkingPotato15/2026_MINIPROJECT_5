#pragma once
#include "SimulationManager.h"

/************************************************************************
	Constructor / Destructor
************************************************************************/
SimulationManager::SimulationManager(void)
{
	initialize();
}

SimulationManager::~SimulationManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void SimulationManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("SimulationManager"));

	mec = new MECComponent;
	mec->setUser(this);

	funcMapInit();
}

void SimulationManager::release(void)
{
	funcMap.clear();
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

void SimulationManager::funcMapInit()
{
	funcMap[_T("ATSStatus")] = std::bind(&SimulationManager::onATSStatus, this, std::placeholders::_1);
	funcMap[_T("RSSStatus")] = std::bind(&SimulationManager::onRSSStatus, this, std::placeholders::_1);
	funcMap[_T("MSSStatus")] = std::bind(&SimulationManager::onMSSStatus, this, std::placeholders::_1);
	funcMap[_T("MLSStatus")] = std::bind(&SimulationManager::onMLSStatus, this, std::placeholders::_1);
}

/************************************************************************
	BaseManager 구현
************************************************************************/
std::shared_ptr<NOM> SimulationManager::registerMsg(tstring msgName)
{
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
	return nomMsg;
}

void SimulationManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void SimulationManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->updateMsg(nomMsg);
}

void SimulationManager::reflectMsg(std::shared_ptr<NOM> nomMsg) {}

void SimulationManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void SimulationManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

/**
 * @brief WPF에서 StartSimulation 또는 Stop NOM 발행 요청
 */
void SimulationManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

/**
 * @brief 각 CSC 상태 메시지 수신 → funcMap 분기
 */
void SimulationManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	auto iter = funcMap.find(nomMsg->getName());
	if (iter != funcMap.end())
	{
		iter->second(nomMsg);
	}
}

void SimulationManager::setUserName(tstring userName) { name = userName; }
tstring SimulationManager::getUserName() { return name; }
void SimulationManager::setData(void* data) {}

bool SimulationManager::start()
{
	tcout << "[" << __FUNCTIONT__ << "] SimulationManager started." << std::endl;
	return true;
}

bool SimulationManager::stop()
{
	simRunning = false;
	tcout << "[" << __FUNCTIONT__ << "] SimulationManager stopped." << std::endl;
	return true;
}

void SimulationManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	수신 핸들러
************************************************************************/
void SimulationManager::onATSStatus(std::shared_ptr<NOM> nomMsg)
{
	atsConnected = true;
	tcout << "[SimulationManager] ATSStatus received." << std::endl;
}

void SimulationManager::onRSSStatus(std::shared_ptr<NOM> nomMsg)
{
	rssConnected = true;
	tcout << "[SimulationManager] RSSStatus received." << std::endl;
}

void SimulationManager::onMSSStatus(std::shared_ptr<NOM> nomMsg)
{
	mssConnected = true;
	tcout << "[SimulationManager] MSSStatus received." << std::endl;
}

void SimulationManager::onMLSStatus(std::shared_ptr<NOM> nomMsg)
{
	mlsConnected = true;
	tcout << "[SimulationManager] MLSStatus received." << std::endl;
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new SimulationManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
