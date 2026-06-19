#include "UDPCommunicationManager.h"
#include <filesystem>
#include <cmath>
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

	msgProc = bind(&UDPCommunicationManager::recvStopSimulation, this, placeholders::_1);
	funcMap.insert({ _T("StopSimulation"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvStop, this, placeholders::_1);
	funcMap.insert({ _T("Stop"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvATSInterceptionResult, this, placeholders::_1);
	funcMap.insert({ _T("ATSInterceptionResult"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvMissionFailed, this, placeholders::_1);
	funcMap.insert({ _T("MissionFailed"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerStartSimulationAck, this, placeholders::_1);
	funcMap.insert({ _T("InnerStartSimulationAck"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerStopSimulationAck, this, placeholders::_1);
	funcMap.insert({ _T("InnerStopSimulationAck"), msgProc });

	msgProc = bind(&UDPCommunicationManager::recvInnerSimulatorStateComm, this, placeholders::_1);
	funcMap.insert({ _T("SimulatorStateToComm"), msgProc });

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

	NInteger status(1);
	NUInteger targetCount(1);
	nomMsg_new->setValue(_T("status"), &status);
	nomMsg_new->setValue(_T("targetCount"), &targetCount);

	NUInteger targetID(nomMsg->getValue(_T("AirThreatInfo.ObjectID"))->toUInt());
	nomMsg_new->setValue(_T("targetInfo[0].targetID"), &targetID);

	NDouble posX(nomMsg->getValue(_T("AirThreatInfo.PositionX"))->toDouble());
	nomMsg_new->setValue(_T("targetInfo[0].pos.x"), &posX);

	NDouble posY(nomMsg->getValue(_T("AirThreatInfo.PositionY"))->toDouble());
	nomMsg_new->setValue(_T("targetInfo[0].pos.y"), &posY);

	NDouble posZ(0.0);
	nomMsg_new->setValue(_T("targetInfo[0].pos.z"), &posZ);

	double velX = nomMsg->getValue(_T("AirThreatInfo.VelocityX"))->toDouble();
	double velY = nomMsg->getValue(_T("AirThreatInfo.VelocityY"))->toDouble();
	NUInteger speed((uint32_t)std::sqrt((velX * velX) + (velY * velY)));
	nomMsg_new->setValue(_T("targetInfo[0].speed"), &speed);

	NBool interceptionFlag(false);
	if (auto value = nomMsg->getValue(_T("AirThreatInfo.ObjectState")))
	{
		interceptionFlag = NBool(value->toUShort() == (ushort)TrackState::ATS_Detonation);
	}
	nomMsg_new->setValue(_T("targetInfo[0].interceptionFlag"), &interceptionFlag);

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
	if (auto value = nomMsg->getValue(_T("simulationStatus")))
	{
		if (!value->toByte())
		{
			recvStopSimulation(nomMsg);
			return;
		}
	}

	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerStartSimulation"));

	this->sendMsg(nomMsg_new);
}

void UDPCommunicationManager::recvStop(shared_ptr<NOM> nomMsg)
{
	recvStopSimulation(nomMsg);
}

void UDPCommunicationManager::recvATSInterceptionResult(shared_ptr<NOM> nomMsg)
{
	if (auto value = nomMsg->getValue(_T("interceptionFlag")))
	{
		if (!value->toByte())
		{
			return;
		}
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
		if (!value->toByte())
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
	tcout << _T("[UDPCommunicationManager] OC ICD has no StartSimulationAck message. Skip external send.") << endl;
}

void UDPCommunicationManager::recvInnerStopSimulationAck(shared_ptr<NOM> nomMsg)
{
	tcout << _T("[UDPCommunicationManager] OC ICD has no StopSimulationAck message. Skip external send.") << endl;
}

void UDPCommunicationManager::recvInnerSimulatorStateComm(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("SimulatorState"));
	NUShort msgID = NUShort((ushort)ICD_MessageID::SimulatorState);
	NUShort simulatorID = nomMsg->getValue(_T("SimulatorID"))->toUShort();

	nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
	nomMsg_new->setValue(_T("SimulatorID"), &simulatorID);

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

