#pragma once
#include <nFramework/util/IniHandler.h>
#include "BarManager.h"
#include <map>
#include "BarManagerIntelliVal.h"

using namespace nframework::intellival;
namespace air = BaseEntity_PhysicalEntity_Platform_Aircraft;
namespace muni = BaseEntity_PhysicalEntity_Munition;

/**
* @ class: BarManager
* @ author : 하재희
* @ version: 1.0
* @ see also: BarHandler
* @ description: MEC 객체를 사용하기 위해 BaseManager 인터페이스를 사용받아 구현한 클래스
*
* @ date: 2023.11.4
*
**/

/************************************************************************
	constructor / destructor
************************************************************************/
BarManager::BarManager(void)
{
	initialize();
}

BarManager::~BarManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
BarManager::initialize(void)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " ;
	l.info(s);
	
	setUserName(L"BarManager");

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
BarManager::release()
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
BarManager::registerMsg(std::wstring msgName)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << msgName ;
	l.info(s);
	
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
BarManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);

}

void
BarManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	mec->updateMsg(nomMsg);
}

void
BarManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
}

void
BarManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void
BarManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	discoveredMsgMap.erase(nomMsg->getInstanceID());

}

void
BarManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);
	
	mec->sendMsg(nomMsg);
}

void
BarManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);

	if (nomMsg->getName() == L"BaseEntity.PhysicalEntity.Platform.Aircraft")
	{
		nomMsg->setValue(L"WorldLocation.X", &air::v_WorldLocation_X(1.0));
		auto x = air::t_WorldLocation_X(nomMsg->getValue(L"WorldLocation.X"));
	}
	else if (nomMsg->getName() == L"BaseEntity.PhysicalEntity.Munition")
	{
		nomMsg->setValue(L"AccelerationVector.XAcceleration", &muni::v_AccelerationVector_XAcceleration(1.0f));
		auto x = muni::t_AccelerationVector_XAcceleration(nomMsg->getValue(L"AccelerationVector.XAcceleration"));
	}
}


void
BarManager::setUserName(std::wstring userName)
{
	name = userName;
}

std::wstring
BarManager::getUserName()
{
	return name;
}

void
BarManager::setData(void* data)
{


}

bool
BarManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(L"BarManager/BarManager.ini"); // ※주의 작업디렉터리: Main.exe가 있는 경로

	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " ;
	l.info(s);

	return true;
}

bool
BarManager::stop()
{
	bool result = true;

	return result;
}

void
BarManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager * createObject()
{
	return new BarManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager * userManager)
{
	delete userManager;
}
