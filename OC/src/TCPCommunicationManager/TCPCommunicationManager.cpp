#include "TCPCommunicationManager.h"
#include <filesystem>
#include <sstream>
#include "TCPCommunicationManagerIntelliVal.h"

using namespace std::filesystem;
/************************************************************************
	Constructor / Destructor
************************************************************************/
TCPCommunicationManager::TCPCommunicationManager(void)
{
	init();
}

TCPCommunicationManager::~TCPCommunicationManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
TCPCommunicationManager::init()
{
	setUserName(L"TCPCommunicationManager");

	// by contract
	mec = new MECComponent;
	mec->setUser(this);

	commConfig = new CommunicationConfig;
	commConfig->setIni(L"CommLinkInfo.ini");

	//socket issue
	//commInterface = new NCommInterface(this);

	//NOM 메시지 등록
	std::wstring schRegFilePath = current_path().c_str();
	schRegFilePath += L"\\..\\SchemaRegistryData.xml";
	nomParser = std::make_unique<NOMParser>();
	nomParser->setNOMFile(schRegFilePath);

	nomParser->parseNote();
	auto noteMap = nomParser->getNoteMap();
	nomParser->parseDataType();
	auto dataTypeMap = nomParser->getDataTypeMap();

	//NOM 파싱 
	std::wstring nomFilePath = current_path().c_str();
	nomFilePath += L"\\";
	nomFilePath += getUserName();
	nomFilePath += L".xml";
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
}

void
TCPCommunicationManager::release()
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
TCPCommunicationManager::registerMsg(std::wstring msgName)
{
	std::wstringstream s; s << L"TCPCommunicationManager::Message is registered." ;
	l.info(s);
	shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.insert(pair<unsigned int, shared_ptr<NOM>>(nomMsg->getInstanceID(), nomMsg));

	return nomMsg;
}

void
TCPCommunicationManager::discoverMsg(shared_ptr<NOM> nomMsg)
{
	discoveredMsg.insert(pair<unsigned int, shared_ptr<NOM>>(nomMsg->getInstanceID(), nomMsg));
	commInterface->registerCommMsg(nomMsg);
}

void
TCPCommunicationManager::updateMsg(shared_ptr<NOM> nomMsg)
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
TCPCommunicationManager::reflectMsg(shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"TCPCommunicationManager::Message is reflected." ;
	l.info(s);
	commInterface->updateCommMsg(nomMsg);
}

void
TCPCommunicationManager::deleteMsg(shared_ptr<NOM> nomMsg)
{
	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
TCPCommunicationManager::removeMsg(shared_ptr<NOM> nomMsg)
{
	map<unsigned int, shared_ptr<NOM>>::iterator itr;
	itr = discoveredMsg.find(nomMsg->getInstanceID());

	if (itr != discoveredMsg.end())
	{
		discoveredMsg.erase(nomMsg->getInstanceID());
	}
	else
	{
		std::wstringstream s; s << L"TCPCommunicationManager::Message was removed." ;
		l.info(s);
	}
}

void
TCPCommunicationManager::sendMsg(shared_ptr<NOM> nomMsg)
{
	mec->sendMsg(nomMsg);
}

void
TCPCommunicationManager::recvMsg(shared_ptr<NOM> nomMsg)
{
	commInterface->sendCommMsg(nomMsg);
}

void
TCPCommunicationManager::setUserName(std::wstring userName)
{
	name = userName;
}

std::wstring
TCPCommunicationManager::getUserName()
{
	return name;
}

void
TCPCommunicationManager::setData(void* data)
{
	// if need be
}

bool
TCPCommunicationManager::start()
{
	//socket issue
	commInterface = new NCommInterface(this);

	commInterface->setMEBComponent(meb);
	MessageProcessor msgProcessor = bind(&TCPCommunicationManager::processRecvMessage, this, placeholders::_1, placeholders::_2);
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
TCPCommunicationManager::stop()
{
	commInterface->releaseNetEnv(commConfig);

	//socket issue
	delete commInterface;

	return true;
}

void
TCPCommunicationManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void
TCPCommunicationManager::processRecvMessage(unsigned char* data, int size)
{
	//auto HeaderSize = commConfig->getHeaderSize();
	auto IDPos = commConfig->getHeaderIDPos();
	auto IDSize = commConfig->getHeaderIDSize();

	unsigned long msgID = 0;

	//ID 형식이 ushort인 경우 처리
	if (IDSize == 2)
	{
		unsigned short tmpMsgID = 0;
		memcpy(&tmpMsgID, data + IDPos, IDSize);
		msgID = static_cast<unsigned long>(ntohs(tmpMsgID));
	}
	//ID 형식이 ulong인 경우 처리
	else if (IDSize == 4)
	{
		unsigned long tmpMsgID = 0;
		memcpy(&tmpMsgID, data + IDPos, IDSize);
		msgID = ntohl(tmpMsgID);
	}
	else
	{
		return;
	}

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
			//nomMsgCP의 인스턴스의 Owner 설정
			nomMsgCP->setOwner(name);
			this->sendMsg(nomMsgCP);
		}
	}
	else
	{
		std::wstringstream s; s << L"undefined message" ;
		l.info(s);
	}
}

unsigned int
TCPCommunicationManager::getObjectInstanceID(shared_ptr<NOM> nomMsg)
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
BaseManager * createObject()
{
	return new TCPCommunicationManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager * userManager)
{
	delete userManager;
}

