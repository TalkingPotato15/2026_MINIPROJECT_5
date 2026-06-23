#include "CommunicationManager.h"
#include <filesystem>
using namespace std::filesystem;

/************************************************************************
	Constructor / Destructor
************************************************************************/
CommunicationManager::CommunicationManager(void)
{
	init();
}

CommunicationManager::~CommunicationManager(void)
{
	release();
}

/************************************************************************f
	initialize / release
************************************************************************/
void
CommunicationManager::init()
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;
	setUserName(_T("CommunicationManager"));

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
CommunicationManager::release()
{
	delete commConfig;

	//socket issue
	//delete commInterface;

	meb = nullptr;
	delete mec;
	mec = nullptr;
}

/************************************************************************
	Inherit Function
************************************************************************/
shared_ptr<NOM>
CommunicationManager::registerMsg(tstring msgName)
{
	shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.insert(pair<unsigned int, shared_ptr<NOM>>(nomMsg->getInstanceID(), nomMsg));

	return nomMsg;
}

void
CommunicationManager::discoverMsg(shared_ptr<NOM> nomMsg)
{
	discoveredMsg.insert(pair<unsigned int, shared_ptr<NOM>>(nomMsg->getInstanceID(), nomMsg));
	commInterface->registerCommMsg(nomMsg);
}

void
CommunicationManager::updateMsg(shared_ptr<NOM> nomMsg)
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
CommunicationManager::reflectMsg(shared_ptr<NOM> nomMsg)
{
	tcout << _T("CommunicationManager::Message is reflected.") << endl;
	commInterface->updateCommMsg(nomMsg);
}

void
CommunicationManager::deleteMsg(shared_ptr<NOM> nomMsg)
{
	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
CommunicationManager::removeMsg(shared_ptr<NOM> nomMsg)
{
	map<unsigned int, shared_ptr<NOM>>::iterator itr;
	itr = discoveredMsg.find(nomMsg->getInstanceID());

	if (itr != discoveredMsg.end())
	{
		discoveredMsg.erase(nomMsg->getInstanceID());
	}
	else
	{
		tcerr << _T("CommunicationManager::Message was removed.") << endl;
	}
}

void
CommunicationManager::sendMsg(shared_ptr<NOM> nomMsg)
{
	//tcout << "[" << __FUNCTIONT__ << "] " << nomMsg->getMessageID() << std::endl;

	mec->sendMsg(nomMsg);
}

void
CommunicationManager::recvMsg(shared_ptr<NOM> nomMsg)
{
	if (auto iter = funcMap.find(nomMsg->getName()); iter != funcMap.end())
	{
		iter->second(nomMsg);
	}

	//commInterface->sendCommMsg(nomMsg);
}

void
CommunicationManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
CommunicationManager::getUserName()
{
	return name;
}

void
CommunicationManager::setData(void* data)
{
	// if need be
}

bool
CommunicationManager::start()
{
	tcout << "[" << __FUNCTIONT__ << "] " << std::endl;

	//socket issue
	commInterface = new NCommInterface(this);

	commInterface->setMEBComponent(meb);
	MessageProcessor msgProcessor = bind(&CommunicationManager::processRecvMessage, this, placeholders::_1, placeholders::_2);
	commConfig->setMsgProcessor(msgProcessor);
	bool initResult = commInterface->initNetEnv(commConfig);
	
	// 메시지 등록
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
CommunicationManager::stop()
{
	commInterface->releaseNetEnv(commConfig);

	//socket issue
	delete commInterface;
	return true;
}

void
CommunicationManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void
CommunicationManager::recvSendScenario(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerScenario"));

	nomMsg_new->setValue(_T("mlsPos.x"), &(NDouble)(nomMsg->getValue(_T("mlsPos.x"))->toDouble()));
	nomMsg_new->setValue(_T("mlsPos.y"), &(NDouble)(nomMsg->getValue(_T("mlsPos.y"))->toDouble()));
	nomMsg_new->setValue(_T("mlsPos.z"), &(NDouble)(nomMsg->getValue(_T("mlsPos.z"))->toDouble()));

	this->sendMsg(nomMsg_new);
}

void
CommunicationManager::recvStartSimulation(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerStartSimulation"));

	this->sendMsg(nomMsg_new);
}

void
CommunicationManager::recvStopSimulation(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerStop"));

	this->sendMsg(nomMsg_new);
}

void
CommunicationManager::recvLaunchCommand(shared_ptr<NOM> nomMsg)
{
	auto nomMsg_new = meb->getNOMInstance(name, _T("InnerLaunchCommand"));

	nomMsg_new->setValue(_T("targetID"), &(NUInteger)(nomMsg->getValue(_T("targetID"))->toUInt()));
	
	this->sendMsg(nomMsg_new);
}

void
CommunicationManager::recvInnerMLSStatus(shared_ptr<NOM> nomMsg)
{
	auto sendNewMsg = meb->getNOMInstance(name, _T("MLSStatus"));

	sendNewMsg->setValue(_T("Header.MessageID"), &NUShort(0x05));
	sendNewMsg->setValue(_T("Header.MessageLength"), &NUShort(28));

	sendNewMsg->setValue(_T("status"), &NUInteger(nomMsg->getValue(_T("status"))->toUInt()));
	sendNewMsg->setValue(_T("launcherInfo.missileStatus1"), &(NUInteger)(nomMsg->getValue(_T("launcherInfo.missileStatus1"))->toUInt()));
	sendNewMsg->setValue(_T("launcherInfo.missileStatus2"), &(NUInteger)(nomMsg->getValue(_T("launcherInfo.missileStatus2"))->toUInt()));
	sendNewMsg->setValue(_T("launcherInfo.missileStatus3"), &(NUInteger)(nomMsg->getValue(_T("launcherInfo.missileStatus3"))->toUInt()));
	sendNewMsg->setValue(_T("launcherInfo.missileStatus4"), &(NUInteger)(nomMsg->getValue(_T("launcherInfo.missileStatus4"))->toUInt()));
	sendNewMsg->setValue(_T("launcherInfo.missileStock"), &(NUInteger)(nomMsg->getValue(_T("launcherInfo.missileStock"))->toUInt()));

	tcout << _T("[CommunicationManager] Sending MLSStatus to network\n");
	commInterface->sendCommMsg(sendNewMsg);
}

void CommunicationManager::recvInnerIgnitionCommand(shared_ptr<NOM> nomMsg)
{
	auto sendNewMsg = meb->getNOMInstance(name, _T("IgnitionCommand"));

	NUShort messageID(0x0a);
	NUShort messageLength(36);
	NUInteger missileID(nomMsg->getValue(_T("missileID"))->toUInt());
	NUInteger targetID(nomMsg->getValue(_T("targetID"))->toUInt());
	NDouble launchPosX(nomMsg->getValue(_T("launchPos.x"))->toDouble());
	NDouble launchPosY(nomMsg->getValue(_T("launchPos.y"))->toDouble());
	NDouble launchPosZ(nomMsg->getValue(_T("launchPos.z"))->toDouble());

	sendNewMsg->setValue(_T("Header.MessageID"), &messageID);
	sendNewMsg->setValue(_T("Header.MessageLength"), &messageLength);
	sendNewMsg->setValue(_T("missileID"), &missileID);
	sendNewMsg->setValue(_T("targetID"), &targetID);
	sendNewMsg->setValue(_T("launchPos.x"), &launchPosX);
	sendNewMsg->setValue(_T("launchPos.y"), &launchPosY);
	sendNewMsg->setValue(_T("launchPos.z"), &launchPosZ);

	tcout << _T("[CommunicationManager] Sending IgnitionCommand to network\n");
	commInterface->sendCommMsg(sendNewMsg);
}

void 
CommunicationManager::funcMapInit()
{
	function<void(shared_ptr<NOM>)> msgProc;

	msgProc = bind(&CommunicationManager::recvSendScenario, this, placeholders::_1);
	funcMap.insert({ _T("Scenario"), msgProc });

	msgProc = bind(&CommunicationManager::recvStartSimulation, this, placeholders::_1);
	funcMap.insert({ _T("StartSimulation"), msgProc });

	msgProc = bind(&CommunicationManager::recvStopSimulation, this, placeholders::_1);
	funcMap.insert({ _T("Stop"), msgProc });

	msgProc = bind(&CommunicationManager::recvLaunchCommand, this, placeholders::_1);
	funcMap.insert({ _T("LaunchCommand"), msgProc });

	msgProc = bind(&CommunicationManager::recvInnerMLSStatus, this, placeholders::_1);
	funcMap.insert({ _T("InnerMLSStatus"), msgProc });

	msgProc = bind(&CommunicationManager::recvInnerIgnitionCommand, this, placeholders::_1);
	funcMap.insert({ _T("InnerIgnitionCommand"), msgProc });
}

void
CommunicationManager::sendInnerMsg(shared_ptr<NOM> nomMsg)
{
	if (auto iter = funcMap.find(nomMsg->getName()); iter != funcMap.end())
	{
		iter->second(nomMsg);
	}
}

void
CommunicationManager::processRecvMessage(unsigned char* data, int size)
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

	tstring msgName = commMsgHandler.getMsgName(msgID);
	if (msgName.empty())
	{
		/*tcout << _T("[CommunicationManager] Ignoring undefined message id: 0x")
			<< std::hex << msgID << std::dec
			<< _T(", size=") << size << std::endl;*/
		return;
	}

	auto nomMsg = meb->getNOMInstance(name, msgName);

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
CommunicationManager::getObjectInstanceID(shared_ptr<NOM> nomMsg)
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
	return new CommunicationManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}
