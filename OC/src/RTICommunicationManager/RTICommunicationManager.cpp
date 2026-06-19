#include "RTICommunicationManager.h"
#include <nFramework/util/IniHandler.h>
#include <sstream>
#include "RTICommunicationManagerIntelliVal.h"

using namespace nframework::nom;

/************************************************************************
	constructor / destructor
************************************************************************/
RTICommunicationManager::RTICommunicationManager(void)
{
	initialize();
}

RTICommunicationManager::~RTICommunicationManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
RTICommunicationManager::initialize(void)
{
	setUserName(L"RTICommunicationManager");	
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " ;
	l.info(s);
	
	continueSimFlag.store(true);

	// design by contract
	mec = new MECComponent; 
	mec->setUser(this);

	*isStarted = false;
}

void
RTICommunicationManager::release()
{
	continueSimFlag.store(false);

	resignFed();
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
RTICommunicationManager::registerMsg(std::wstring msgName)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << msgName ;
	l.info(s);
	
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
RTICommunicationManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	discoveredMsg.emplace(nomMsg->getInstanceID(), nomMsg);
	if (*isStarted && hlaCommunicator) {
		hlaCommunicator->registerCommMsg(nomMsg);
	}
}

void
RTICommunicationManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	mec->updateMsg(nomMsg);
}

void
RTICommunicationManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	if (*isStarted && hlaCommunicator) {
		hlaCommunicator->updateCommMsg(nomMsg);
	}
}

void
RTICommunicationManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
RTICommunicationManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	if (auto result = discoveredMsg.erase(nomMsg->getInstanceID());
		result != 0) {
		if (*isStarted && hlaCommunicator) {
			hlaCommunicator->deleteCommMsg(nomMsg);
		}
	}
}

void
RTICommunicationManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	mec->sendMsg(nomMsg);
}

void
RTICommunicationManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	if (*isStarted && hlaCommunicator) {
		hlaCommunicator->sendCommMsg(nomMsg);
	}
}

void
RTICommunicationManager::setUserName(std::wstring userName)
{
	name = userName; 
}

std::wstring
RTICommunicationManager::getUserName()
{
	return name;
}

void
RTICommunicationManager::setData(void* data)
{
	// if need be, write your code
}

bool
RTICommunicationManager::start()
{
	joinFed();

	*isStarted = true;
	return true;
}

bool
RTICommunicationManager::stop()
{ 
	resignFed();

	return true;
}

void
RTICommunicationManager::resignFed()
{
	std::lock_guard<std::mutex> lock(mut);
	continueSimFlag.store(false);

	if (hlaCommunicator && hlaCommConfig) {
		hlaCommunicator->releaseNetEnv(hlaCommConfig);

		hlaCommunicator.reset();
		delete hlaCommConfig;
		hlaCommConfig = nullptr;
	}
}

void
RTICommunicationManager::joinFed()
{
	std::lock_guard<std::mutex> lock(mut);
	continueSimFlag.store(true);

	// The code below includes use of the middleware such as RTI
	if (!hlaCommunicator && !hlaCommConfig) {
		std::wstringstream s; s << "[" __FUNCTIONT__ << "] " << " Try to join federation." ;
		l.info(s);
		hlaCommConfig = new CommunicationConfig;
		hlaCommConfig->setIni(L"RTICommunicationManager/HLAFed.ini");
		hlaCommunicator = std::make_unique<HLACommInterface>(this);
		hlaCommunicator->setMEBComponent(meb);

		if (!hlaCommunicator->initNetEnv(hlaCommConfig)) {
			hlaCommunicator.reset();
			delete hlaCommConfig;
			hlaCommConfig = nullptr;
		}
		else {
			// else
		}
	}
	else
	{
		// else
	}

	if (hlaCommunicator && hlaCommConfig)
	{
		*isStarted = true;
	}
	else
	{
		// else
	}
}

void
RTICommunicationManager::setMEBComponent(IMEBComponent* realMEB)
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
	return new RTICommunicationManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}