#pragma once
# include <nFramework/util/IniHandler.h>
# include "ScenarioManager.h"
# include <map>
# include <format>

/**
* @ class: ScenarioManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
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
void
ScenarioManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("ScenarioManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
ScenarioManager::release(void)
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
ScenarioManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
ScenarioManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
ScenarioManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
ScenarioManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
ScenarioManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
ScenarioManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
ScenarioManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
ScenarioManager::recvMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	if (auto iter = msgFuncMap.find(nomMsg->getName()); iter != msgFuncMap.end())
	{
		iter->second(nomMsg);
	}
}

void
ScenarioManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
ScenarioManager::getUserName()
{
	return name;
}

void
ScenarioManager::setData(void * data)
{
}

bool
ScenarioManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("ScenarioManager/ScenarioManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	// recvMsg에서 호출될 메서드 등록
	std::function<void(std::shared_ptr<NOM>)> msgProcessor;

	msgProcessor = std::bind(&ScenarioManager::inputScenario, this, std::placeholders::_1);
	msgFuncMap.insert(make_pair(_T("InnerScenario"), msgProcessor));
	
	msgProcessor = std::bind(&ScenarioManager::startScenario, this, std::placeholders::_1);
	msgFuncMap.insert(make_pair(_T("InnerStartSimulation"), msgProcessor));

	msgProcessor = std::bind(&ScenarioManager::stopScenario, this, std::placeholders::_1);
	msgFuncMap.insert(make_pair(_T("InnerStop"), msgProcessor));

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
ScenarioManager::stop()
{
	bool result = true;
	return result;
}

void
ScenarioManager::setMEBComponent(IMEBComponent * realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	Message Processor
************************************************************************/

void
ScenarioManager::inputScenario(std::shared_ptr<NOM> nomMsg)
{
	POSITION scenarioPos;

	scenarioPos.x = nomMsg->getValue(_T("mlsPos.x"))->toDouble();
	scenarioPos.y = nomMsg->getValue(_T("mlsPos.y"))->toDouble();
	scenarioPos.z = nomMsg->getValue(_T("mlsPos.z"))->toDouble();

	// LauncherControlManager로 전송
	std::shared_ptr<NOM> msg = meb->getNOMInstance(name, _T("InnerSettingScenario"));
	msg->setValue(_T("mlsPos.x"), &NDouble(scenarioPos.x));
	msg->setValue(_T("mlsPos.y"), &NDouble(scenarioPos.y));
	msg->setValue(_T("mlsPos.z"), &NDouble(scenarioPos.z));

	std::cout << std::format("[ScenarioManager::inputScenario] : {} {} {}\n", scenarioPos.x, scenarioPos.y, scenarioPos.z);

	sendMsg(msg);
}

void
ScenarioManager::startScenario(std::shared_ptr<NOM> nomMsg)
{
	// LauncherControlManager로 전송
	std::shared_ptr<NOM> msg = meb->getNOMInstance(name, _T("InnerStartMLS"));

	std::cout << "[ScenarioManager::startScenario]\n";

	sendMsg(msg);
}

void
ScenarioManager::stopScenario(std::shared_ptr<NOM> nomMsg)
{
	// LauncherControlManager로 전송
	std::shared_ptr<NOM> msg = meb->getNOMInstance(name, _T("InnerStopMLS"));

	std::cout << "[ScenarioManager::stopScenario]\n";

	sendMsg(msg);
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
