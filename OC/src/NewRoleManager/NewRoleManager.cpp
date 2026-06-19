#include "NewRoleManager.h"
#include "UIMessageEnum.h"
#include <cassert>
#include "NewRoleManagerIntelliVal.h"

/************************************************************************
	constructor / destructor
************************************************************************/
NewRoleManager::NewRoleManager(void)
{
	initialize();
}

NewRoleManager::~NewRoleManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
NewRoleManager::initialize(void)
{
	NewRoleManager::setUserName(L"NewRoleManager");
	uiTrackHandler = std::make_unique<UITrackHandler>(this);

	// design by contract
	mec = std::make_unique<MECComponent>();
	mec->setUser(this);
}

void
NewRoleManager::release()
{
	meb = nullptr;
	winHandle = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
NewRoleManager::registerMsg(std::wstring msgName)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << msgName ;
	l.info(s);

	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.emplace(nomMsg->getInstanceID(), nomMsg);
	return nomMsg;
}

void
NewRoleManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);

	discoveredMsg.emplace(nomMsg->getInstanceID(), nomMsg);
	if (nomMsg->getName() == L"BaseEntity.PhysicalEntity.Platform.Aircraft" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Munition" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Sensor" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Platform.SurfaceVessel" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Platform.GroundVehicle" ||
		nomMsg->getName() == L"Target")
	{
		nomMsg = uiTrackHandler->discoverUITrack(nomMsg);
	}

	if (winHandle != nullptr)
	{
		uint nomLen = 0;
		byte* nomBytes = nomMsg->serialize(nomLen);

		NOMInfo nomInfo;

		_tcscpy(nomInfo.MsgName, nomMsg->getName().c_str());
		nomInfo.MsgID = nomMsg->getMessageID();
		nomInfo.MsgInstanceID = nomMsg->getInstanceID();
		nomInfo.MsgLen = nomLen;

		::SendMessage(winHandle, WM_DISCOVERED_MSG_DATA, (WPARAM)&nomInfo, (LPARAM)nomBytes);

		delete[] nomBytes;
	}
}

void
NewRoleManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);

	nomMsg->setInstanceName(this->getUserName());
	mec->updateMsg(nomMsg);
}

void
NewRoleManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);

	/*if (nomMsg->getName() == L"AirThreatInformation") {
		auto objectCount = nomMsg->getValue(L"ObjectCount")->toUShort();
		tcout << __FUNCTIONW__ << L" " << objectCount ;
	}*/

	if (nomMsg->getName() == L"BaseEntity.PhysicalEntity.Platform.Aircraft" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Munition" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Sensor" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Platform.SurfaceVessel" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Platform.GroundVehicle" ||
		nomMsg->getName() == L"Target")
	{
		nomMsg = uiTrackHandler->reflectUITrack(nomMsg);
	}

	if (winHandle != nullptr && nomMsg != nullptr)
	{
		uint nomLen = 0;
		byte* nomBytes = nomMsg->serialize(nomLen);

		NOMInfo nomInfo;

		_tcscpy(nomInfo.MsgName, nomMsg->getName().c_str());
		nomInfo.MsgID = nomMsg->getMessageID();
		nomInfo.MsgInstanceID = nomMsg->getInstanceID();
		nomInfo.MsgLen = nomLen;

		::SendMessage(winHandle, WM_SEND_DATA, (WPARAM)&nomInfo, (LPARAM)nomBytes);

		delete[] nomBytes;
	}
}

void
NewRoleManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);

	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
NewRoleManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);

	discoveredMsg.erase(nomMsg->getInstanceID());
	if (nomMsg->getName() == L"BaseEntity.PhysicalEntity.Platform.Aircraft" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Munition" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Sensor" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Platform.SurfaceVessel" ||
		nomMsg->getName() == L"BaseEntity.PhysicalEntity.Platform.GroundVehicle" ||
		nomMsg->getName() == L"Target")
	{
		nomMsg = uiTrackHandler->removeUITrack(nomMsg);
	}

	if (winHandle != nullptr && nomMsg != nullptr)
	{
		uint nomLen = 0;
		byte* nomBytes = nomMsg->serialize(nomLen);

		NOMInfo nomInfo;

		_tcscpy(nomInfo.MsgName, nomMsg->getName().c_str());
		nomInfo.MsgID = nomMsg->getMessageID();
		nomInfo.MsgInstanceID = nomMsg->getInstanceID();
		nomInfo.MsgLen = nomLen;

		::SendMessage(winHandle, WM_REMOVED_MSG_DATA, (WPARAM)&nomInfo, (LPARAM)nomBytes);

		delete[] nomBytes;
	}
}

void
NewRoleManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);

	if (nomMsg->getName() == L"GUI_StartResume")
	{
		uiTrackHandler->startTimer();
	}

	if (nomMsg->getName() == L"GUI_StopFreeze")
	{
		uiTrackHandler->stopTimer();
	}

	mec->sendMsg(nomMsg);
}

void
NewRoleManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"[" << __FUNCTIONW__ << L"] " << nomMsg->getName() ;
	l.info(s);

	if (winHandle != nullptr)
	{
		uint nomLen = 0;
		byte* nomBytes = nomMsg->serialize(nomLen);

		NOMInfo nomInfo;

		_tcscpy(nomInfo.MsgName, nomMsg->getName().c_str());
		nomInfo.MsgID = nomMsg->getMessageID();
		nomInfo.MsgLen = nomLen;
		nomInfo.MsgInstanceID = nomMsg->getInstanceID();

		::SendMessage(winHandle, WM_SEND_DATA, (WPARAM)&nomInfo, (LPARAM)nomBytes);

		delete[] nomBytes;
	}
}

void
NewRoleManager::setUserName(std::wstring userName)
{
	managerName = userName;
}

std::wstring
NewRoleManager::getUserName()
{
	return managerName;
}

void
NewRoleManager::setData(void* data)
{
	this->winHandle = (HWND)data;
	assert("HWND == 0" && winHandle);
}

bool
NewRoleManager::start()
{
	return true;
}

bool
NewRoleManager::stop()
{
	this->winHandle = nullptr;
	return true;
}

void
NewRoleManager::setMEBComponent(IMEBComponent* realMEB)
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
	return new NewRoleManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}