#include "UIManager.h"

#include "UIMessageEnum.h"

/************************************************************************
	Constructor / Destructor
************************************************************************/
UIManager::UIManager(void)
{
	initialize();
}

UIManager::~UIManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void UIManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("UIManager"));

	mec = new MECComponent;
	mec->setUser(this);

	funcMapInit();
}

void UIManager::release(void)
{
	funcMap.clear();
	delete mec;
	mec = nullptr;
	meb = nullptr;
	winHandle = nullptr;
}

void UIManager::funcMapInit()
{
	funcMap[_T("ATSStatus")] = std::bind(&UIManager::onATSStatus, this, std::placeholders::_1);
	funcMap[_T("RSSStatus")] = std::bind(&UIManager::onRSSStatus, this, std::placeholders::_1);
	funcMap[_T("MSSStatus")] = std::bind(&UIManager::onMSSStatus, this, std::placeholders::_1);
	funcMap[_T("MLSStatus")] = std::bind(&UIManager::onMLSStatus, this, std::placeholders::_1);
	funcMap[_T("TargetDetection")] = std::bind(&UIManager::onTargetDetection, this, std::placeholders::_1);
	funcMap[_T("TargetDestroyed")] = std::bind(&UIManager::onTargetDestroyed, this, std::placeholders::_1);
}

void UIManager::notifyGui(std::shared_ptr<NOM> nomMsg, UINT message)
{
	if (winHandle == nullptr || nomMsg == nullptr)
	{
		return;
	}

	uint nomLen = 0;
	byte* nomBytes = nomMsg->serialize(nomLen);
	if (nomBytes == nullptr)
	{
		return;
	}

	NOMInfo nomInfo;
	_tcsncpy_s(nomInfo.MsgName, _countof(nomInfo.MsgName), nomMsg->getName().c_str(), _TRUNCATE);
	nomInfo.MsgID = nomMsg->getMessageID();
	nomInfo.MsgInstanceID = nomMsg->getInstanceID();
	nomInfo.MsgLen = static_cast<int>(nomLen);

	::SendMessage(winHandle, message, (WPARAM)&nomInfo, (LPARAM)nomBytes);

	delete[] nomBytes;
}

/************************************************************************
	BaseManager inherited functions
************************************************************************/
std::shared_ptr<NOM> UIManager::registerMsg(tstring msgName)
{
	tcout << "[" << __FUNCTIONT__ << "] " << msgName << std::endl;
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
	return nomMsg;
}

void UIManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
	notifyGui(nomMsg, WM_DISCOVERED_MSG_DATA);
}

void UIManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void UIManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	notifyGui(nomMsg, WM_SEND_DATA);
}

void UIManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void UIManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	discoveredMsgMap.erase(nomMsg->getInstanceID());
	notifyGui(nomMsg, WM_REMOVED_MSG_DATA);
}

void UIManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void UIManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager::recvMsg] internal MEB delivered for GUI update: "
		<< nomMsg->getName() << std::endl;

	auto iter = funcMap.find(nomMsg->getName());
	if (iter != funcMap.end())
	{
		iter->second(nomMsg);
	}

	notifyGui(nomMsg, WM_SEND_DATA);
}

void UIManager::setUserName(tstring userName)
{
	name = userName;
}

tstring UIManager::getUserName()
{
	return name;
}

void UIManager::setData(void* data)
{
	winHandle = static_cast<HWND>(data);
}

bool UIManager::start()
{
	tcout << "[" << __FUNCTIONT__ << "] UIManager started." << std::endl;
	return true;
}

bool UIManager::stop()
{
	tcout << "[" << __FUNCTIONT__ << "] UIManager stopped." << std::endl;
	winHandle = nullptr;
	return true;
}

void UIManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	Message handlers
************************************************************************/
void UIManager::onATSStatus(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] ATSStatus delivered to GUI. name=" << nomMsg->getName() << std::endl;
}

void UIManager::onRSSStatus(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] RSSStatus delivered to GUI." << std::endl;
}

void UIManager::onMSSStatus(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] MSSStatus delivered to GUI." << std::endl;
}

void UIManager::onMLSStatus(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] MLSStatus delivered to GUI." << std::endl;
}

void UIManager::onTargetDetection(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] TargetDetection delivered to GUI." << std::endl;
}

void UIManager::onTargetDestroyed(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] TargetDestroyed delivered to GUI." << std::endl;
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new UIManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
