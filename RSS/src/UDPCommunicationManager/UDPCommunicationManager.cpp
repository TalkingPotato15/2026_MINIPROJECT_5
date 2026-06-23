#include "UDPCommunicationManager.h"
#include <filesystem>
#include <cmath>
using namespace std::filesystem;

namespace
{
	void copyUIntValue(const shared_ptr<NOM>& src, const tstring& srcName, const shared_ptr<NOM>& dst, const tstring& dstName)
	{
		if (auto value = src->getValue(srcName))
		{
			NUInteger v(value->toUInt());
			dst->setValue(dstName, &v);
		}
	}

	void copyDoubleValue(const shared_ptr<NOM>& src, const tstring& srcName, const shared_ptr<NOM>& dst, const tstring& dstName)
	{
		if (auto value = src->getValue(srcName))
		{
			NDouble v(value->toDouble());
			dst->setValue(dstName, &v);
		}
	}

	void copyBoolValue(const shared_ptr<NOM>& src, const tstring& srcName, const shared_ptr<NOM>& dst, const tstring& dstName)
	{
		if (auto value = src->getValue(srcName))
		{
			NBool v(value->toUInt() != 0);
			dst->setValue(dstName, &v);
		}
	}

	void copyATSInformation(const shared_ptr<NOM>& src, const tstring& srcPrefix, const shared_ptr<NOM>& dst, const tstring& dstPrefix)
	{
		copyDoubleValue(src, srcPrefix + _T(".ATSPos.x"), dst, dstPrefix + _T(".ATSPos.x"));
		copyDoubleValue(src, srcPrefix + _T(".ATSPos.y"), dst, dstPrefix + _T(".ATSPos.y"));
		copyDoubleValue(src, srcPrefix + _T(".ATSPos.z"), dst, dstPrefix + _T(".ATSPos.z"));
		copyUIntValue(src, srcPrefix + _T(".speed"), dst, dstPrefix + _T(".speed"));
		copyUIntValue(src, srcPrefix + _T(".targetId"), dst, dstPrefix + _T(".targetId"));
		copyUIntValue(src, srcPrefix + _T(".atsStatus"), dst, dstPrefix + _T(".atsStatus"));
	}

	void copyMSSInformation(const shared_ptr<NOM>& src, const tstring& srcPrefix, const shared_ptr<NOM>& dst, const tstring& dstPrefix)
	{
		copyUIntValue(src, srcPrefix + _T(".targetId"), dst, dstPrefix + _T(".targetId"));
		copyUIntValue(src, srcPrefix + _T(".missileId"), dst, dstPrefix + _T(".missileId"));
		copyDoubleValue(src, srcPrefix + _T(".MSSPos.x"), dst, dstPrefix + _T(".MSSPos.x"));
		copyDoubleValue(src, srcPrefix + _T(".MSSPos.y"), dst, dstPrefix + _T(".MSSPos.y"));
		copyDoubleValue(src, srcPrefix + _T(".MSSPos.z"), dst, dstPrefix + _T(".MSSPos.z"));
		copyUIntValue(src, srcPrefix + _T(".mssStatus"), dst, dstPrefix + _T(".mssStatus"));
	}
	void logATSInformation(const tstring& label, const shared_ptr<NOM>& msg, const tstring& prefix, unsigned int index)
	{
		auto targetId = msg->getValue(prefix + _T(".targetId"));
		auto atsStatus = msg->getValue(prefix + _T(".atsStatus"));
		auto x = msg->getValue(prefix + _T(".ATSPos.x"));
		auto y = msg->getValue(prefix + _T(".ATSPos.y"));
		auto z = msg->getValue(prefix + _T(".ATSPos.z"));
		auto speed = msg->getValue(prefix + _T(".speed"));
		if (!targetId && !atsStatus && !x && !y && !z && !speed)
		{
			return;
		}

		tcout << _T("[UDPCommunicationManager] ") << label
			<< _T(": index=") << index
			<< _T(", targetId=") << (targetId ? targetId->toUInt() : 0)
			<< _T(", atsStatus=") << (atsStatus ? atsStatus->toUInt() : 0)
			<< _T(", pos=(") << (x ? x->toDouble() : 0.0)
			<< _T(", ") << (y ? y->toDouble() : 0.0)
			<< _T(", ") << (z ? z->toDouble() : 0.0) << _T(")")
			<< _T(", speed=") << (speed ? speed->toUInt() : 0) << endl;
	}

	void logMSSInformation(const tstring& label, const shared_ptr<NOM>& msg, const tstring& prefix, int index)
	{
		auto targetId = msg->getValue(prefix + _T(".targetId"));
		auto missileId = msg->getValue(prefix + _T(".missileId"));
		auto x = msg->getValue(prefix + _T(".MSSPos.x"));
		auto y = msg->getValue(prefix + _T(".MSSPos.y"));
		auto z = msg->getValue(prefix + _T(".MSSPos.z"));
		auto status = msg->getValue(prefix + _T(".mssStatus"));
		if (!targetId && !missileId && !x && !y && !z && !status)
		{
			return;
		}

		tcout << _T("[UDPCommunicationManager] ") << label
			<< _T(": index=") << index
			<< _T(", targetId=") << (targetId ? targetId->toUInt() : 0)
			<< _T(", missileId=") << (missileId ? missileId->toUInt() : 0)
			<< _T(", mssStatus=") << (status ? status->toUInt() : 0)
			<< _T(", pos=(") << (x ? x->toDouble() : 0.0)
			<< _T(", ") << (y ? y->toDouble() : 0.0)
			<< _T(", ") << (z ? z->toDouble() : 0.0) << _T(")") << endl;
	}
}

/************************************************************************
	Constructor / Destructor
************************************************************************/
UDPCommunicationManager::UDPCommunicationManager(void)
{
	init();
}

UDPCommunicationManager::~UDPCommunicationManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
UDPCommunicationManager::init()
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("UDPCommunicationManager"));

	// by contract
	mec = new MECComponent;
	mec->setUser(this);

	commConfig = new CommunicationConfig;
	commConfig->setIni(_T("CommLinkInfo.ini"));

	//socket issue
	//commInterface = new NCommInterface(this);

	//NOM 메시지 등록
	tstring schRegFilePath = current_path().c_str();
	schRegFilePath += _T("\\..\\SchemaRegistryData.xml");
	nomParser = std::make_unique<NOMParser>();
	nomParser->setNOMFile(schRegFilePath);

	nomParser->parseNote();
	auto noteMap = nomParser->getNoteMap();
	nomParser->parseDataType();
	auto dataTypeMap = nomParser->getDataTypeMap();

	//NOM 파싱 
	tstring nomFilePath = current_path().c_str();
	nomFilePath += _T("\\");
	nomFilePath += getUserName();
	nomFilePath += _T(".xml");
	nomParser->setNOMFile(nomFilePath);

	if (nomParser->parse(dataTypeMap, noteMap))
		//if (nomParser->parse())
	{
		list<NMessage*> msgList = nomParser->getMessageList();
		list<NMessage*>::iterator itr;
		for (itr = msgList.begin(); itr != msgList.end(); itr++)
		{
			NMessage* nMsg = *itr;
			commMsgHandler.setIDNameTable(nMsg->getMessageID(), nMsg->getName());
		}
	}

	funcMapInit();
}

void
UDPCommunicationManager::release()
{
	delete commConfig;

	//socket issue
	//delete commInterface;

	meb = nullptr;
	delete mec;
	mec = nullptr;

	funcMap.clear();
}

/************************************************************************
	Inherit Function
************************************************************************/
shared_ptr<NOM>
UDPCommunicationManager::registerMsg(tstring msgName)
{
	shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.insert(pair<unsigned int, shared_ptr<NOM>>(nomMsg->getInstanceID(), nomMsg));

	return nomMsg;
}

void
UDPCommunicationManager::discoverMsg(shared_ptr<NOM> nomMsg)
{
	discoveredMsg.insert(pair<unsigned int, shared_ptr<NOM>>(nomMsg->getInstanceID(), nomMsg));
	commInterface->registerCommMsg(nomMsg);
}

void
UDPCommunicationManager::updateMsg(shared_ptr<NOM> nomMsg)
{
	unsigned int oid = getObjectInstanceID(nomMsg);

	if (oid > 0)
	{
		nomMsg->setInstanceID(oid);
		mec->updateMsg(nomMsg);
	}
	else
	{
		printf("oid error:%u\n", oid);
	}
}

void
UDPCommunicationManager::reflectMsg(shared_ptr<NOM> nomMsg)
{
	tcout << _T("UDPCommunicationManager::Message is reflected.") << endl;
	commInterface->updateCommMsg(nomMsg);
}

void
UDPCommunicationManager::deleteMsg(shared_ptr<NOM> nomMsg)
{
	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
UDPCommunicationManager::removeMsg(shared_ptr<NOM> nomMsg)
{
	map<unsigned int, shared_ptr<NOM>>::iterator itr;
	itr = discoveredMsg.find(nomMsg->getInstanceID());

	if(itr != discoveredMsg.end())
	{
		discoveredMsg.erase(nomMsg->getInstanceID());
	}
	else
	{
		tcerr << _T("UDPCommunicationManager::Message was removed.") << endl;
	}
}

void
UDPCommunicationManager::sendMsg(shared_ptr<NOM> nomMsg)
{
	//tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() << std::endl;

	mec->sendMsg(nomMsg);
}

void
UDPCommunicationManager::recvMsg(shared_ptr<NOM> nomMsg)
{
	if (auto iter = funcMap.find(nomMsg->getName()); iter != funcMap.end())
	{
		iter->second(nomMsg);
	}

	//commInterface->sendCommMsg(nomMsg);
}

void
UDPCommunicationManager::setUserName(tstring userName)
{
	name = userName; 
}

tstring
UDPCommunicationManager::getUserName()
{
	return name;
}

void
UDPCommunicationManager::setData(void* data)
{
	// if need be
}

bool
UDPCommunicationManager::start()
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;

	//socket issue
	commInterface = new NCommInterface(this);
	
	commInterface->setMEBComponent(meb);
	MessageProcessor msgProcessor = bind(&UDPCommunicationManager::processRecvMessage, this, placeholders::_1, placeholders::_2);
	commConfig->setMsgProcessor(msgProcessor);
	commInterface->initNetEnv(commConfig);

	//메시지 등록
	list<NMessage*> msgList = nomParser->getObjectList();
	list<NMessage*>::iterator itr;
	for (itr = msgList.begin(); itr != msgList.end(); itr++)
	{
		NMessage* nMsg = *itr;
		if (nMsg->getSharing() == ESharing::ENUM_SHARING_PUBLISHSUBSCRIBE || nMsg->getSharing() == ESharing::ENUM_SHARING_PUBLISH)
		{
			this->registerMsg(nMsg->getName());
		}
	}

	return true;
}

bool
UDPCommunicationManager::stop()
{
	commInterface->releaseNetEnv(commConfig);

	//socket issue
	delete commInterface;
	return true;
}

void
UDPCommunicationManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void UDPCommunicationManager::funcMapInit()
{
	function<void(shared_ptr<NOM>)> msgProc;

	msgProc = bind(&UDPCommunicationManager::recvScenario, this, placeholders::_1);
	funcMap.insert({ _T("Scenario"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerSendScenarioAck, this, placeholders::_1);
	funcMap.insert({ _T("InnerSendScenarioAck"), msgProc });


	msgProc = bind(&UDPCommunicationManager::recvSendScenario, this, placeholders::_1);
	funcMap.insert({ _T("SendScenario"), msgProc});

	msgProc = bind(&UDPCommunicationManager::recvStartSimulation, this, placeholders::_1);
	funcMap.insert({ _T("StartSimulation"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvStop, this, placeholders::_1);
	funcMap.insert({ _T("Stop"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvATSInterceptionResult, this, placeholders::_1);
	funcMap.insert({ _T("ATSInterceptionResult"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerStartSimulationAck, this, placeholders::_1);
	funcMap.insert({ _T("InnerStartSimulationAck"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerStopSimulationAck, this, placeholders::_1);
	funcMap.insert({ _T("InnerStopSimulationAck"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerSimulatorStateComm, this, placeholders::_1);
	funcMap.insert({ _T("SimulatorStateToComm"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerRSSStatusToComm, this, placeholders::_1);
	funcMap.insert({ _T("InnerRSSStatusToComm"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvATSInformationToRSS, this, placeholders::_1);
	funcMap.insert({ _T("ATSInformationToRSS"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvMSSInformationDownlinkToRSS, this, placeholders::_1);
	funcMap.insert({ _T("MSSInformationDownlinkToRSS"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerTargetDetectionToComm, this, placeholders::_1);
	funcMap.insert({ _T("InnerTargetDetectionToComm"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerTargetDestroyedToComm, this, placeholders::_1);
	funcMap.insert({ _T("InnerTargetDestroyedToComm"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerATSInformationUplinkToComm, this, placeholders::_1);
	funcMap.insert({ _T("InnerATSInformationUplinkToComm"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerRouteToComm, this, placeholders::_1);
	funcMap.insert({ _T("InnerRouteToComm"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerAirThreatInfo, this, placeholders::_1);
	funcMap.insert({ _T("InnerAirThreatInfoToComm"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvMissileDetonation, this, placeholders::_1);
	funcMap.insert({ _T("MissileDetonation"), msgProc });
}

void UDPCommunicationManager::recvScenario(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerSendScenario"));
	if (!nomMsg_new.get())
	{
		tcerr << _T("[UDPCommunicationManager] InnerSendScenario NOM is undefined.") << endl;
		return;
	}

	NDouble zero(0.0);
	nomMsg_new->setValue(_T("Scenario.OriginLat"), &zero);
	nomMsg_new->setValue(_T("Scenario.OriginLng"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint0_X"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint0_Y"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint1_X"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint1_Y"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint2_X"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint2_Y"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint3_X"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint3_Y"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint0_Lat"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint0_Lng"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint1_Lat"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint1_Lng"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint2_Lat"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint2_Lng"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint3_Lat"), &zero);
	nomMsg_new->setValue(_T("Scenario.WayPoint3_Lng"), &zero);

	if (auto value = nomMsg->getValue(_T("rssPos.x")))
	{
		NDouble v(value->toDouble());
		nomMsg_new->setValue(_T("Scenario.RadarPositionX"), &v);
	}
	if (auto value = nomMsg->getValue(_T("rssPos.y")))
	{
		NDouble v(value->toDouble());
		nomMsg_new->setValue(_T("Scenario.RadarPositionY"), &v);
	}
	if (auto value = nomMsg->getValue(_T("mlsPos.x")))
	{
		NDouble v(value->toDouble());
		nomMsg_new->setValue(_T("Scenario.LauncherPositionX"), &v);
	}
	if (auto value = nomMsg->getValue(_T("mlsPos.y")))
	{
		NDouble v(value->toDouble());
		nomMsg_new->setValue(_T("Scenario.LauncherPositionY"), &v);
	}

	auto detectionAreaMsg = meb->getNOMInstance(name, _T("InnerRSSDetectionAreaToRSS"));
	if (detectionAreaMsg.get())
	{
		copyDoubleValue(nomMsg, _T("rssPos.x"), detectionAreaMsg, _T("rssPos.x"));
		copyDoubleValue(nomMsg, _T("rssPos.y"), detectionAreaMsg, _T("rssPos.y"));
		copyDoubleValue(nomMsg, _T("rssPos.z"), detectionAreaMsg, _T("rssPos.z"));
		copyUIntValue(nomMsg, _T("rssRadius"), detectionAreaMsg, _T("rssRadius"));
		this->sendMsg(detectionAreaMsg);
	}
	else
	{
		tcerr << _T("[UDPCommunicationManager] InnerRSSDetectionAreaToRSS NOM is undefined.") << endl;
	}

	this->sendMsg(nomMsg_new);
}

void UDPCommunicationManager::recvMissileDetonation(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerAirThreatDetonationToATM"));
	mec->sendMsg(nomMsg_new);
	//std::cout << "\n\n\n\nUDP에서 미사일 폭파 이벤트 수신\n\n\n" << std::endl;
}

void UDPCommunicationManager::recvInnerAirThreatInfo(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("ATSStatus"));
	if (!nomMsg_new.get())
	{
		tcerr << _T("[UDPCommunicationManager] ATSStatus NOM is undefined.") << endl;
		return;
	}

	NUShort msgID((ushort)ICD_MessageID::ATSStatus);
	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);

	NUInteger status(1);
	nomMsg_new->setValue(_T("status"), &status);

	NUInteger targetID(nomMsg->getValue(_T("AirThreatInfo.ObjectID"))->toUInt());
	nomMsg_new->setValue(_T("targetInfo[0].targetId"), &targetID);

	NDouble posX(nomMsg->getValue(_T("AirThreatInfo.PositionX"))->toDouble());
	nomMsg_new->setValue(_T("targetInfo[0].ATSPos.x"), &posX);

	NDouble posY(nomMsg->getValue(_T("AirThreatInfo.PositionY"))->toDouble());
	nomMsg_new->setValue(_T("targetInfo[0].ATSPos.y"), &posY);

	NDouble posZ(0.0);
	nomMsg_new->setValue(_T("targetInfo[0].ATSPos.z"), &posZ);

	double velX = nomMsg->getValue(_T("AirThreatInfo.VelocityX"))->toDouble();
	double velY = nomMsg->getValue(_T("AirThreatInfo.VelocityY"))->toDouble();
	NUInteger speed((uint32_t)std::sqrt((velX * velX) + (velY * velY)));
	nomMsg_new->setValue(_T("targetInfo[0].speed"), &speed);

	NUInteger atsStatus(1);
	if (auto value = nomMsg->getValue(_T("AirThreatInfo.ObjectState")))
	{
		atsStatus = NUInteger(value->toUInt());
	}
	nomMsg_new->setValue(_T("targetInfo[0].atsStatus"), &atsStatus);

	logATSInformation(_T("Sending ATSStatus"), nomMsg_new, _T("targetInfo[0]"), 0);
	commInterface->sendCommMsg(nomMsg_new);
}

void UDPCommunicationManager::recvInnerRouteToComm(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("sendRouteAT"));
	routeString = nomMsg->getValue(_T("RouteAT"))->toString();
	NUShort msgID(0x43);;
	NString route(routeString);

	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
	nomMsg_new->setValue(_T("RouteAT"), &route);

	commInterface->sendCommMsg(nomMsg_new);
}

void UDPCommunicationManager::recvSendScenario(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerSendScenario"));

	nomMsg_new->setValue(_T("Scenario.OriginLat"), &(NDouble)(nomMsg->getValue(_T("Scenario.OriginLat"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.OriginLng"), &(NDouble)(nomMsg->getValue(_T("Scenario.OriginLng"))->toDouble()));

	nomMsg_new->setValue(_T("Scenario.WayPoint0_X"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint0_X"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint0_Y"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint0_Y"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint1_X"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint1_X"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint1_Y"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint1_Y"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint2_X"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint2_X"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint2_Y"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint2_Y"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint3_X"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint3_X"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint3_Y"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint3_Y"))->toDouble()));

	nomMsg_new->setValue(_T("Scenario.WayPoint0_Lat"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint0_Lat"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint0_Lng"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint0_Lng"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint1_Lat"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint1_Lat"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint1_Lng"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint1_Lng"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint2_Lat"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint2_Lat"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint2_Lng"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint2_Lng"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint3_Lat"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint3_Lat"))->toDouble()));
	nomMsg_new->setValue(_T("Scenario.WayPoint3_Lng"), &(NDouble)(nomMsg->getValue(_T("Scenario.WayPoint3_Lng"))->toDouble()));

	this->sendMsg(nomMsg_new);
}

void UDPCommunicationManager::recvStartSimulation(shared_ptr<NOM> nomMsg)
{
	auto value = nomMsg->getValue(_T("startFlag"));
	if (!value)
	{
		value = nomMsg->getValue(_T("simulationStatus"));
	}

	if (value && value->toUInt() == 0)
	{
		recvStopSimulation(nomMsg);
		return;
	}

	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerStartSimulation"));

	this->sendMsg(nomMsg_new);
}

void UDPCommunicationManager::recvStop(shared_ptr<NOM> nomMsg)
{
	if (auto value = nomMsg->getValue(_T("stopFlag")))
	{
		if (value->toUInt() == 0)
		{
			return;
		}
	}

	recvStopSimulation(nomMsg);
}

void UDPCommunicationManager::recvATSInterceptionResult(shared_ptr<NOM> nomMsg)
{
	auto value = nomMsg->getValue(_T("missionFlag"));
	if (!value)
	{
		value = nomMsg->getValue(_T("interceptionFlag"));
	}

	if (value && value->toUInt() == 0)
	{
		return;
	}

	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerAirThreatDetonationToATM"));
	if (!nomMsg_new.get())
	{
		tcerr << _T("[UDPCommunicationManager] InnerAirThreatDetonationToATM NOM is undefined.") << endl;
		return;
	}

	mec->sendMsg(nomMsg_new);
}

void UDPCommunicationManager::recvMissionFailed(shared_ptr<NOM> nomMsg)
{
	if (auto value = nomMsg->getValue(_T("missionFlag")))
	{
		if (value->toUInt() == 0)
		{
			return;
		}
	}

	recvStopSimulation(nomMsg);
}

void UDPCommunicationManager::recvStopSimulation(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerStopSimulation"));

	this->sendMsg(nomMsg_new);
}

void UDPCommunicationManager::recvInnerSendScenarioAck(shared_ptr<NOM> nomMsg)
{
	(void)nomMsg;
	tcout << _T("[UDPCommunicationManager] SendScenarioAck received.") << endl;
}

void UDPCommunicationManager::recvInnerStartSimulationAck(shared_ptr<NOM> nomMsg)
{
	(void)nomMsg;
	tcout << _T("[UDPCommunicationManager] StartSimulationAck received.") << endl;
}

void UDPCommunicationManager::recvInnerStopSimulationAck(shared_ptr<NOM> nomMsg)
{
	(void)nomMsg;
	tcout << _T("[UDPCommunicationManager] StopSimulationAck received.") << endl;
}

void UDPCommunicationManager::recvInnerSimulatorStateComm(shared_ptr<NOM> nomMsg)
{
	(void)nomMsg;
}

void UDPCommunicationManager::recvInnerRSSStatusToComm(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("RSSStatus"));
	if (!nomMsg_new.get())
	{
		tcerr << _T("[UDPCommunicationManager] RSSStatus NOM is undefined.") << endl;
		return;
	}

	NUShort msgID = NUShort((ushort)ICD_MessageID::RSSStatus);
	NUInteger status(1);
	if (auto value = nomMsg->getValue(_T("status")))
	{
		status = NUInteger(value->toUInt());
	}

	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
	nomMsg_new->setValue(_T("status"), &status);

	auto statusValue = nomMsg_new->getValue(_T("status"));
	tcout << _T("[UDPCommunicationManager] Sending RSSStatus: status=") << (statusValue ? statusValue->toUInt() : 0) << endl;
	commInterface->sendCommMsg(nomMsg_new);
}

void UDPCommunicationManager::recvATSInformationToRSS(shared_ptr<NOM> nomMsg)
{
	tcout << _T("[UDPCommunicationManager] ATSInformationToRSS received.") << endl;

	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerATSInformationToRSS"));
	if (!nomMsg_new.get())
	{
		tcerr << _T("[UDPCommunicationManager] InnerATSInformationToRSS NOM is undefined.") << endl;
		return;
	}

	for (unsigned int i = 0; i < 4; ++i)
	{
		tstring index = _T("[") + to_tstring(i) + _T("]");
		copyATSInformation(nomMsg, _T("targetInfo") + index, nomMsg_new, _T("targetInfo") + index);
		logATSInformation(_T("Publishing InnerATSInformationToRSS"), nomMsg_new, _T("targetInfo") + index, i);
	}

	this->sendMsg(nomMsg_new);
}

void UDPCommunicationManager::recvMSSInformationDownlinkToRSS(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerMSSInformationToRSS"));
	if (!nomMsg_new.get())
	{
		tcerr << _T("[UDPCommunicationManager] InnerMSSInformationToRSS NOM is undefined.") << endl;
		return;
	}

	for (int i = 0; i < 4; ++i)
	{
		tstring index = _T("[") + to_tstring(i) + _T("]");
		copyMSSInformation(nomMsg, _T("missileInfo") + index, nomMsg_new, _T("missileInfo") + index);
		logMSSInformation(_T("Publishing InnerMSSInformationToRSS"), nomMsg_new, _T("missileInfo") + index, i);
	}

	this->sendMsg(nomMsg_new);
}

void UDPCommunicationManager::recvInnerTargetDetectionToComm(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("TargetDetection"));
	if (!nomMsg_new.get())
	{
		tcerr << _T("[UDPCommunicationManager] TargetDetection NOM is undefined.") << endl;
		return;
	}

	NUShort msgID((ushort)ICD_MessageID::TargetDetection);
	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
	copyUIntValue(nomMsg, _T("targetID"), nomMsg_new, _T("targetID"));
	copyUIntValue(nomMsg, _T("targetDetectonSuccess"), nomMsg_new, _T("targetDetectonSuccess"));

	auto targetId = nomMsg_new->getValue(_T("targetID"));
	auto success = nomMsg_new->getValue(_T("targetDetectonSuccess"));
	tcout << _T("[UDPCommunicationManager] Sending TargetDetection: targetID=") << (targetId ? targetId->toUInt() : 0)
		<< _T(", targetDetectonSuccess=") << (success ? success->toUInt() : 0) << endl;
	commInterface->sendCommMsg(nomMsg_new);
}

void UDPCommunicationManager::recvInnerTargetDestroyedToComm(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("TargetDestroyed"));
	if (!nomMsg_new.get())
	{
		tcerr << _T("[UDPCommunicationManager] TargetDestroyed NOM is undefined.") << endl;
		return;
	}

	NUShort msgID((ushort)ICD_MessageID::TargetDestroyed);
	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
	copyUIntValue(nomMsg, _T("targetID"), nomMsg_new, _T("targetID"));
	copyUIntValue(nomMsg, _T("missionFlag"), nomMsg_new, _T("missionFlag"));

	auto targetId = nomMsg_new->getValue(_T("targetID"));
	auto missionFlag = nomMsg_new->getValue(_T("missionFlag"));
	tcout << _T("[UDPCommunicationManager] Sending TargetDestroyed: targetID=") << (targetId ? targetId->toUInt() : 0)
		<< _T(", missionFlag=") << (missionFlag ? missionFlag->toUInt() : 0) << endl;
	commInterface->sendCommMsg(nomMsg_new);
}

void UDPCommunicationManager::recvInnerATSInformationUplinkToComm(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("ATSInformationUplink"));
	if (!nomMsg_new.get())
	{
		tcerr << _T("[UDPCommunicationManager] ATSInformationUplink NOM is undefined.") << endl;
		return;
	}

	NUShort msgID((ushort)ICD_MessageID::ATSInformationUplink);
	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
	copyATSInformation(nomMsg, _T("matchedTarget"), nomMsg_new, _T("matchedTarget"));
	logATSInformation(_T("Sending ATSInformationUplink"), nomMsg_new, _T("matchedTarget"), 0);

	commInterface->sendCommMsg(nomMsg_new);
}

void UDPCommunicationManager::sendInnerMsg(shared_ptr<NOM> nomMsg)
{
	if (auto iter = funcMap.find(nomMsg->getName()); iter != funcMap.end())
	{
		iter->second(nomMsg);
	}
}

void
UDPCommunicationManager::processRecvMessage(unsigned char* data, int size)
{
	//auto HeaderSize = commConfig->getHeaderSize();
	auto IDPos = commConfig->getHeaderIDPos();
	auto IDSize = commConfig->getHeaderIDSize();

	auto msgID = 0;

	//ID 형식이 short 또는 int인 경우만 처리
	if (IDSize == 2)
	{
		unsigned short tmpMsgID = 0;
		memcpy(&tmpMsgID, data + IDPos, IDSize);
		msgID = ntohs(tmpMsgID);
	}
	else
	{
		return;
	}

	//unsigned short tmpMsgID = 0;
	//memcpy(&tmpMsgID, data + IDPos, IDPos);
	//auto msgID = ntohs(tmpMsgID);

	auto nomMsg = meb->getNOMInstance(name, commMsgHandler.getMsgName(msgID));

	if (nomMsg.get())
	{
		if (nomMsg->getType() == nframework::nom::ENOMType::NOM_TYPE_OBJECT)
		{
			nomMsg->deserialize(data, size);
			this->updateMsg(nomMsg);
		}
		else
		{
			auto nomMsgCP = nomMsg->clone();
			nomMsgCP->deserialize(data, size);
			nomMsgCP->setOwner(name);
			sendInnerMsg(nomMsgCP);
			//this->sendMsg(nomMsgCP);
		}
	}
	else
	{
		tcerr << _T("undefined message") << endl;
	}
}

unsigned int
UDPCommunicationManager::getObjectInstanceID(shared_ptr<NOM> nomMsg)
{
	unsigned int oid = 0;
	map<unsigned int, shared_ptr<NOM>>::iterator itr;
	for (itr = registeredMsg.begin(); itr != registeredMsg.end(); itr++)
	{
		unsigned int key = itr->first;
		shared_ptr<NOM> nom = itr->second;

		if (nom->getMessageID() == nomMsg->getMessageID())
		{
			printf("[TCPCommunicationManager]Found object instance id : %u\n", key);
			oid = key;
			break;
		}
	}

	return oid;
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new UDPCommunicationManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}

