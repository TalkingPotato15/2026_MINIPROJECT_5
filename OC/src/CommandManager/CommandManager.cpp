#pragma once
#include "CommandManager.h"
#include <nFramework/util/IniHandler.h>
#include "CommandManagerIntelliVal.h"

using namespace nframework;
using namespace nom;
using namespace std::chrono;
namespace air = intellival::BaseEntity_PhysicalEntity_Platform_Aircraft;
namespace evtrpt = intellival::EventReport;

/************************************************************************
	Constructor / Destructor
************************************************************************/
CommandManager::CommandManager(void)
{
	init();
}

CommandManager::~CommandManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
CommandManager::init()
{
	
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " ;
	l.info(s);
	
	setUserName(L"CommandManager");


	// by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
CommandManager::release()
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	Inherit Function
************************************************************************/
std::shared_ptr<NOM>
CommandManager::registerMsg(std::wstring msgName)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << msgName ;
	l.info(s);
	
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
CommandManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	discoveredMsg.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
CommandManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->updateMsg(nomMsg);
}

void
CommandManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	//if (nomMsg->getName() == L"AirThreatInformation") {
	//	auto objectCount = nomMsg->getValue(L"ObjectCount")->toUShort();
	//	tcout << __FUNCTIONW__ << L" " << objectCount ;
	//}
	//tcout << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	// if need be, write your code
}

void
CommandManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->sendMsg(nomMsg);
}

void
CommandManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << __FUNCTIONT__ L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
CommandManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	std::map<unsigned int, std::shared_ptr<NOM>>::iterator itr;
	itr = discoveredMsg.find(nomMsg->getInstanceID());

	if(itr != discoveredMsg.end())
	{
		discoveredMsg.erase(nomMsg->getInstanceID());
	}
	else
	{
		s.str(L""); s << L"[CommandManager] " << L"message was not removed." ;
		l.info(s);
	}
}

void
CommandManager::processStartResume(std::shared_ptr<NOM> nomMsg)
{
	nomMsg->setValue(_T("OriginatingEntity.EntityNumber"), &NUShort(10));
}

void
CommandManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	//tcout << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() << ;
	//tcout << L"[" << __FUNCTIONW__ << L"] "<< nomMsg->getInstanceName() << ;
	// if need be, write your code
}

void
CommandManager::setUserName(std::wstring userName)
{
	name = userName; 
}

std::wstring
CommandManager::getUserName()
{
	return name;
}

void
CommandManager::setData(void* data)
{
	// if need be, write your code
}

bool
CommandManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(L"CommandManager/CommandManager.ini"); // ※주의 작업디렉터리: Main.exe가 있는 경로

	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " ;
	l.info(s);
	

	unsigned int numOfSimulators = iniHandler.readInteger(L"Simulators", L"Count");


	for (unsigned int cnt = 1; cnt <= numOfSimulators; cnt++)
	{
		tstringstream dllPrefix;
		dllPrefix << L"Simulator_" << cnt;

		std::wstring dllIndex;
		dllPrefix >> dllIndex;

		std::wstring simulator = iniHandler.readString(dllIndex, L"Simulator");

		weapons.emplace_back(simulator);
	}

	std::shared_ptr<NOM> dds_obj;
	std::wstring cmdStr;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	nTimer = &(NTimer::getInstance());
	int timerHandle = 0;
	std::wstring prompt = L"cmd input (e.g., register, delete, update. send, break, quit, etc.):";
	s.str(L""); s << prompt;
	l.info(s);

	while (tcin >> cmdStr)
	{

		if (cmdStr == L"register")
		{
			testObjNOM = this->registerMsg(L"BaseEntity.PhysicalEntity.Platform.Aircraft");
		}
		else if (cmdStr == L"delete")
		{
			this->deleteMsg(testObjNOM);
		}
		else if (cmdStr == L"update")
		{
			if (testObjNOM.get())
			{

				testObjNOM->setValue(L"WorldLocation.X", &air::v_WorldLocation_X(10.0));
				
				this->updateMsg(testObjNOM);
			}
			else
			{
				s.str(L""); s << L"message is not registered.";
				l.info(s);
			}
		}
		else if (cmdStr == L"send")
		{
			/*STDFUNCTION testPeriodic = std::bind(&CommandManager::testSend, this);
			timerHandle = nTimer->addPeriodicTask(1000, testPeriodic);
			this->testSend();*/
			wchar_t* args = L"SAAM";
			STDFUNCTION testPeriodic = std::bind(&CommandManager::testSendArgs, this, args);
			timerHandle = nTimer->addPeriodicTask(1000, testPeriodic, (void*)args);
			this->testSendArgs(args);
		}
		else if (cmdStr == L"break")
		{
			nTimer->removeTask(timerHandle);
		}
		else if (cmdStr == L"quit")
		{
			break;
		}
		else
		{
			s.str(L""); s << L"[" << __FUNCTIONW__ << L"] " << L"command is not valid." ;
			l.info(s);
		}
	}

	return true;
}

bool
CommandManager::stop()
{
	return true;
}

void
CommandManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void
CommandManager::testSend()
{
	using namespace intellival::EventReport;
	std::shared_ptr<NOM> testIntrNOM = meb->getNOMInstance(getUserName(), L"EventReport");
	evtrpt::v_OriginatingEntity_FederateIdentifier_SiteID id = 7;
	testIntrNOM->setValue(L"OriginatingEntity.FederateIdentifier.SiteID", &id);
	evtrpt::v_EventType evtType = 101;
	testIntrNOM->setValue(L"EventType", &evtType);

	//using namespace intellival::SetData;
	//std::shared_ptr<NOM> testIntrNOM = meb->getNOMInstance(getUserName(), L"SetData");
	//OriginatingEntity_FederateIdentifier_SiteID id = 7;
	//testIntrNOM->setValue(L"OriginatingEntity.FederateIdentifier.SiteID", &id);
	//RequestIdentifier requestIdentifier = 101;
	//testIntrNOM->setValue(L"RequestIdentifier", &requestIdentifier);

	this->sendMsg(testIntrNOM);
}

void
CommandManager::testSendArgs(wchar_t* arg)
{
	std::wstringstream s; s << arg ;
	l.info(s);
	
	using namespace intellival::EventReport;
	std::shared_ptr<NOM> testIntrNOM = meb->getNOMInstance(getUserName(), L"EventReport");
	evtrpt::v_OriginatingEntity_FederateIdentifier_SiteID id = 7;
	testIntrNOM->setValue(L"OriginatingEntity.FederateIdentifier.SiteID", &id);
	evtrpt::v_EventType evtType = 101;
	testIntrNOM->setValue(L"EventType", &evtType);

	//using namespace intellival::SetData;
	//std::shared_ptr<NOM> testIntrNOM = meb->getNOMInstance(getUserName(), L"SetData");
	//OriginatingEntity_FederateIdentifier_SiteID id = 7;
	//testIntrNOM->setValue(L"OriginatingEntity.FederateIdentifier.SiteID", &id);
	//RequestIdentifier requestIdentifier = 101;
	//testIntrNOM->setValue(L"RequestIdentifier", &requestIdentifier);

	this->sendMsg(testIntrNOM);
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new CommandManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}