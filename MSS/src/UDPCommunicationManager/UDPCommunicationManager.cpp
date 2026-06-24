#include "UDPCommunicationManager.h"
#include <filesystem>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std::filesystem;

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
	tcout << _T("[COMM][CONFIG] local=") << commConfig->getLocalIPNumber()
		<< _T(":") << commConfig->getLocalPortNumber()
		<< _T(" remote=") << commConfig->getRemoteIPNumber()
		<< _T(":") << commConfig->getRemotePortNumber()
		<< _T(" multicast=") << commConfig->getMulticastIPNumber()
		<< _T(":") << commConfig->getMulticastPort()
		<< _T(" protocol=") << commConfig->getProtocolName()
		<< _T(" role=") << commConfig->getServerRole()
		<< _T(" cast=") << commConfig->getCastType() << endl;
	tcout << _T("[COMM][CONFIG] headerSize=") << commConfig->getHeaderSize()
		<< _T(" idPos=") << commConfig->getHeaderIDPos()
		<< _T(" idSize=") << commConfig->getHeaderIDSize()
		<< _T(" lengthPos=") << commConfig->getHeaderLengthPos()
		<< _T(" lengthSize=") << commConfig->getHeaderLengthSize() << endl;

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
			tcout << _T("[COMM][MAP] id=") << nMsg->getMessageID()
				<< _T(" name=") << nMsg->getName() << endl;
		}
	}
	else
	{
		tcerr << _T("[COMM][ERROR] Failed to parse UDPCommunicationManager.xml") << endl;
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
	if (!nomMsg.get())
	{
		tcerr << _T("[COMM][INNER TX][ERROR] null NOM") << endl;
		return;
	}
	tcout << _T("[COMM][INNER TX] name=") << nomMsg->getName()
		<< _T(" id=") << nomMsg->getMessageID()
		<< _T(" bytes=") << nomMsg->getLength() << endl;
	mec->sendMsg(nomMsg);
}

void UDPCommunicationManager::sendExternalMsg(shared_ptr<NOM> nomMsg, const tstring& reason)
{
	if (!nomMsg.get())
	{
		tcerr << _T("[COMM][TX][ERROR] null NOM, reason=") << reason << endl;
		return;
	}
	if (nomMsg->getName() != _T("MSSStatus"))
	{
		return;
	}

	unsigned int payloadLength = 0;
	if (auto value = nomMsg->getValue(_T("Header.MessageLength")))
	{
		payloadLength = value->toUInt();
	}

	std::wostringstream idStream;
	idStream << _T("0x") << std::uppercase << std::hex
		<< std::setw(2) << std::setfill(_T('0')) << nomMsg->getMessageID();
	tcout << _T("[COMM][TX] id=") << idStream.str()
		<< _T(" name=") << nomMsg->getName()
		<< _T(" payloadLength=") << payloadLength
		<< _T(" serializedBytes=") << nomMsg->getLength()
		<< _T(" reason=") << reason << endl;

	commInterface->sendCommMsg(nomMsg);
}

void
UDPCommunicationManager::recvMsg(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg.get())
	{
		tcerr << _T("[COMM][INNER RX][ERROR] null NOM") << endl;
		return;
	}

	tcout << _T("[COMM][INNER RX] name=") << nomMsg->getName()
		<< _T(" id=") << nomMsg->getMessageID()
		<< _T(" bytes=") << nomMsg->getLength() << endl;

	if (auto iter = funcMap.find(nomMsg->getName()); iter != funcMap.end())
	{
		iter->second(nomMsg);
	}
	else
	{
		// tcerr << _T("[COMM][INNER RX][WARN] no handler for ") << nomMsg->getName() << endl;
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
	const bool initialized = commInterface->initNetEnv(commConfig);
	if (initialized)
	{
		tcout << _T("[COMM][START] network initialization succeeded") << endl;
	}
	else
	{
		tcerr << _T("[COMM][START][ERROR] network initialization failed") << endl;
	}

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

	msgProc = bind(&UDPCommunicationManager::recvATSInformationUplink, this, placeholders::_1);
	funcMap.insert({ _T("ATSInformationUplink"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvIgnitionCommand, this, placeholders::_1);
	funcMap.insert({ _T("IgnitionCommand"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvMSSInterceptionResult, this, placeholders::_1);
	funcMap.insert({ _T("MSSInterceptionResult"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerSendScenarioAck, this, placeholders::_1);
	funcMap.insert({ _T("InnerSendScenarioAck"), msgProc });


	msgProc = bind(&UDPCommunicationManager::recvSendScenario, this, placeholders::_1);
	funcMap.insert({ _T("SendScenario"), msgProc});

	msgProc = bind(&UDPCommunicationManager::recvStartSimulation, this, placeholders::_1);
	funcMap.insert({ _T("StartSimulation"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvStop, this, placeholders::_1);
	funcMap.insert({ _T("Stop"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerStartSimulationAck, this, placeholders::_1);
	funcMap.insert({ _T("InnerStartSimulationAck"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerStopSimulationAck, this, placeholders::_1);
	funcMap.insert({ _T("InnerStopSimulationAck"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerSimulatorStateComm, this, placeholders::_1);
	funcMap.insert({ _T("SimulatorStateToComm"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerMSSStatusToComm, this, placeholders::_1);
	funcMap.insert({ _T("InnerMSSStatusToComm"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerRouteToComm, this, placeholders::_1);
	funcMap.insert({ _T("InnerRouteToComm"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerAirThreatInfo, this, placeholders::_1);
	funcMap.insert({ _T("InnerAirThreatInfoToComm"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvMissileDetonation, this, placeholders::_1);
	funcMap.insert({ _T("MissileDetonation"), msgProc });
}

void UDPCommunicationManager::recvScenario(shared_ptr<NOM> nomMsg)
{
	tcout << _T("[COMM][****BRIDGE****] Scenario -> InnerSendScenario") << endl;
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

	this->sendMsg(nomMsg_new);
}

void UDPCommunicationManager::recvATSInformationUplink(shared_ptr<NOM> nomMsg)
{
	auto targetId = nomMsg->getValue(_T("matchedTarget.targetId"));
	auto atsStatus = nomMsg->getValue(_T("matchedTarget.atsStatus"));
	tcout << _T("[COMM][****BRIDGE****] ATSInformationUplink -> InnerATSInformationToMSS targetId=")
		<< (targetId ? targetId->toUInt() : 0)
		<< _T(" atsStatus=") << (atsStatus ? atsStatus->toUInt() : 0) << endl;

	auto innerMsg = meb->getNOMInstance(name, _T("InnerATSInformationToMSS"));
	if (!innerMsg.get())
	{
		tcerr << _T("[UDPCommunicationManager] InnerATSInformationToMSS NOM is undefined.") << endl;
		return;
	}

	const tstring fields[] = {
		_T("ATSPos.x"), _T("ATSPos.y"), _T("ATSPos.z"),
		_T("speed"), _T("targetId"), _T("atsStatus")
	};
	for (const auto& field : fields)
	{
		auto value = nomMsg->getValue(_T("matchedTarget.") + field);
		if (value) innerMsg->setValue(_T("matchedTarget.") + field, value);
	}

	this->sendMsg(innerMsg);
}

void UDPCommunicationManager::recvIgnitionCommand(shared_ptr<NOM> nomMsg)
{
	auto missileId = nomMsg->getValue(_T("missileID"));
	auto targetId = nomMsg->getValue(_T("targetID"));
	tcout << _T("[COMM][****BRIDGE****] IgnitionCommand -> InnerIgnitionCommandToMSS missileID=")
		<< (missileId ? missileId->toUInt() : 0)
		<< _T(" targetID=") << (targetId ? targetId->toUInt() : 0) << endl;

	auto innerMsg = meb->getNOMInstance(name, _T("InnerIgnitionCommandToMSS"));
	if (!innerMsg.get())
	{
		tcerr << _T("[UDPCommunicationManager] InnerIgnitionCommandToMSS NOM is undefined.") << endl;
		return;
	}

	const tstring fields[] = {
		_T("missileID"), _T("targetID"),
		_T("launchPos.x"), _T("launchPos.y"), _T("launchPos.z")
	};
	for (const auto& field : fields)
	{
		auto value = nomMsg->getValue(field);
		if (value) innerMsg->setValue(field, value);
	}

	this->sendMsg(innerMsg);
}

void UDPCommunicationManager::recvMSSInterceptionResult(shared_ptr<NOM> nomMsg)
{
	auto innerMsg = meb->getNOMInstance(name, _T("InnerMSSInterceptionResultToMSS"));
	if (!innerMsg.get())
	{
		tcerr << _T("[UDPCommunicationManager] InnerMSSInterceptionResultToMSS NOM is undefined.") << endl;
		return;
	}

	const tstring fields[] = { _T("targetID"), _T("missionFlag") };
	for (const auto& field : fields)
	{
		auto value = nomMsg->getValue(field);
		if (value) innerMsg->setValue(field, value);
	}

	this->sendMsg(innerMsg);
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

	sendExternalMsg(nomMsg_new, _T("ATS status"));
}

void UDPCommunicationManager::recvInnerRouteToComm(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("sendRouteAT"));
	routeString = nomMsg->getValue(_T("RouteAT"))->toString();
	NUShort msgID(0x43);;
	NString route(routeString);

	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
	nomMsg_new->setValue(_T("RouteAT"), &route);

	sendExternalMsg(nomMsg_new, _T("ATS route"));
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
		tcout << _T("[COMM][****BRIDGE****] StartSimulation flag=0 -> InnerStopSimulation") << endl;
		recvStopSimulation(nomMsg);
		return;
	}

	tcout << _T("[COMM][****BRIDGE****] StartSimulation -> InnerStartSimulation flag=")
		<< (value ? value->toUInt() : 1) << endl;
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerStartSimulation"));

	this->sendMsg(nomMsg_new);
}

void UDPCommunicationManager::recvStop(shared_ptr<NOM> nomMsg)
{
	if (auto value = nomMsg->getValue(_T("stopFlag")))
	{
		if (value->toUInt() == 0)
		{
			tcout << _T("[COMM][****BRIDGE****] Stop ignored because stopFlag=0") << endl;
			return;
		}
	}

	tcout << _T("[COMM][****BRIDGE****] Stop -> InnerStopSimulation") << endl;
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
	tcout << _T("[UDPCommunicationManager] OC ICD has no SendScenarioAck message. Skip external send.") << endl;
}

void UDPCommunicationManager::recvInnerStartSimulationAck(shared_ptr<NOM> nomMsg)
{
	(void)nomMsg;
}

void UDPCommunicationManager::recvInnerStopSimulationAck(shared_ptr<NOM> nomMsg)
{
	(void)nomMsg;
}

void UDPCommunicationManager::recvInnerSimulatorStateComm(shared_ptr<NOM> nomMsg)
{
	tcout << _T("[UDPCommunicationManager] OC ICD has no ATSInformationUplink bridge yet. Skip external send.") << endl;
}

void UDPCommunicationManager::recvInnerMSSStatusToComm(shared_ptr<NOM> nomMsg)
{
	auto statusMsg = meb->getNOMInstance(name, _T("MSSStatus"));
	if (!statusMsg.get())
	{
		tcerr << _T("[UDPCommunicationManager] MSS output NOM is undefined.") << endl;
		return;
	}

	NUShort statusMsgID((ushort)ICD_MessageID::MSSStatus);
	NUShort statusMsgLength(148);
	statusMsg->setValue(_T("Header.MessageID"), &statusMsgID);
	statusMsg->setValue(_T("Header.MessageLength"), &statusMsgLength);

	NUInteger status(1);
	if (auto value = nomMsg->getValue(_T("status")))
	{
		status = NUInteger(value->toUInt());
	}
	tcout << _T("[COMM][MSS] status=") << status.toUInt();
	for (unsigned int i = 0; i < 4; ++i)
	{
		const tstring prefix = _T("missileInfo[") + std::to_wstring(i) + _T("].");
		auto missileId = nomMsg->getValue(prefix + _T("missileId"));
		auto targetId = nomMsg->getValue(prefix + _T("targetId"));
		auto missileStatus = nomMsg->getValue(prefix + _T("mssStatus"));
		tcout << _T(" [") << i
			<< _T(":mid=") << (missileId ? missileId->toUInt() : 0)
			<< _T(",tid=") << (targetId ? targetId->toUInt() : 0)
			<< _T(",state=") << (missileStatus ? missileStatus->toUInt() : 0)
			<< _T("]");
	}
	tcout << endl;
	statusMsg->setValue(_T("status"), &status);

	auto copyMissileInfo = [&](shared_ptr<NOM> destination)
	{
		for (unsigned int i = 0; i < 4; ++i)
		{
			const tstring prefix = _T("missileInfo[") + std::to_wstring(i) + _T("].");
			const tstring fields[] = {
				_T("targetId"), _T("missileId"),
				_T("MSSPos.x"), _T("MSSPos.y"), _T("MSSPos.z"), _T("mssStatus")
			};
			for (const auto& field : fields)
			{
				auto value = nomMsg->getValue(prefix + field);
				if (value) destination->setValue(prefix + field, value);
			}
		}
	};

	copyMissileInfo(statusMsg);
	sendExternalMsg(statusMsg, _T("periodic MSS status"));
}

void UDPCommunicationManager::sendInnerMsg(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg.get())
	{
		tcerr << _T("[COMM][DISPATCH][ERROR] null NOM") << endl;
		return;
	}

	if (auto iter = funcMap.find(nomMsg->getName()); iter != funcMap.end())
	{
		tcout << _T("[COMM][DISPATCH] handler found for ") << nomMsg->getName() << endl;
		iter->second(nomMsg);
	}
	else
	{
		// tcerr << _T("[COMM][DISPATCH][WARN] no handler for ") << nomMsg->getName() << endl;
	}
}

void
UDPCommunicationManager::processRecvMessage(unsigned char* data, int size)
{
	if (data == nullptr || size <= 0)
	{
		tcerr << _T("[COMM][RX][ERROR] empty packet data=")
			<< (data == nullptr ? _T("null") : _T("valid"))
			<< _T(" size=") << size << endl;
		return;
	}

	const auto headerSize = commConfig->getHeaderSize();
	auto IDPos = commConfig->getHeaderIDPos();
	auto IDSize = commConfig->getHeaderIDSize();
	auto lengthPos = commConfig->getHeaderLengthPos();
	auto lengthSize = commConfig->getHeaderLengthSize();

	if (size < static_cast<int>(headerSize))
	{
		tcerr << _T("[COMM][RX][ERROR] packet shorter than header packetBytes=")
			<< size << _T(" headerBytes=") << headerSize << endl;
		return;
	}
	if (IDPos + IDSize > static_cast<unsigned int>(size))
	{
		tcerr << _T("[COMM][RX][ERROR] message ID is outside packet idPos=")
			<< IDPos << _T(" idSize=") << IDSize << _T(" packetBytes=") << size << endl;
		return;
	}

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
		tcerr << _T("[COMM][RX][ERROR] unsupported ID_SIZE=") << IDSize << endl;
		return;
	}

	unsigned int declaredMessageLength = 0;
	if (lengthPos + lengthSize <= static_cast<unsigned int>(size))
	{
		if (lengthSize == 2)
		{
			unsigned short rawLength = 0;
			memcpy(&rawLength, data + lengthPos, lengthSize);
			declaredMessageLength = commConfig->getLengthBigEndian() ? ntohs(rawLength) : rawLength;
		}
		else if (lengthSize == 4)
		{
			unsigned int rawLength = 0;
			memcpy(&rawLength, data + lengthPos, lengthSize);
			declaredMessageLength = commConfig->getLengthBigEndian() ? ntohl(rawLength) : rawLength;
		}
	}

	const tstring msgName = commMsgHandler.getMsgName((unsigned short)msgID);
	const bool suppressStatusLog = msgName == _T("ATSStatus")
		|| msgName == _T("MLSStatus")
		|| msgName == _T("RSSStatus");
	std::wostringstream idStream;
	idStream << _T("0x") << std::uppercase << std::hex
		<< std::setw(2) << std::setfill(_T('0')) << msgID;
	if (!suppressStatusLog)
	{
		tcout << _T("[COMM][RX] id=") << idStream.str()
			<< _T(" name=") << (msgName.empty() ? _T("<unknown>") : msgName)
			<< _T(" packetBytes=") << size
			<< _T(" declaredMessageLength=") << declaredMessageLength << endl;
	}
	if (declaredMessageLength > 0 && declaredMessageLength != static_cast<unsigned int>(size))
	{
		tcerr << _T("[COMM][RX][WARN] header length mismatch: actual=") << size
			<< _T(" expected=") << declaredMessageLength << endl;
	}
	if (msgName.empty())
	{
		tcerr << _T("[COMM][RX][ERROR] unknown message ID ") << idStream.str() << endl;
		return;
	}

	auto nomMsg = meb->getNOMInstance(name, msgName);

	if (nomMsg.get())
	{
		if (nomMsg->getType() == nframework::nom::ENOMType::NOM_TYPE_OBJECT)
		{
			const bool decoded = nomMsg->deserialize(data, size);
			if (!decoded)
			{
				tcerr << _T("[COMM][RX][ERROR] deserialize failed for object ") << msgName << endl;
				return;
			}
			// tcout << _T("[COMM][RX] deserialize succeeded for object ") << msgName << endl;
			this->updateMsg(nomMsg);
		}
		else
		{
			auto nomMsgCP = nomMsg->clone();
			const bool decoded = nomMsgCP->deserialize(data, size);
			if (!decoded)
			{
				tcerr << _T("[COMM][RX][ERROR] deserialize failed for interaction ") << msgName << endl;
				return;
			}
			// tcout << _T("[COMM][RX] deserialize succeeded for interaction ") << msgName << endl;
			nomMsgCP->setOwner(name);
			sendInnerMsg(nomMsgCP);
			//this->sendMsg(nomMsgCP);
		}
	}
	else
	{
		tcerr << _T("[COMM][RX][ERROR] NOM instance is undefined for ") << msgName << endl;
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

