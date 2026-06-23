#pragma once
# include <nFramework/util/IniHandler.h>
# include "LauncherControlManager.h"
# include "VerticalLauncherModel.h"
# include <map>

/**
* @ class: LauncherControlManager
* @ author: 
* @ version: 
* @ see also: 
* @ description: 
* @ date: 
**/

/************************************************************************
	constructor / destructor
************************************************************************/
LauncherControlManager::LauncherControlManager(void)
{
	initialize();
}

LauncherControlManager::~LauncherControlManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
LauncherControlManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("LauncherControlManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
	launcherModel = std::make_unique<VerticalLauncherModel>();
}

void
LauncherControlManager::release(void)
{
	stopPeriodicTask();
	launcherModel.reset();
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
LauncherControlManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
LauncherControlManager::discoverMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
LauncherControlManager::updateMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void
LauncherControlManager::reflectMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
}

void
LauncherControlManager::deleteMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
LauncherControlManager::removeMsg(std::shared_ptr < NOM > nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void
LauncherControlManager::sendMsg(std::shared_ptr < NOM > nomMsg)
{
	//tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void
LauncherControlManager::recvMsg(std::shared_ptr < NOM > nomMsg)
{
	//tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	if (auto iter = msgFuncMap.find(nomMsg->getName()); iter != msgFuncMap.end())
	{
		iter->second(nomMsg);
	}
	else
	{
		tcerr << _T("[LauncherControlManager] No handler for message: ")
			<< nomMsg->getName() << std::endl;
	}
}

void
LauncherControlManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
LauncherControlManager::getUserName()
{
	return name;
}

void
LauncherControlManager::setData(void * data)
{
}

bool
LauncherControlManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("LauncherControlManager/LauncherControlManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	// 모의기 초기 상태 설정
	launcherModel->init();

	// 모의 주기 설정
	stopPeriodicTask();
	nTimer = &(NTimer::getInstance());
	STDFUNCTION periodicFunc = [this](void*) { simulatePeriodic(); };
	timerHandle = nTimer->addPeriodicTask(HEARTBEAT_INTERVAL_MS, periodicFunc, nullptr);
	if (timerHandle == 0)
	{
		tcerr << _T("[LauncherControlManager] Failed to register MLSStatus heartbeat.") << std::endl;
		return false;
	}

	// recvMsg에서 호출될 메서드 등록
	std::function<void(std::shared_ptr<NOM>)> msgProcessor;

	msgProcessor = std::bind(&LauncherControlManager::inputScenario, this, std::placeholders::_1);
	msgFuncMap.insert_or_assign(_T("InnerSettingScenario"), msgProcessor);

	msgProcessor = std::bind(&LauncherControlManager::startMLS, this, std::placeholders::_1);
	msgFuncMap.insert_or_assign(_T("InnerStartMLS"), msgProcessor);

	msgProcessor = std::bind(&LauncherControlManager::stopMLS, this, std::placeholders::_1);
	msgFuncMap.insert_or_assign(_T("InnerStopMLS"), msgProcessor);

	msgProcessor = std::bind(&LauncherControlManager::launchMLS, this, std::placeholders::_1);
	msgFuncMap.insert_or_assign(_T("InnerLaunchCommand"), msgProcessor);

	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	return true;
}

bool
LauncherControlManager::stop()
{
	stopPeriodicTask();

	bool result = true;
	return result;
}

void LauncherControlManager::stopPeriodicTask()
{
	if (nTimer && timerHandle != 0)
	{
		nTimer->removeTask(timerHandle);
		timerHandle = 0;
	}
}

void
LauncherControlManager::setMEBComponent(IMEBComponent * realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	Message Processor
************************************************************************/

void LauncherControlManager::inputScenario(std::shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
	{
		return;
	}

	POSITION position;
	position.x = nomMsg->getValue(_T("mlsPos.x"))->toDouble();
	position.y = nomMsg->getValue(_T("mlsPos.y"))->toDouble();
	position.z = nomMsg->getValue(_T("mlsPos.z"))->toDouble();

	launcherModel->setting(position);
}

void LauncherControlManager::startMLS(std::shared_ptr<NOM> nomMsg)
{
	launcherModel->start();
}

void LauncherControlManager::stopMLS(std::shared_ptr<NOM> nomMsg)
{
	launcherModel->stop();
}

void LauncherControlManager::launchMLS(std::shared_ptr<NOM> nomMsg)
{
	unsigned int targetID;
	targetID = nomMsg->getValue(_T("targetID"))->toUInt();

	unsigned int missileID = launcherModel->fireMissile(targetID);
	sendInnerIgnitionCommand(missileID, targetID);
}

void LauncherControlManager::sendInnerIgnitionCommand(unsigned int missileID, unsigned int targetID)
{
	// CommunicationManager로 IgnitionCommand 전송
	std::shared_ptr<NOM> sendNewMsg = meb->getNOMInstance(name, _T("InnerIgnitionCommand"));
	POSITION launchPos = launcherModel->currentPosition();

	sendNewMsg->setValue(_T("missileID"), &(NUInteger)missileID);
	sendNewMsg->setValue(_T("targetID"), &(NUInteger)targetID);
	sendNewMsg->setValue(_T("launchPos.x"), &(NDouble)launchPos.x);
	sendNewMsg->setValue(_T("launchPos.y"), &(NDouble)launchPos.y);
	sendNewMsg->setValue(_T("launchPos.z"), &(NDouble)launchPos.z);

	sendMsg(sendNewMsg);
}

void LauncherControlManager::simulatePeriodic()
{
	// CommunicationManager로 MLSSTATUS 전송
	std::shared_ptr<NOM> msg = meb->getNOMInstance(name, _T("InnerMLSStatus"));

	MLS_STATUS mlsStatus;
	mlsStatus = launcherModel->mlsStatus();
	if (mlsStatus.simulationStatus == SIMULATION_STATUS::RUNNING)
	{
		launcherModel->update(SIMULATION_TICK_SECONDS);
	}

	SIMULATION_STATUS simulationStatus = mlsStatus.simulationStatus;

	msg->setValue(_T("status"), &(NUInteger)(static_cast<unsigned int>(simulationStatus)));
	msg->setValue(_T("launcherInfo.missileStatus1"), &(NUInteger)static_cast<unsigned int>(mlsStatus.launcherInfo.missileStatus1));
	msg->setValue(_T("launcherInfo.missileStatus2"), &(NUInteger)static_cast<unsigned int>(mlsStatus.launcherInfo.missileStatus2));
	msg->setValue(_T("launcherInfo.missileStatus3"), &(NUInteger)static_cast<unsigned int>(mlsStatus.launcherInfo.missileStatus3));
	msg->setValue(_T("launcherInfo.missileStatus4"), &(NUInteger)static_cast<unsigned int>(mlsStatus.launcherInfo.missileStatus4));
	msg->setValue(_T("launcherInfo.missileStock"), &(NUInteger)mlsStatus.missileStock);

	sendMsg(msg);
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new LauncherControlManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
