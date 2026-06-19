#pragma once
#include "UIManager.h"

/**
 * @class  UIManager
 * @brief  WPF ↔ nFramework 브릿지
 *         - sendMsg(): WPF가 발행 요청한 NOM을 MEC로 버스 발행
 *         - recvMsg(): 내부 버스에서 수신된 NOM을 funcMap으로 분기
 */

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
}

void UIManager::funcMapInit()
{
	// 내부 버스에서 수신 가능한 메시지와 처리 함수 바인딩
	funcMap[_T("ATSStatus")]      = std::bind(&UIManager::onATSStatus,      this, std::placeholders::_1);
	funcMap[_T("RSSStatus")]      = std::bind(&UIManager::onRSSStatus,      this, std::placeholders::_1);
	funcMap[_T("MSSStatus")]      = std::bind(&UIManager::onMSSStatus,      this, std::placeholders::_1);
	funcMap[_T("MLSStatus")]      = std::bind(&UIManager::onMLSStatus,      this, std::placeholders::_1);
	funcMap[_T("TargetDetection")]= std::bind(&UIManager::onTargetDetection, this, std::placeholders::_1);
	funcMap[_T("TargetDestroyed")]= std::bind(&UIManager::onTargetDestroyed, this, std::placeholders::_1);
}

/************************************************************************
	BaseManager 순수 가상 함수 구현
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
}

void UIManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->updateMsg(nomMsg);
}

void UIManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
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
}

/**
 * @brief WPF(NOMHandler)가 호출 → 내부 MEC 버스로 메시지 발행
 *        (Scenario, StartSimulation, LaunchCommand 등 OC 송신 메시지)
 */
void UIManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

/**
 * @brief 내부 버스에서 수신된 메시지를 funcMap으로 분기
 *        (ATSStatus, RSSStatus 등 OC 수신 메시지)
 */
void UIManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	auto iter = funcMap.find(nomMsg->getName());
	if (iter != funcMap.end())
	{
		iter->second(nomMsg);
	}
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
	// 필요 시 외부 데이터 포인터 저장
}

bool UIManager::start()
{
	tcout << "[" << __FUNCTIONT__ << "] UIManager started." << std::endl;
	return true;
}

bool UIManager::stop()
{
	tcout << "[" << __FUNCTIONT__ << "] UIManager stopped." << std::endl;
	return true;
}

void UIManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	수신 메시지 처리 핸들러
	- 여기서 WPF로 이벤트를 전달하는 로직을 추가한다.
	- 현재는 콘솔 로그만 출력 (WPF 연동은 NOMHandler가 담당)
************************************************************************/
void UIManager::onATSStatus(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] ATSStatus received. name=" << nomMsg->getName() << std::endl;
	// WPF NOMHandler가 Subscribe로 자동 수신하므로 추가 처리 불필요
}

void UIManager::onRSSStatus(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] RSSStatus received." << std::endl;
}

void UIManager::onMSSStatus(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] MSSStatus received." << std::endl;
}

void UIManager::onMLSStatus(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] MLSStatus received." << std::endl;
}

void UIManager::onTargetDetection(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] TargetDetection received." << std::endl;
}

void UIManager::onTargetDestroyed(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[UIManager] TargetDestroyed received." << std::endl;
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