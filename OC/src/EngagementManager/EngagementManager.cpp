#pragma once
#include "EngagementManager.h"

/************************************************************************
	Constructor / Destructor
************************************************************************/
EngagementManager::EngagementManager(void)
{
	initialize();
}

EngagementManager::~EngagementManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void EngagementManager::initialize(void)
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("EngagementManager"));

	mec = new MECComponent;
	mec->setUser(this);

	funcMapInit();
}

void EngagementManager::release(void)
{
	funcMap.clear();
	lastATSStatus.reset();
	lastMSSStatus.reset();
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

void EngagementManager::funcMapInit()
{
	funcMap[_T("ATSStatus")]      = std::bind(&EngagementManager::onATSStatus,      this, std::placeholders::_1);
	funcMap[_T("MSSStatus")]      = std::bind(&EngagementManager::onMSSStatus,      this, std::placeholders::_1);
	funcMap[_T("TargetDetection")]= std::bind(&EngagementManager::onTargetDetection, this, std::placeholders::_1);
	funcMap[_T("TargetDestroyed")]= std::bind(&EngagementManager::onTargetDestroyed, this, std::placeholders::_1);
}

/************************************************************************
	BaseManager 구현
************************************************************************/
std::shared_ptr<NOM> EngagementManager::registerMsg(tstring msgName)
{
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
	return nomMsg;
}

void EngagementManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	discoveredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
}

void EngagementManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void EngagementManager::reflectMsg(std::shared_ptr<NOM> nomMsg) {}

void EngagementManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->deleteMsg(nomMsg);
	registeredMsgMap.erase(nomMsg->getInstanceID());
}

void EngagementManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	discoveredMsgMap.erase(nomMsg->getInstanceID());
}

void EngagementManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;
	mec->sendMsg(nomMsg);
}

void EngagementManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	auto iter = funcMap.find(nomMsg->getName());
	if (iter != funcMap.end())
	{
		iter->second(nomMsg);
	}
}

void EngagementManager::setUserName(tstring userName) { name = userName; }
tstring EngagementManager::getUserName() { return name; }
void EngagementManager::setData(void* data) {}

bool EngagementManager::start()
{
	tcout << "[" << __FUNCTIONT__ << "] EngagementManager started." << std::endl;
	return true;
}

bool EngagementManager::stop()
{
	missionInProgress = false;
	tcout << "[" << __FUNCTIONT__ << "] EngagementManager stopped." << std::endl;
	return true;
}

void EngagementManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	수신 핸들러
************************************************************************/
/**
 * @brief ATSStatus 수신 → 캐시 저장 후 ATSInformationToRSS 릴레이
 */
void EngagementManager::onATSStatus(std::shared_ptr<NOM> nomMsg)
{
	lastATSStatus = nomMsg->clone();

	// ATSStatus의 위치 정보를 ATSInformationToRSS 형태로 RSS에 릴레이
	sendATSInformationToRSS();
}

/**
 * @brief MSSStatus 수신 → 캐시 저장 후 MSSInformationDownlinkToRSS 릴레이
 */
void EngagementManager::onMSSStatus(std::shared_ptr<NOM> nomMsg)
{
	lastMSSStatus = nomMsg->clone();

	if (missionInProgress)
	{
		sendMSSInformationDownlinkToRSS();
	}
}

/**
 * @brief TargetDetection 수신 → LaunchCommand 발행
 */
void EngagementManager::onTargetDetection(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[EngagementManager] TargetDetection received." << std::endl;

	// 탐지 성공 여부 확인 (toUInt() != 0 으로 bool 판별)
	NValueType* detectionVal = nomMsg->getValue(_T("targetDetectionSuccess"));
	bool detected = detectionVal ? (detectionVal->toUInt() != 0) : false;

	if (!detected) return;

	NValueType* idVal = nomMsg->getValue(_T("targetID"));
	unsigned int targetID = idVal ? static_cast<unsigned int>(idVal->toUInt()) : 0;

	missionInProgress = true;
	sendLaunchCommand(targetID);
}

/**
 * @brief TargetDestroyed 수신 → 요격 결과 메시지 발행
 */
void EngagementManager::onTargetDestroyed(std::shared_ptr<NOM> nomMsg)
{
	tcout << "[EngagementManager] TargetDestroyed received." << std::endl;

	NValueType* successVal = nomMsg->getValue(_T("missionSuccess"));
	bool success = successVal ? (successVal->toUInt() != 0) : false;

	missionInProgress = false;

	if (success)
	{
		// 요격 성공
		sendInterceptionResult(0, true);
	}
	else
	{
		// 임무 실패
		sendMissionFailed();
	}
}

/************************************************************************
	발행 헬퍼
************************************************************************/
void EngagementManager::sendATSInformationToRSS()
{
	if (!lastATSStatus || !meb) return;

	auto msg = meb->getNOMInstance(name, _T("ATSInformationToRSS"));
	if (!msg) return;

	NValueType* countVal = lastATSStatus->getValue(_T("targetCount"));
	if (countVal)
	{
		unsigned int count = static_cast<unsigned int>(countVal->toUInt());
		msg->setValue(_T("targetCount"), &NUInteger(count));

		for (unsigned int i = 0; i < count && i < 20; ++i)
		{
			auto srcID    = lastATSStatus->getValue(_T("targetInfo.targetID"),         i);
			auto srcX     = lastATSStatus->getValue(_T("targetInfo.pos.x"),            i);
			auto srcY     = lastATSStatus->getValue(_T("targetInfo.pos.y"),            i);
			auto srcZ     = lastATSStatus->getValue(_T("targetInfo.pos.z"),            i);
			auto srcSpeed = lastATSStatus->getValue(_T("targetInfo.speed"),            i);
			auto srcFlag  = lastATSStatus->getValue(_T("targetInfo.interceptionFlag"), i);

			if (srcID)    msg->setValue(_T("targetInfo.targetID"),         &NUInteger(srcID->toUInt()),   i);
			if (srcX)     msg->setValue(_T("targetInfo.pos.x"),            &NDouble(srcX->toDouble()),    i);
			if (srcY)     msg->setValue(_T("targetInfo.pos.y"),            &NDouble(srcY->toDouble()),    i);
			if (srcZ)     msg->setValue(_T("targetInfo.pos.z"),            &NDouble(srcZ->toDouble()),    i);
			if (srcSpeed) msg->setValue(_T("targetInfo.speed"),            &NUInteger(srcSpeed->toUInt()), i);
			// boolean 필드: NBool 사용, toUInt()!=0 으로 판별
			if (srcFlag)  msg->setValue(_T("targetInfo.interceptionFlag"), &NBool(srcFlag->toUInt() != 0), i);
		}
	}

	msg->setValue(_T("Header.MessageID"), &NUShort(0x07));
	msg->setValue(_T("Header.MessageLength"), &NUShort(2));
	mec->sendMsg(msg);
}

void EngagementManager::sendMSSInformationDownlinkToRSS()
{
	if (!lastMSSStatus || !meb) return;

	auto msg = meb->getNOMInstance(name, _T("MSSInformationDownlinkToRSS"));
	if (!msg) return;

	NValueType* countVal = lastMSSStatus->getValue(_T("missileCount"));
	if (countVal)
	{
		unsigned int count = static_cast<unsigned int>(countVal->toUInt());
		msg->setValue(_T("missileCount"), &NUInteger(count));

		for (unsigned int i = 0; i < count && i < 4; ++i)
		{
			auto srcMID  = lastMSSStatus->getValue(_T("missileInfo.missileID"),    i);
			auto srcTID  = lastMSSStatus->getValue(_T("missileInfo.targetID"),     i);
			auto srcX    = lastMSSStatus->getValue(_T("missileInfo.pos.x"),        i);
			auto srcY    = lastMSSStatus->getValue(_T("missileInfo.pos.y"),        i);
			auto srcZ    = lastMSSStatus->getValue(_T("missileInfo.pos.z"),        i);
			auto srcSt   = lastMSSStatus->getValue(_T("missileInfo.mssStatus"),    i);
			auto srcFlag = lastMSSStatus->getValue(_T("missileInfo.isIntercepted"), i);

			if (srcMID)  msg->setValue(_T("missileInfo.missileID"),     &NUInteger(srcMID->toUInt()),          i);
			if (srcTID)  msg->setValue(_T("missileInfo.targetID"),      &NUInteger(srcTID->toUInt()),          i);
			if (srcX)    msg->setValue(_T("missileInfo.pos.x"),         &NDouble(srcX->toDouble()),            i);
			if (srcY)    msg->setValue(_T("missileInfo.pos.y"),         &NDouble(srcY->toDouble()),            i);
			if (srcZ)    msg->setValue(_T("missileInfo.pos.z"),         &NDouble(srcZ->toDouble()),            i);
			if (srcSt)   msg->setValue(_T("missileInfo.mssStatus"),     &NInteger(srcSt->toInt()),             i);
			if (srcFlag) msg->setValue(_T("missileInfo.isIntercepted"),  &NBool(srcFlag->toUInt() != 0),       i);
		}
	}

	msg->setValue(_T("Header.MessageID"), &NUShort(0x0c));
	msg->setValue(_T("Header.MessageLength"), &NUShort(2));
	mec->sendMsg(msg);
}

void EngagementManager::sendLaunchCommand(unsigned int targetID)
{
	if (!meb) return;

	auto msg = meb->getNOMInstance(name, _T("LaunchCommand"));
	if (!msg) return;

	msg->setValue(_T("Header.MessageID"), &NUShort(0x09));
	msg->setValue(_T("Header.MessageLength"), &NUShort(2));
	msg->setValue(_T("targetID"),          &NUInteger(targetID));
	mec->sendMsg(msg);

	tcout << "[EngagementManager] LaunchCommand sent. targetID=" << targetID << std::endl;
}

void EngagementManager::sendInterceptionResult(unsigned int targetID, bool success)
{
	if (!meb) return;

	// ATS에 결과 전달
	auto msgATS = meb->getNOMInstance(name, _T("ATSInterceptionResult"));
	if (msgATS)
	{
		msgATS->setValue(_T("Header.MessageID"), &NUShort(0x0e));
		msgATS->setValue(_T("Header.MessageLength"), &NUShort(2));
		msgATS->setValue(_T("targetID"),         &NUInteger(targetID));
		msgATS->setValue(_T("interceptionFlag"), &NBool(success));   // NBoolean → NBool
		mec->sendMsg(msgATS);
	}

	// MSS에 결과 전달
	auto msgMSS = meb->getNOMInstance(name, _T("MSSInterceptionResult"));
	if (msgMSS)
	{
		msgMSS->setValue(_T("Header.MessageID"), &NUShort(0x0f));
		msgMSS->setValue(_T("Header.MessageLength"), &NUShort(2));
		msgMSS->setValue(_T("missileID"),        &NUInteger(0u));
		msgMSS->setValue(_T("isIntercepted"),    &NBool(success));   // NBoolean → NBool
		mec->sendMsg(msgMSS);
	}

	tcout << "[EngagementManager] InterceptionResult sent. success=" << success << std::endl;
}

void EngagementManager::sendMissionFailed()
{
	if (!meb) return;

	auto msg = meb->getNOMInstance(name, _T("MissionFailed"));
	if (!msg) return;

	msg->setValue(_T("Header.MessageID"), &NUShort(0x11));
	msg->setValue(_T("Header.MessageLength"), &NUShort(2));
	msg->setValue(_T("missionFlag"),      &NBool(true));   // NBoolean → NBool
	mec->sendMsg(msg);

	tcout << "[EngagementManager] MissionFailed sent." << std::endl;
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new EngagementManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
