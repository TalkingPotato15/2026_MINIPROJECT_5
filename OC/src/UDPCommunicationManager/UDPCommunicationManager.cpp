#include "UDPCommunicationManager.h"
#include <filesystem>
#include <sstream>
#include "UDPCommunicationManagerIntelliVal.h"

using namespace std::filesystem;

namespace
{
	std::wstring fieldName(const wchar_t* arrayName, int index, const wchar_t* childName)
	{
		std::wstringstream ss;
		ss << arrayName << L"[" << index << L"]." << childName;
		return ss.str();
	}

	uint32_t readUInt(const shared_ptr<NOM>& nomMsg, const std::wstring& name, uint32_t fallback = 0)
	{
		auto value = nomMsg->getValue(name);
		return value != nullptr ? value->toUInt() : fallback;
	}

	double readDouble(const shared_ptr<NOM>& nomMsg, const std::wstring& name, double fallback = 0.0)
	{
		auto value = nomMsg->getValue(name);
		return value != nullptr ? value->toDouble() : fallback;
	}

	uint32_t readArrayUInt(
		const shared_ptr<NOM>& nomMsg,
		const wchar_t* arrayName,
		int index,
		const wchar_t* childName,
		uint32_t fallback = 0)
	{
		auto value = nomMsg->getValue(fieldName(arrayName, index, childName));
		return value != nullptr ? value->toUInt() : fallback;
	}

	double readArrayDouble(
		const shared_ptr<NOM>& nomMsg,
		const wchar_t* arrayName,
		int index,
		const wchar_t* childName,
		double fallback = 0.0)
	{
		auto value = nomMsg->getValue(fieldName(arrayName, index, childName));
		return value != nullptr ? value->toDouble() : fallback;
	}

	bool setArrayValue(
		const shared_ptr<NOM>& nomMsg,
		const wchar_t* arrayName,
		int index,
		const wchar_t* childName,
		NValueType* value)
	{
		return nomMsg->setValue(fieldName(arrayName, index, childName), value);
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
	std::wstringstream s; s << "[" << __FUNCTIONT__ << "] " ;
	l.info(s);
	setUserName(L"UDPCommunicationManager");

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
UDPCommunicationManager::release()
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
UDPCommunicationManager::registerMsg(std::wstring msgName)
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
	std::wstringstream s; s << L"UDPCommunicationManager::Message is reflected." ;
	l.info(s);
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
		std::wstringstream s; s << L"UDPCommunicationManager::Message was removed." ;
		l.info(s);
	}
}

void
UDPCommunicationManager::sendMsg(shared_ptr<NOM> nomMsg)
{
	std::wstringstream s;
	s << L"[UDPCommunicationManager::sendMsg] publish to internal MEB: "
		<< nomMsg->getName();
	l.info(s);

	mec->sendMsg(nomMsg);
}

void
UDPCommunicationManager::recvMsg(shared_ptr<NOM> nomMsg)
{
	std::wstringstream s;
	s << L"[UDPCommunicationManager::recvMsg] internal MEB delivered for external UDP send: "
		<< nomMsg->getName();
	l.info(s);

	commInterface->sendCommMsg(nomMsg);
}

void
UDPCommunicationManager::setUserName(std::wstring userName)
{
	name = userName; 
}

std::wstring
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
	std::wstringstream s; s << "[" << __FUNCTIONT__ << "] " ;
	l.info(s);

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

void
UDPCommunicationManager::processRecvMessage(unsigned char* data, int size)
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

	const auto msgName = commMsgHandler.getMsgName(msgID);

	std::wstringstream rxLog;
	rxLog << L"[UDPCommunicationManager::processRecvMessage] external UDP received: msgID=0x"
		<< std::hex << msgID << std::dec
		<< L", msgName=" << msgName
		<< L", size=" << size;
	l.info(rxLog);

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
			interpretReceivedNom(nomMsgCP);
			this->sendMsg(nomMsgCP);
		}
	}
	else
	{
		std::wstringstream s; s << L"undefined message" ;
		l.info(s);
	}
}

void
UDPCommunicationManager::interpretReceivedNom(const shared_ptr<NOM>& nomMsg)
{
	if (!nomMsg)
	{
		return;
	}

	const auto msgName = nomMsg->getName();
	if (msgName == L"Scenario")
	{
		interpretScenario(nomMsg);
	}
	else if (msgName == L"ATSStatus")
	{
		interpretATSStatus(nomMsg);
		relayATSInformationToRSS(nomMsg);
	}
	else if (msgName == L"RSSStatus")
	{
		interpretRSSStatus(nomMsg);
	}
	else if (msgName == L"MSSStatus")
	{
		interpretMSSStatus(nomMsg);
		relayMSSInformationDownlinkToRSS(nomMsg);
	}
	else if (msgName == L"MLSStatus")
	{
		interpretMLSStatus(nomMsg);
	}
	else if (msgName == L"TargetDetection")
	{
		interpretTargetDetection(nomMsg);
	}
	else if (msgName == L"TargetDestroyed")
	{
		interpretTargetDestroyed(nomMsg);
	}
	else
	{
		std::wstringstream s;
		s << L"[UDPCommunicationManager::interpretReceivedNom] pass-through message=" << msgName;
		l.info(s);
	}
}

void
UDPCommunicationManager::interpretScenario(const shared_ptr<NOM>& nomMsg)
{
	std::wstringstream s;
	s << L"[UDPCommunicationManager::interpretScenario] rssPos=("
		<< readDouble(nomMsg, L"rssPos.x") << L","
		<< readDouble(nomMsg, L"rssPos.y") << L","
		<< readDouble(nomMsg, L"rssPos.z") << L"), rssRadius="
		<< readUInt(nomMsg, L"rssRadius")
		<< L", mlsPos=("
		<< readDouble(nomMsg, L"mlsPos.x") << L","
		<< readDouble(nomMsg, L"mlsPos.y") << L","
		<< readDouble(nomMsg, L"mlsPos.z") << L")";
	l.info(s);

	for (int i = 0; i < 4; ++i)
	{
		std::wstringstream row;
		row << L"[UDPCommunicationManager::interpretScenario] sceneInfo[" << i << L"] speed="
			<< readUInt(nomMsg, fieldName(L"sceneInfo", i, L"speed"));
		for (int point = 0; point < 4; ++point)
		{
			std::wstringstream prefix;
			prefix << L"sceneInfo[" << i << L"].ATSPos[" << point << L"]";
			row << L", p" << point << L"=("
				<< readDouble(nomMsg, prefix.str() + L".x") << L","
				<< readDouble(nomMsg, prefix.str() + L".y") << L","
				<< readDouble(nomMsg, prefix.str() + L".z") << L")";
		}
		l.info(row);
	}
}

void
UDPCommunicationManager::interpretATSStatus(const shared_ptr<NOM>& nomMsg)
{
	std::wstringstream summary;
	summary << L"[UDPCommunicationManager::interpretATSStatus] status="
		<< readUInt(nomMsg, L"status");
	l.info(summary);

	for (int i = 0; i < 4; ++i)
	{
		std::wstringstream row;
		row << L"[UDPCommunicationManager::interpretATSStatus] targetInfo[" << i << L"] targetId="
			<< readArrayUInt(nomMsg, L"targetInfo", i, L"targetId")
			<< L", pos=("
			<< readArrayDouble(nomMsg, L"targetInfo", i, L"ATSPos.x") << L","
			<< readArrayDouble(nomMsg, L"targetInfo", i, L"ATSPos.y") << L","
			<< readArrayDouble(nomMsg, L"targetInfo", i, L"ATSPos.z") << L")"
			<< L", speed=" << readArrayUInt(nomMsg, L"targetInfo", i, L"speed")
			<< L", atsStatus=" << readArrayUInt(nomMsg, L"targetInfo", i, L"atsStatus");
		l.info(row);
	}
}

void
UDPCommunicationManager::interpretRSSStatus(const shared_ptr<NOM>& nomMsg)
{
	std::wstringstream s;
	s << L"[UDPCommunicationManager::interpretRSSStatus] status=" << readUInt(nomMsg, L"status");
	l.info(s);
}

void
UDPCommunicationManager::relayATSInformationToRSS(const shared_ptr<NOM>& atsStatusMsg)
{
	if (!atsStatusMsg || !meb || !commInterface)
	{
		return;
	}

	auto relayMsg = meb->getNOMInstance(name, L"ATSInformationToRSS");
	if (!relayMsg)
	{
		std::wstringstream s;
		s << L"[UDPCommunicationManager::relayATSInformationToRSS] ATSInformationToRSS NOM instance not found";
		l.info(s);
		return;
	}

	relayMsg->setOwner(name);

	NUShort messageId(0x07);
	NUShort messageLength(144);
	relayMsg->setValue(L"Header.MessageID", &messageId);
	relayMsg->setValue(L"Header.MessageLength", &messageLength);

	for (int i = 0; i < 4; ++i)
	{
		const auto posX = readArrayDouble(atsStatusMsg, L"targetInfo", i, L"ATSPos.x");
		const auto posY = readArrayDouble(atsStatusMsg, L"targetInfo", i, L"ATSPos.y");
		const auto posZ = readArrayDouble(atsStatusMsg, L"targetInfo", i, L"ATSPos.z");
		const auto speed = readArrayUInt(atsStatusMsg, L"targetInfo", i, L"speed");
		const auto rawTargetId = readArrayUInt(atsStatusMsg, L"targetInfo", i, L"targetId", static_cast<uint32_t>(i));
		const auto targetId = static_cast<uint32_t>(i);
		const auto atsStatus = readArrayUInt(atsStatusMsg, L"targetInfo", i, L"atsStatus");

		NDouble relayX(posX);
		NDouble relayY(posY);
		NDouble relayZ(posZ);
		NUInteger relaySpeed(speed);
		NUInteger relayTargetId(targetId);
		NUInteger relayAtsStatus(atsStatus);

		auto setOk = true;
		setOk &= setArrayValue(relayMsg, L"targetInfo", i, L"ATSPos.x", &relayX);
		setOk &= setArrayValue(relayMsg, L"targetInfo", i, L"ATSPos.y", &relayY);
		setOk &= setArrayValue(relayMsg, L"targetInfo", i, L"ATSPos.z", &relayZ);
		setOk &= setArrayValue(relayMsg, L"targetInfo", i, L"speed", &relaySpeed);
		setOk &= setArrayValue(relayMsg, L"targetInfo", i, L"targetId", &relayTargetId);
		setOk &= setArrayValue(relayMsg, L"targetInfo", i, L"atsStatus", &relayAtsStatus);

		std::wstringstream row;
		row << L"[UDPCommunicationManager::relayATSInformationToRSS] targetInfo[" << i
			<< L"] rawTargetId=" << rawTargetId
			<< L", relayTargetId=" << targetId
			<< L", verifiedTargetId=" << readArrayUInt(relayMsg, L"targetInfo", i, L"targetId")
			<< L", setOk=" << setOk
			<< L", pos=(" << posX << L"," << posY << L"," << posZ << L")";
		l.info(row);
	}

	std::wstringstream s;
	s << L"[UDPCommunicationManager::relayATSInformationToRSS] external UDP send: ATSInformationToRSS, length="
		<< relayMsg->getLength();
	l.info(s);

	commInterface->sendCommMsg(relayMsg);
}

void
UDPCommunicationManager::relayMSSInformationDownlinkToRSS(const shared_ptr<NOM>& mssStatusMsg)
{
	if (!mssStatusMsg || !meb || !commInterface)
	{
		return;
	}

	auto relayMsg = meb->getNOMInstance(name, L"MSSInformationDownlinkToRSS");
	if (!relayMsg)
	{
		std::wstringstream s;
		s << L"[UDPCommunicationManager::relayMSSInformationDownlinkToRSS] MSSInformationDownlinkToRSS NOM instance not found";
		l.info(s);
		return;
	}

	relayMsg->setOwner(name);

	NUShort messageId(0x0c);
	NUShort messageLength(144);
	relayMsg->setValue(L"Header.MessageID", &messageId);
	relayMsg->setValue(L"Header.MessageLength", &messageLength);

	for (int i = 0; i < 4; ++i)
	{
		const auto posX = readArrayDouble(mssStatusMsg, L"missileInfo", i, L"MSSPos.x");
		const auto posY = readArrayDouble(mssStatusMsg, L"missileInfo", i, L"MSSPos.y");
		const auto posZ = readArrayDouble(mssStatusMsg, L"missileInfo", i, L"MSSPos.z");
		const auto missileId = readArrayUInt(mssStatusMsg, L"missileInfo", i, L"missileId", static_cast<uint32_t>(i + 1));
		const auto targetId = readArrayUInt(mssStatusMsg, L"missileInfo", i, L"targetId");
		const auto mssStatus = readArrayUInt(mssStatusMsg, L"missileInfo", i, L"mssStatus");

		NDouble relayX(posX);
		NDouble relayY(posY);
		NDouble relayZ(posZ);
		NUInteger relayMissileId(missileId);
		NUInteger relayTargetId(targetId);
		NUInteger relayMssStatus(mssStatus);

		auto setOk = true;
		setOk &= setArrayValue(relayMsg, L"missileInfo", i, L"MSSPos.x", &relayX);
		setOk &= setArrayValue(relayMsg, L"missileInfo", i, L"MSSPos.y", &relayY);
		setOk &= setArrayValue(relayMsg, L"missileInfo", i, L"MSSPos.z", &relayZ);
		setOk &= setArrayValue(relayMsg, L"missileInfo", i, L"missileId", &relayMissileId);
		setOk &= setArrayValue(relayMsg, L"missileInfo", i, L"targetId", &relayTargetId);
		setOk &= setArrayValue(relayMsg, L"missileInfo", i, L"mssStatus", &relayMssStatus);

		std::wstringstream row;
		row << L"[UDPCommunicationManager::relayMSSInformationDownlinkToRSS] missileInfo[" << i
			<< L"] missileId=" << missileId
			<< L", targetId=" << targetId
			<< L", mssStatus=" << mssStatus
			<< L", setOk=" << setOk
			<< L", pos=(" << posX << L"," << posY << L"," << posZ << L")";
		l.info(row);
	}

	std::wstringstream s;
	s << L"[UDPCommunicationManager::relayMSSInformationDownlinkToRSS] external UDP send: MSSInformationDownlinkToRSS, length="
		<< relayMsg->getLength();
	l.info(s);

	commInterface->sendCommMsg(relayMsg);
}

void
UDPCommunicationManager::interpretMSSStatus(const shared_ptr<NOM>& nomMsg)
{
	std::wstringstream summary;
	summary << L"[UDPCommunicationManager::interpretMSSStatus] status="
		<< readUInt(nomMsg, L"status");
	l.info(summary);

	for (int i = 0; i < 4; ++i)
	{
		const auto missileId = readUInt(nomMsg, fieldName(L"missileInfo", i, L"missileId"), static_cast<uint32_t>(i + 1));
		const auto targetId = readUInt(nomMsg, fieldName(L"missileInfo", i, L"targetId"));
		const auto mssStatus = readUInt(nomMsg, fieldName(L"missileInfo", i, L"mssStatus"));

		std::wstringstream row;
		row << L"[UDPCommunicationManager::interpretMSSStatus] missileInfo[" << i << L"] missileId="
			<< missileId
			<< L", targetId=" << targetId
			<< L", pos=("
			<< readDouble(nomMsg, fieldName(L"missileInfo", i, L"MSSPos.x")) << L","
			<< readDouble(nomMsg, fieldName(L"missileInfo", i, L"MSSPos.y")) << L","
			<< readDouble(nomMsg, fieldName(L"missileInfo", i, L"MSSPos.z")) << L")"
			<< L", mssStatus=" << mssStatus;
		l.info(row);
	}
}

void
UDPCommunicationManager::interpretMLSStatus(const shared_ptr<NOM>& nomMsg)
{
	std::wstringstream s;
	s << L"[UDPCommunicationManager::interpretMLSStatus] status=" << readUInt(nomMsg, L"status")
		<< L", missileStatus=("
		<< readUInt(nomMsg, L"launcherInfo.missileStatus1") << L","
		<< readUInt(nomMsg, L"launcherInfo.missileStatus2") << L","
		<< readUInt(nomMsg, L"launcherInfo.missileStatus3") << L","
		<< readUInt(nomMsg, L"launcherInfo.missileStatus4") << L")"
		<< L", missileStock=" << readUInt(nomMsg, L"launcherInfo.missileStock");
	l.info(s);
}

void
UDPCommunicationManager::interpretTargetDetection(const shared_ptr<NOM>& nomMsg)
{
	std::wstringstream s;
	s << L"[UDPCommunicationManager::interpretTargetDetection] targetID="
		<< readUInt(nomMsg, L"targetID")
		<< L", targetDetectonSuccess="
		<< readUInt(nomMsg, L"targetDetectonSuccess");
	l.info(s);
}

void
UDPCommunicationManager::interpretTargetDestroyed(const shared_ptr<NOM>& nomMsg)
{
	std::wstringstream s;
	s << L"[UDPCommunicationManager::interpretTargetDestroyed] targetID="
		<< readUInt(nomMsg, L"targetID")
		<< L", missionFlag="
		<< readUInt(nomMsg, L"missionFlag");
	l.info(s);
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

