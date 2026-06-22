#pragma once

#include "DDSMessageHandler.h"
//#include "DDSMessageTable.h"
#include <algorithm>
#include <filesystem>
#include <fstream>	// test
#include <nFramework/util/util.h>

using namespace std::filesystem;
/************************************************************************
	constructor / destructor
************************************************************************/
DDSMessageHandler::DDSMessageHandler(BaseManager* ddsSimNetManager) : user(ddsSimNetManager)
{
	initialize();
}


DDSMessageHandler::~DDSMessageHandler(void)
{
	release();
}


/************************************************************************
	initialize / release
************************************************************************/
void
DDSMessageHandler::initialize()
{
	path p(util::tstring2string(user->getUserName()).c_str());
	current_path(p);

	IniHandler iniHandler;
	iniHandler.readIni(L"LinkInfo.ini");
	domainId = iniHandler.readInteger(L"DDS", L"DOMAIN_ID");
	

	// Schema Registry Data 파싱
	std::wstring schRegFilePath = current_path().c_str();
	schRegFilePath += L"\\..\\SchemaRegistryData.xml";
	nomParser = std::make_unique<NOMParser>();
	nomParser->setNOMFile(schRegFilePath);

	// 순서 중요!!
	nomParser->parseNote();
	auto noteMap = nomParser->getNoteMap();
	nomParser->parseDataType();
	auto dataTypeMap = nomParser->getDataTypeMap();
	
	// NOM 파싱
	std::wstring nomFilePath = current_path().c_str();
	nomFilePath += L"\\";
	nomFilePath += user->getUserName();
	nomFilePath += L".xml";
	nomParser->setNOMFile(nomFilePath);
	if (nomParser->parse(dataTypeMap, noteMap))
	{
		msgMap = nomParser->getMessageMap();
	}

	dcps = new DDSServiceProvider;

	participant = dcps->createDomainParticipant(domainId/*, project*/);
	participant->ignore_participant(participant->get_instance_handle());

	publisher = dcps->createPublisher();
	subscriber = dcps->createSubscriber();

	registerNOMMsg();
	registerNOMMsgProcessor();
	createLITS_DDSTopic();

	path up("..");
	current_path(up);
}


void
DDSMessageHandler::release()
{
	dcps->deleteSubscriber(subscriber);
	dcps->deletePublisher(publisher);
	dcps->deleteDomainParticipant(participant);
	
	delete dcps;

	deleteNOMMsgProcessor();
	deleteLITS_DDSTopic();
}


/************************************************************************
	register or delete NOM and TOPIC messages
************************************************************************/
void
DDSMessageHandler::registerNOMMsg()
{
	for (auto nomMsgItr : msgMap)
	{
		NMessage* nMsg = nomMsgItr.second;
		if (nMsg->getSharing() == ESharing::ENUM_SHARING_PUBLISH ||
			nMsg->getSharing() == ESharing::ENUM_SHARING_PUBLISHSUBSCRIBE) 
		{
			std::shared_ptr<NOM> nomMsg;

			int atsSourceID = 11;
			if (nomMsgItr.first == L"AirThreatInformation")
			{
				for (int nCount = 0; nCount < 4; nCount++)
				{
					nomMsg = user->registerMsg(nomMsgItr.first);
					topicList.try_emplace(1000 + atsSourceID + nCount, nomMsg);
				}
			}

			int mssSourceID = 21;
			if (nomMsgItr.first == L"InterceptorInformation")
			{
				for (int nCount = 0; nCount < 2; nCount++)
				{
					nomMsg = user->registerMsg(nomMsgItr.first);
					topicList.try_emplace(2000 + mssSourceID + nCount, nomMsg);
				}
			}

			if (nomMsgItr.first == L"UplinkInformation")
			{
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(3031, nomMsg);			// REGCC
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(3051, nomMsg);			// MFRS
			}

			int downLinkSourceID = 21;
			if (nomMsgItr.first == L"DownlinkInformation")
			{
				for (int nCount = 0; nCount < 2; nCount++)
				{
					nomMsg = user->registerMsg(nomMsgItr.first);
					topicList.try_emplace(4000 + downLinkSourceID + nCount, nomMsg);
				}
			}

			if (nomMsgItr.first == L"TimeTickInformation")
			{
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(5031, nomMsg);			// REGCC
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(5051, nomMsg);			// MFRS
			}

			if (nomMsgItr.first == L"MFRAttitudeInformation")
			{
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(6031, nomMsg);			// REGCC
				nomMsg = user->registerMsg(nomMsgItr.first);
				topicList.try_emplace(6051, nomMsg);			// MFRS
			}

		}
	}
}


void
DDSMessageHandler::registerNOMMsgProcessor()
{
	std::function<void(std::shared_ptr<NOM>)> nomMsgProc;

	nomMsgProc = bind(&DDSMessageHandler::processAirThreatInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(L"AirThreatInformation", nomMsgProc);

	nomMsgProc = bind(&DDSMessageHandler::processInterceptorInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(L"InterceptorInformation", nomMsgProc);

	nomMsgProc = bind(&DDSMessageHandler::processUplinkInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(L"UplinkInformation", nomMsgProc);

	nomMsgProc = bind(&DDSMessageHandler::processDownlinkInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(L"DownlinkInformation", nomMsgProc);

	nomMsgProc = bind(&DDSMessageHandler::processTimeTickInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(L"TimeTickInformation", nomMsgProc);

	nomMsgProc = bind(&DDSMessageHandler::processMFRAttitudeInformationSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(L"MFRAttitudeInformation", nomMsgProc);

	// test
	/*nomMsgProc = bind(&DDSMessageHandler::testDDSConnectSent, this, std::placeholders::_1);
	nomProcessorMap.emplace(L"TestDDSConnection", nomMsgProc);*/

	// test
	/*
	nomMsgProc = bind(&DDSMessageHandler::processStop, this, std::placeholders::_1);
	nomProcessorMap.emplace(L"StopSimulation", nomMsgProc);
	*/
}


// test
/*
void
DDSMessageHandler::processStop(std::shared_ptr<NOM> nom)
{
	ofstream testFile("./testDDSFile.txt", std::ofstream::out | std::ofstream::trunc);
	testFile << "Time" << std::endl;
	for (auto itr : testQueue)
	{
		std::time_t testTime = std::chrono::system_clock::to_time_t(itr);
		struct tm T;
		localtime_s(&T, &testTime);

		auto timeSineEpoch = itr.time_since_epoch();
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(timeSineEpoch).count();
		auto mills = std::chrono::duration_cast<std::chrono::milliseconds>(timeSineEpoch).count();

		testFile << T.tm_hour << "." << T.tm_min << "." << T.tm_sec << "." << mills - seconds * 1000 << std::endl;
	}
	testFile.close();
}
*/

void
DDSMessageHandler::deleteNOMMsgProcessor()
{
	nomProcessorMap.clear();
}


void
DDSMessageHandler::createLITS_DDSTopic()
{
	DDSProviderInterface* topic;

	// Topic_Instance::AirThreatInformation
	topic = new DDSTopicServicesTemplate<AirThreatInformationTypeSupport, AirThreatInformationDataWriter, AirThreatInformationDataReader, AirThreatInformationSeq, AirThreatInformation>(participant, publisher, subscriber, "AirThreatInformation");
	topicProcessorList.emplace(L"AirThreatInformation", topic);

	auto airThreatInfoTopic = static_cast<DDSTopicServicesTemplate<AirThreatInformationTypeSupport, AirThreatInformationDataWriter, AirThreatInformationDataReader, AirThreatInformationSeq, AirThreatInformation>*>(topic);
	std::function<void(byte*)> airThreatInfoProc = bind(&DDSMessageHandler::processAirThreatInformationReceived, this, std::placeholders::_1);
	airThreatInfoTopic->injectDDSMsgProcessor(airThreatInfoProc);
	
	// Topic_Instance::InterceptorInformation
	topic = new DDSTopicServicesTemplate<InterceptorInformationTypeSupport, InterceptorInformationDataWriter, InterceptorInformationDataReader, InterceptorInformationSeq, InterceptorInformation>(participant, publisher, subscriber, "InterceptorInformation");
	topicProcessorList.emplace(L"InterceptorInformation", topic);

	auto interceptorInfoTopic = static_cast<DDSTopicServicesTemplate<InterceptorInformationTypeSupport, InterceptorInformationDataWriter, InterceptorInformationDataReader, InterceptorInformationSeq, InterceptorInformation>*>(topic);
	std::function<void(byte*)> interceptorInfoProc = bind(&DDSMessageHandler::processInterceptorInformationReceived, this, std::placeholders::_1);
	interceptorInfoTopic->injectDDSMsgProcessor(interceptorInfoProc);

	// Topic_Instance::UplinkInformation
	topic = new DDSTopicServicesTemplate<UplinkInformationTypeSupport, UplinkInformationDataWriter, UplinkInformationDataReader, UplinkInformationSeq, UplinkInformation>(participant, publisher, subscriber, "UplinkInformation");
	topicProcessorList.emplace(L"UplinkInformation", topic);

	auto uplinkInfoTopic = static_cast<DDSTopicServicesTemplate<UplinkInformationTypeSupport, UplinkInformationDataWriter, UplinkInformationDataReader, UplinkInformationSeq, UplinkInformation>*>(topic);
	std::function<void(byte*)> uplinkInfoProc = bind(&DDSMessageHandler::processUplinkInformationReceived, this, std::placeholders::_1);
	uplinkInfoTopic->injectDDSMsgProcessor(uplinkInfoProc);

	// Topic_Instance::DownlinkInformation
	topic = new DDSTopicServicesTemplate<DownlinkInformationTypeSupport, DownlinkInformationDataWriter, DownlinkInformationDataReader, DownlinkInformationSeq, DownlinkInformation>(participant, publisher, subscriber, "DownlinkInformation");
	topicProcessorList.emplace(L"DownlinkInformation", topic);

	auto downlinkInfoTopic = static_cast<DDSTopicServicesTemplate<DownlinkInformationTypeSupport, DownlinkInformationDataWriter, DownlinkInformationDataReader, DownlinkInformationSeq, DownlinkInformation>*>(topic);
	std::function<void(byte*)> downlinkInfoProc = bind(&DDSMessageHandler::processDownlinkInformationReceived, this, std::placeholders::_1);
	downlinkInfoTopic->injectDDSMsgProcessor(downlinkInfoProc);

	// Topic_Instance::TimeTickInformation
	topic = new DDSTopicServicesTemplate<TimeTickInformationTypeSupport, TimeTickInformationDataWriter, TimeTickInformationDataReader, TimeTickInformationSeq, TimeTickInformation>(participant, publisher, subscriber, "TimeTickInformation");
	topicProcessorList.emplace(L"TimeTickInformation", topic);

	auto timeTickInfoTopic = static_cast<DDSTopicServicesTemplate<TimeTickInformationTypeSupport, TimeTickInformationDataWriter, TimeTickInformationDataReader, TimeTickInformationSeq, TimeTickInformation>*>(topic);
	std::function<void(byte*)> timeTickInfoProc = bind(&DDSMessageHandler::processTimeTickInformationReceived, this, std::placeholders::_1);
	timeTickInfoTopic->injectDDSMsgProcessor(timeTickInfoProc);

	// Topic_Instance::MFRAttitudeInformation
	topic = new DDSTopicServicesTemplate<MFRAttitudeInformationTypeSupport, MFRAttitudeInformationDataWriter, MFRAttitudeInformationDataReader, MFRAttitudeInformationSeq, MFRAttitudeInformation>(participant, publisher, subscriber, "MFRAttitudeInformation");
	topicProcessorList.emplace(L"MFRAttitudeInformation", topic);

	auto mfrAttitudeInformationTopic = static_cast<DDSTopicServicesTemplate<MFRAttitudeInformationTypeSupport, MFRAttitudeInformationDataWriter, MFRAttitudeInformationDataReader, MFRAttitudeInformationSeq, MFRAttitudeInformation>*>(topic);
	std::function<void(byte*)> mfrAttituedInfoProc = bind(&DDSMessageHandler::processMFRAttitudeInformationReceived, this, std::placeholders::_1);
	mfrAttitudeInformationTopic->injectDDSMsgProcessor(mfrAttituedInfoProc);

	// test 230921
	//<typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
	/*topic = new DDSTopicServicesTemplate<TestDDSConnectionTypeSupport, TestDDSConnectionDataWriter, TestDDSConnectionDataReader, TestDDSConnectionSeq, TestDDSConnection>(participant, publisher, subscriber, "TestDDSConnection";
	topicProcessorList.emplace(L"TestDDSConnection", topic));
	
	auto ddsConnectTopic = static_cast<DDSTopicServicesTemplate<TestDDSConnectionTypeSupport, TestDDSConnectionDataWriter, TestDDSConnectionDataReader, TestDDSConnectionSeq, TestDDSConnection>*>(topic);
	std::function<void(byte*)> ddsConnectProc = bind(&DDSMessageHandler::testDDSConnectReceived, this, std::placeholders::_1);
	ddsConnectTopic->injectDDSMsgProcessor(ddsConnectProc);*/


	// to access topic services
	for_each(topicProcessorList.begin(), topicProcessorList.end(), [this](auto elem) { elem.second->injectDDSProvider(dcps); elem.second->create(); });
}


void
DDSMessageHandler::deleteLITS_DDSTopic()
{
	for_each(topicProcessorList.begin(), topicProcessorList.end(), [](auto elem) { delete elem.second; });
	topicProcessorList.clear();
}


/************************************************************************
	methods between xxxHandler and xxxManager
************************************************************************/
void
DDSMessageHandler::injectMEB(IMEBComponent* meb)
{
	this->meb = meb;
}


void
DDSMessageHandler::processMessageSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = nomProcessorMap.find(nom->getName()); itr != nomProcessorMap.end())
	{ 
		itr->second(nom);
		//if (itr->first == L"AirThreatInformation"
		//{
		//	tstringstream pathPrefixStream;
		//	pathPrefixStream << L"AirThreatMessage[" << 0 << L"]";

		//	std::wstring pathPrefix;
		//	pathPrefixStream >> pathPrefix;
		//	tcout << nom->getValue(pathPrefix + L".AccelerationX")->toShort();
		//	tcout << nom->getValue(pathPrefix + L".AccelerationY")->toShort();
		//	tcout << nom->getValue(pathPrefix + L".AccelerationZ")->toShort();
		//}
	}
	else
	{
		l.error( L"NOM does not exist." );
	}
}


/************************************************************************
	process NOM Messages
************************************************************************/

// test
//void
//DDSMessageHandler::testDDSConnectSent(std::shared_ptr<NOM> nom)
//{
//	tcout << L"before test Start" << std::std::endl;
//	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
//	{	
//		auto topicInterface = static_cast<DDSTopicServicesTemplate<TestDDSConnectionTypeSupport, TestDDSConnectionDataWriter, TestDDSConnectionDataReader, TestDDSConnectionSeq, TestDDSConnection>*>(itr->second);
//		TestDDSConnection* instance = topicInterface->createTopic();
//		instance->TestParam = nom->getValue(L"TestParam")->toUShort();
//		tcout << L"in Test DDS Connect Sent";
//		topicInterface->writeTopic(instance);
//	}
//	tcout << L"after test Start" << std::std::endl;
//
//}

void
DDSMessageHandler::processAirThreatInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		inAirthreatCount++;
		if((inAirthreatCount % 50)==0)
		{ 
			l.debug(L"in Airthreat");
		}
		auto topicInterface = static_cast<DDSTopicServicesTemplate<AirThreatInformationTypeSupport, AirThreatInformationDataWriter, AirThreatInformationDataReader, AirThreatInformationSeq, AirThreatInformation>*>(itr->second);
		AirThreatInformation* instance = topicInterface->createTopic();

		// MessageHeader
		instance->Header.TopicLabel = nom->getValue(L"Header.TopicLabel")->toUShort();
		instance->Header.TopicSize = nom->getValue(L"Header.TopicSize")->toUShort();
		instance->Header.SourceID = nom->getValue(L"Header.SourceID")->toByte();
		instance->Header.TopicClass = nom->getValue(L"Header.TopicClass")->toByte();
		instance->Header.TopicNumber = nom->getValue(L"Header.TopicNumber")->toUShort();
		instance->Header.SystemTime = nom->getValue(L"Header.SystemTime")->toUInt64();
		
		// AirThreatInformation
		instance->TimeTick = nom->getValue(L"TimeTick")->toUInt();
		instance->SimulationFlag = nom->getValue(L"SimulationFlag")->toUShort();
		auto objectCount = nom->getValue(L"ObjectCount")->toUShort();
		instance->ObjectCount = objectCount;
		instance->AirThreatInformation::AirThreatMessage.length(objectCount);
		

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << L"AirThreatMessage[" << i << L"]";

			std::wstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			instance->AirThreatInformation::AirThreatMessage[i].ObjectID = nom->getValue(pathPrefix + L".ObjectID")->toUShort();
			instance->AirThreatInformation::AirThreatMessage[i].ObjectType = nom->getValue(pathPrefix + L".ObjectType")->toByte();
			instance->AirThreatInformation::AirThreatMessage[i].DestructionFlag = nom->getValue(pathPrefix + L".DestructionFlag")->toByte();
			instance->AirThreatInformation::AirThreatMessage[i].PositionX = nom->getValue(pathPrefix + L".PositionX")->toInt();
			instance->AirThreatInformation::AirThreatMessage[i].PositionY = nom->getValue(pathPrefix + L".PositionY")->toInt();
			instance->AirThreatInformation::AirThreatMessage[i].PositionZ = nom->getValue(pathPrefix + L".PositionZ")->toInt();
			instance->AirThreatInformation::AirThreatMessage[i].VelocityX = nom->getValue(pathPrefix + L".VelocityX")->toShort();
			instance->AirThreatInformation::AirThreatMessage[i].VelocityY = nom->getValue(pathPrefix + L".VelocityY")->toShort();
			instance->AirThreatInformation::AirThreatMessage[i].VelocityZ = nom->getValue(pathPrefix + L".VelocityZ")->toShort();
			instance->AirThreatInformation::AirThreatMessage[i].AccelerationX = nom->getValue(pathPrefix + L".AccelerationX")->toShort();
			// tcout << nom->getValue(pathPrefix + L".AccelerationX")->toShort() << std::std::endl ;
			instance->AirThreatInformation::AirThreatMessage[i].AccelerationY = nom->getValue(pathPrefix + L".AccelerationY")->toShort();
			instance->AirThreatInformation::AirThreatMessage[i].AccelerationZ = nom->getValue(pathPrefix + L".AccelerationZ")->toShort();
			instance->AirThreatInformation::AirThreatMessage[i].MeanRCS = nom->getValue(pathPrefix + L".MeanRCS")->toUShort();
			instance->AirThreatInformation::AirThreatMessage[i].Reserved = nom->getValue(pathPrefix + L".Reserved")->toByte();
			instance->AirThreatInformation::AirThreatMessage[i].JammingType = nom->getValue(pathPrefix + L".JammingType")->toByte();
			instance->AirThreatInformation::AirThreatMessage[i].JammingPower = nom->getValue(pathPrefix + L".JammingPower")->toUShort();
			instance->AirThreatInformation::AirThreatMessage[i].JammingPullOff = nom->getValue(pathPrefix + L".JammingPullOff")->toUShort();
		}

		topicInterface->writeTopic(instance);

		//testQueue.push_back(std::chrono::system_clock::now());	// test
	}
	else
	{
		l.error(L"NOM does not exist.");
	}
}


void
DDSMessageHandler::processInterceptorInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		auto topicInterface = static_cast<DDSTopicServicesTemplate<InterceptorInformationTypeSupport, InterceptorInformationDataWriter, InterceptorInformationDataReader, InterceptorInformationSeq, InterceptorInformation>*>(itr->second);
		InterceptorInformation* instance = topicInterface->createTopic();

		// MessageHeader
		instance->Header.TopicLabel = nom->getValue(L"Header.TopicLabel")->toUShort();
		instance->Header.TopicSize = nom->getValue(L"Header.TopicSize")->toUShort();
		instance->Header.SourceID = nom->getValue(L"Header.SourceID")->toByte();
		instance->Header.TopicClass = nom->getValue(L"Header.TopicClass")->toByte();
		instance->Header.TopicNumber = nom->getValue(L"Header.TopicNumber")->toUShort();
		instance->Header.SystemTime = nom->getValue(L"Header.SystemTime")->toUInt64();

		instance->TimeTick = nom->getValue(L"TimeTick")->toUInt();
		instance->SimulationFlag = nom->getValue(L"SimulationFlag")->toUShort();
		auto objectCount = nom->getValue(L"ObjectCount")->toUShort();
		instance->ObjectCount = objectCount;
		instance->InterceptorInformation::InterceptorMessage.length(objectCount);

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << L"InterceptorMessage[" << i << L"]";

			std::wstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			instance->InterceptorInformation::InterceptorMessage[i].ObjectID = nom->getValue(pathPrefix + L".ObjectID")->toUShort();	// [2021.12.06] ysk
			instance->InterceptorInformation::InterceptorMessage[i].MissileType = nom->getValue(pathPrefix + L".MissileType")->toByte();
			instance->InterceptorInformation::InterceptorMessage[i].DestructionFlag = nom->getValue(pathPrefix + L".DestructionFlag")->toByte();
			instance->InterceptorInformation::InterceptorMessage[i].PositionX = nom->getValue(pathPrefix + L".PositionX")->toInt();
			instance->InterceptorInformation::InterceptorMessage[i].PositionY = nom->getValue(pathPrefix + L".PositionY")->toInt();
			instance->InterceptorInformation::InterceptorMessage[i].PositionZ = nom->getValue(pathPrefix + L".PositionZ")->toInt();
			instance->InterceptorInformation::InterceptorMessage[i].VelocityX = nom->getValue(pathPrefix + L".VelocityX")->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].VelocityY = nom->getValue(pathPrefix + L".VelocityY")->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].VelocityZ = nom->getValue(pathPrefix + L".VelocityZ")->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].AccelerationX = nom->getValue(pathPrefix + L".AccelerationX")->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].AccelerationY = nom->getValue(pathPrefix + L".AccelerationY")->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].AccelerationZ = nom->getValue(pathPrefix + L".AccelerationZ")->toShort();
			instance->InterceptorInformation::InterceptorMessage[i].MeanRCS = nom->getValue(pathPrefix + L".MeanRCS")->toUShort();		// [22.09.06] ksy
			instance->InterceptorInformation::InterceptorMessage[i].Reserved = nom->getValue(pathPrefix + L".Reserved")->toUShort();		// [22.09.06] ksy
			instance->InterceptorInformation::InterceptorMessage[i].SignalPower = nom->getValue(pathPrefix + L".SignalPower")->toUShort();
			instance->InterceptorInformation::InterceptorMessage[i].SeekerPhase = nom->getValue(pathPrefix + L".SeekerPhase")->toByte();	// [22.09.06] ksy
			instance->InterceptorInformation::InterceptorMessage[i].AddressKey = nom->getValue(pathPrefix + L".AddressKey")->toByte();	// [22.05.24] ksy
		}

		topicInterface->writeTopic(instance);
	}
	else
	{
		l.error(L"NOM does not exist.");
	}
}


void
DDSMessageHandler::processUplinkInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		auto topicInterface = static_cast<DDSTopicServicesTemplate<UplinkInformationTypeSupport, UplinkInformationDataWriter, UplinkInformationDataReader, UplinkInformationSeq, UplinkInformation>*>(itr->second);
		UplinkInformation* instance = topicInterface->createTopic();

		// MessageHeader
		instance->Header.TopicLabel = nom->getValue(L"Header.TopicLabel")->toUShort();
		instance->Header.TopicSize = nom->getValue(L"Header.TopicSize")->toUShort();
		instance->Header.SourceID = nom->getValue(L"Header.SourceID")->toByte();
		instance->Header.TopicClass = nom->getValue(L"Header.TopicClass")->toByte();
		instance->Header.TopicNumber = nom->getValue(L"Header.TopicNumber")->toUShort();
		instance->Header.SystemTime = nom->getValue(L"Header.SystemTime")->toUInt64();

		instance->TimeTick = nom->getValue(L"TimeTick")->toUInt();
	
		// [21.11.10] ysk, [22.05.24] ksy
		instance->UplinkMessage.AddressKey = nom->getValue(L"UplinkMessage.AddressKey")->toUInt();
		instance->UplinkMessage.MissileType = nom->getValue(L"UplinkMessage.MissileType")->toUInt();

		for (auto i = 0; i < 26; i++)
		{
			instance->UplinkMessage.Data[i] = nom->getValue(L"UplinkMessage.Data", i)->toUShort();
		}

		topicInterface->writeTopic(instance);
	}
	else
	{
		l.error(L"NOM does not exist.");
	}
}


void
DDSMessageHandler::processDownlinkInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		auto topicInterface = static_cast<DDSTopicServicesTemplate<DownlinkInformationTypeSupport, DownlinkInformationDataWriter, DownlinkInformationDataReader, DownlinkInformationSeq, DownlinkInformation>*>(itr->second);
		DownlinkInformation* instance = topicInterface->createTopic();

		// MessageHeader
		instance->Header.TopicLabel = nom->getValue(L"Header.TopicLabel")->toUShort();
		instance->Header.TopicSize = nom->getValue(L"Header.TopicSize")->toUShort();
		instance->Header.SourceID = nom->getValue(L"Header.SourceID")->toByte();
		instance->Header.TopicClass = nom->getValue(L"Header.TopicClass")->toByte();
		instance->Header.TopicNumber = nom->getValue(L"Header.TopicNumber")->toUShort();
		instance->Header.SystemTime = nom->getValue(L"Header.SystemTime")->toUInt64();

		instance->TimeTick = nom->getValue(L"TimeTick")->toUInt();
		auto objectCount = nom->getValue(L"ObjectCount")->toUInt();
		instance->ObjectCount = objectCount;
		instance->DownlinkInformation::DownlinkMessage.length(objectCount);

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << L"DownlinkMessage[" << i << L"]";

			std::wstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			instance->DownlinkInformation::DownlinkMessage[i].AddressKey = nom->getValue(pathPrefix + L".AddressKey")->toUShort();
			instance->DownlinkInformation::DownlinkMessage[i].CRC = nom->getValue(pathPrefix + L".CRC")->toUShort();

			for (auto j = 0; j < 24; j++)
			{
				instance->DownlinkInformation::DownlinkMessage[i].Data[j] = nom->getValue(pathPrefix + L".Data", j)->toUShort();
			}
		}

		topicInterface->writeTopic(instance);
	}
	else
	{
		l.error(L"NOM does not exist.");
	}
}


void
DDSMessageHandler::processTimeTickInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		auto topicInterface = static_cast<DDSTopicServicesTemplate<TimeTickInformationTypeSupport, TimeTickInformationDataWriter, TimeTickInformationDataReader, TimeTickInformationSeq, TimeTickInformation>*>(itr->second);
		TimeTickInformation* instance = topicInterface->createTopic();

		instance->Header.TopicLabel = nom->getValue(L"Header.TopicLabel")->toUShort();
		instance->Header.TopicSize = nom->getValue(L"Header.TopicSize")->toUShort();
		instance->Header.SourceID = nom->getValue(L"Header.SourceID")->toByte();
		instance->Header.TopicClass = nom->getValue(L"Header.TopicClass")->toByte();
		instance->Header.TopicNumber = nom->getValue(L"Header.TopicNumber")->toUShort();
		instance->Header.SystemTime = nom->getValue(L"Header.SystemTime")->toUInt64();
		instance->TimeTickMessage.SyncCycle = nom->getValue(L"TimeTickMessage.SyncCycle")->toUInt();
		instance->TimeTickMessage.TimeTick = nom->getValue(L"TimeTickMessage.TimeTick")->toUInt();
		topicInterface->writeTopic(instance);
}
	else
	{
		l.error(L"NOM does not exist.");
	}
}


void
DDSMessageHandler::processMFRAttitudeInformationSent(std::shared_ptr<NOM> nom)
{
	if (auto itr = topicProcessorList.find(nom->getName()); itr != topicProcessorList.end())
	{
		auto topicInterface = static_cast<DDSTopicServicesTemplate<MFRAttitudeInformationTypeSupport, MFRAttitudeInformationDataWriter, MFRAttitudeInformationDataReader, MFRAttitudeInformationSeq, MFRAttitudeInformation>*>(itr->second);
		MFRAttitudeInformation* instance = topicInterface->createTopic();

		instance->Header.TopicLabel = nom->getValue(L"Header.TopicLabel")->toUShort();
		instance->Header.TopicSize = nom->getValue(L"Header.TopicSize")->toUShort();
		instance->Header.SourceID = nom->getValue(L"Header.SourceID")->toByte();
		instance->Header.TopicClass = nom->getValue(L"Header.TopicClass")->toByte();
		instance->Header.TopicNumber = nom->getValue(L"Header.TopicNumber")->toUShort();
		instance->Header.SystemTime = nom->getValue(L"Header.SystemTime")->toUInt64();
		instance->MFRAttitudeMessage.MFRAntennaRoll = nom->getValue(L"MFRAttitudeMessage.MFRAntennaRoll")->toFloat();
		instance->MFRAttitudeMessage.MFRAntennaPitch = nom->getValue(L"MFRAttitudeMessage.MFRAntennaPitch")->toFloat();
		instance->MFRAttitudeMessage.MFRAntennaHeading = nom->getValue(L"MFRAttitudeMessage.MFRAntennaHeading")->toFloat();
		topicInterface->writeTopic(instance);
	}
	else
	{
		l.error(L"NOM does not exist.");
	}
}

/************************************************************************
	process Topic Messages
************************************************************************/
void
DDSMessageHandler::processAirThreatInformationReceived(byte* instance)
{
	// if need be, write your code
	// converting topic instance to nom instance should be implemented.
	// [22.05.25] ksy
	AirThreatInformation* topic = nullptr;
	topic = reinterpret_cast<AirThreatInformation*>(instance);

		// [2021.11.12] ysk
	int topicKey = 1000 + topic->Header.SourceID;
	//tcout << topic->Header.SourceID << std::endl;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(L"Header.TopicLabel", &NUShort(topic->Header.TopicLabel));
		nom->setValue(L"Header.TopicSize", &NUShort(topic->Header.TopicSize));
		nom->setValue(L"Header.SourceID", &NByte(topic->Header.SourceID));
		nom->setValue(L"Header.TopicClass", &NByte(topic->Header.TopicClass));
		nom->setValue(L"Header.TopicNumber", &NUShort(topic->Header.TopicNumber));
		nom->setValue(L"Header.SystemTime", &NUInteger64((uint64)(topic->Header.SystemTime)));

		// body
		nom->setValue(L"TimeTick", &NUInteger(topic->TimeTick));
		nom->setValue(L"SimulationFlag", &NUShort(topic->SimulationFlag));
		auto objectCount = topic->ObjectCount;
		nom->setValue(L"ObjectCount", &NUShort(objectCount));

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << L"AirThreatMessage[" << i << L"]";

			std::wstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			nom->setValue(pathPrefix + L".ObjectID", &NUShort(topic->AirThreatMessage[i].ObjectID));
			nom->setValue(pathPrefix + L".ObjectType", &NByte(topic->AirThreatMessage[i].ObjectType));
			nom->setValue(pathPrefix + L".DestructionFlag", &NByte(topic->AirThreatMessage[i].DestructionFlag));
			nom->setValue(pathPrefix + L".PositionX", &NInteger(topic->AirThreatMessage[i].PositionX));
			nom->setValue(pathPrefix + L".PositionY", &NInteger(topic->AirThreatMessage[i].PositionY));
			nom->setValue(pathPrefix + L".PositionZ", &NInteger(topic->AirThreatMessage[i].PositionZ));
			nom->setValue(pathPrefix + L".VelocityX", &NShort(topic->AirThreatMessage[i].VelocityX));
			nom->setValue(pathPrefix + L".VelocityY", &NShort(topic->AirThreatMessage[i].VelocityY));
			nom->setValue(pathPrefix + L".VelocityZ", &NShort(topic->AirThreatMessage[i].VelocityZ));
			nom->setValue(pathPrefix + L".AccelerationX", &NShort(topic->AirThreatMessage[i].AccelerationX));
			nom->setValue(pathPrefix + L".AccelerationY", &NShort(topic->AirThreatMessage[i].AccelerationY));
			nom->setValue(pathPrefix + L".AccelerationZ", &NShort(topic->AirThreatMessage[i].AccelerationZ));
			nom->setValue(pathPrefix + L".MeanRCS", &NUShort(topic->AirThreatMessage[i].MeanRCS));
			nom->setValue(pathPrefix + L".Reserved", &NByte(topic->AirThreatMessage[i].Reserved));
			nom->setValue(pathPrefix + L".JammingType", &NByte(topic->AirThreatMessage[i].JammingType));
			nom->setValue(pathPrefix + L".JammingPower", &NUShort(topic->AirThreatMessage[i].JammingPower));
			nom->setValue(pathPrefix + L".JammingPullOff", &NUShort(topic->AirThreatMessage[i].JammingPullOff));
		}

		user->updateMsg(nom);
	}
}


void
DDSMessageHandler::processInterceptorInformationReceived(byte* instance)
{
	// if need be, write your code
	// getting the nom instance must be implemented.
	// [22.05.25] ksy
	InterceptorInformation* topic = nullptr;
	topic = reinterpret_cast<InterceptorInformation*>(instance);

	// [2021.11.12] ysk
	int topicKey = 2000 + topic->Header.SourceID;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(L"Header.TopicLabel", &NUShort(topic->Header.TopicLabel));
		nom->setValue(L"Header.TopicSize", &NUShort(topic->Header.TopicSize));
		nom->setValue(L"Header.SourceID", &NByte(topic->Header.SourceID));
		nom->setValue(L"Header.TopicClass", &NByte(topic->Header.TopicClass));
		nom->setValue(L"Header.TopicNumber", &NUShort(topic->Header.TopicNumber));
		nom->setValue(L"Header.SystemTime", &NUInteger64(topic->Header.SystemTime));

		// body
		nom->setValue(L"TimeTick", &NUInteger(topic->TimeTick));
		nom->setValue(L"SimulationFlag", &NUShort(topic->SimulationFlag));
		auto objectCount = topic->ObjectCount;
		nom->setValue(L"ObjectCount", &NUShort(objectCount));

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << L"InterceptorMessage[" << i << L"]";

			std::wstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			nom->setValue(pathPrefix + L".ObjectID", &NUShort(topic->InterceptorMessage[i].ObjectID));
			nom->setValue(pathPrefix + L".MissileType", &NByte(topic->InterceptorMessage[i].MissileType));
			nom->setValue(pathPrefix + L".DestructionFlag", &NByte(topic->InterceptorMessage[i].DestructionFlag));
			nom->setValue(pathPrefix + L".PositionX", &NInteger(topic->InterceptorMessage[i].PositionX));
			nom->setValue(pathPrefix + L".PositionY", &NInteger(topic->InterceptorMessage[i].PositionY));
			nom->setValue(pathPrefix + L".PositionZ", &NInteger(topic->InterceptorMessage[i].PositionZ));
			nom->setValue(pathPrefix + L".VelocityX", &NShort(topic->InterceptorMessage[i].VelocityX));
			nom->setValue(pathPrefix + L".VelocityY", &NShort(topic->InterceptorMessage[i].VelocityY));
			nom->setValue(pathPrefix + L".VelocityZ", &NShort(topic->InterceptorMessage[i].VelocityZ));
			nom->setValue(pathPrefix + L".AccelerationX", &NShort(topic->InterceptorMessage[i].AccelerationX));
			nom->setValue(pathPrefix + L".AccelerationY", &NShort(topic->InterceptorMessage[i].AccelerationY));
			nom->setValue(pathPrefix + L".AccelerationZ", &NShort(topic->InterceptorMessage[i].AccelerationZ));
			nom->setValue(pathPrefix + L".MeanRCS", &NUShort(topic->InterceptorMessage[i].MeanRCS));
			nom->setValue(pathPrefix + L".Reserved", &NUShort(topic->InterceptorMessage[i].Reserved));
			nom->setValue(pathPrefix + L".SignalPower", &NUShort(topic->InterceptorMessage[i].SignalPower));
			nom->setValue(pathPrefix + L".SeekerPhase", &NByte(topic->InterceptorMessage[i].SeekerPhase));
			nom->setValue(pathPrefix + L".AddressKey", &NByte(topic->InterceptorMessage[i].AddressKey));	// [22.05.24] ksy
		}

		user->updateMsg(nom);
	}
}


void
DDSMessageHandler::processUplinkInformationReceived(byte* instance)
{
	// [22.05.25] ksy
	UplinkInformation* topic = nullptr;
	topic = reinterpret_cast<UplinkInformation*>(instance);

	// [2021.11.12] ysk
	int topicKey = 3000 + topic->Header.SourceID;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(L"Header.TopicLabel", &NUShort(topic->Header.TopicLabel));
		nom->setValue(L"Header.TopicSize", &NUShort(topic->Header.TopicSize));
		nom->setValue(L"Header.SourceID", &NByte(topic->Header.SourceID));
		nom->setValue(L"Header.TopicClass", &NByte(topic->Header.TopicClass));
		nom->setValue(L"Header.TopicNumber", &NUShort(topic->Header.TopicNumber));
		nom->setValue(L"Header.SystemTime", &NUInteger64(topic->Header.SystemTime));

		// body
		nom->setValue(L"TimeTick", &NUInteger(topic->TimeTick));
		nom->setValue(L"UplinkMessage.AddressKey", &NUShort(topic->UplinkMessage.AddressKey));
		nom->setValue(L"UplinkMessage.MissileType", &NUShort(topic->UplinkMessage.MissileType));

		for (auto i = 0; i < 26; i++)
		{
			nom->setValue(L"UplinkMessage.Data", &NUShort(topic->UplinkMessage.Data[i]), i);
		}

		user->updateMsg(nom);
	}
}


void
DDSMessageHandler::processDownlinkInformationReceived(byte* instance)
{
	// [22.05.25] ksy
	DownlinkInformation* topic = nullptr;
	topic = reinterpret_cast<DownlinkInformation*>(instance);

	// [2021.11.12] ysk
	int topicKey = 4000 + topic->Header.SourceID;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(L"Header.TopicLabel", &NUShort(topic->Header.TopicLabel));
		nom->setValue(L"Header.TopicSize", &NUShort(topic->Header.TopicSize));
		nom->setValue(L"Header.SourceID", &NByte(topic->Header.SourceID));
		nom->setValue(L"Header.TopicClass", &NByte(topic->Header.TopicClass));
		nom->setValue(L"Header.TopicNumber", &NUShort(topic->Header.TopicNumber));
		nom->setValue(L"Header.SystemTime", &NUInteger64(topic->Header.SystemTime));

		// body
		nom->setValue(L"TimeTick", &NUInteger(topic->TimeTick));
		uint objectCount = topic->ObjectCount;
		nom->setValue(L"ObjectCount", &NUInteger(objectCount));

		for (int i = 0; i < objectCount; i++)
		{
			tstringstream pathPrefixStream;
			pathPrefixStream << L"DownlinkMessage[" << i << L"]";

			std::wstring pathPrefix;
			pathPrefixStream >> pathPrefix;

			nom->setValue(pathPrefix + L".AddressKey", &NUShort(topic->DownlinkMessage[i].AddressKey));
			nom->setValue(pathPrefix + L".CRC", &NUShort(topic->DownlinkMessage[i].CRC));

			for (auto j = 0; j < 24; j++)
			{
				nom->setValue(pathPrefix + L".Data", &NUShort(topic->DownlinkMessage[i].Data[j]), j);
			}
		}

		user->updateMsg(nom);
	}
}


void
DDSMessageHandler::processTimeTickInformationReceived(byte* instance)
{
	// if need be, write your code
	// getting the nom instance must be implemented.
	// [22.05.25] ksy
	TimeTickInformation* topic = nullptr;
	topic = reinterpret_cast<TimeTickInformation*>(instance);

	// [2021.11.12] ysk
	int topicKey = 5000 + topic->Header.SourceID;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(L"Header.TopicLabel", &NUShort(topic->Header.TopicLabel));
		nom->setValue(L"Header.TopicSize", &NUShort(topic->Header.TopicSize));
		nom->setValue(L"Header.SourceID", &NByte(topic->Header.SourceID));
		nom->setValue(L"Header.TopicClass", &NByte(topic->Header.TopicClass));
		nom->setValue(L"Header.TopicNumber", &NUShort(topic->Header.TopicNumber));
		nom->setValue(L"Header.SystemTime", &NUInteger64(topic->Header.SystemTime));

		// body
		nom->setValue(L"TimeTickMessage.SyncCycle", &NUInteger(topic->TimeTickMessage.SyncCycle));
		nom->setValue(L"TimeTickMessage.TimeTick", &NUInteger(topic->TimeTickMessage.TimeTick));

		user->updateMsg(nom);
	}
}


void
DDSMessageHandler::processMFRAttitudeInformationReceived(byte* instance)
{
	// [2022.05.24] ksy
	MFRAttitudeInformation* topic = nullptr;
	topic = reinterpret_cast<MFRAttitudeInformation*>(instance);

	int topicKey = 6000 + topic->Header.SourceID;

	if (auto topicItr = topicList.find(topicKey); topicItr != topicList.end())
	{
		std::shared_ptr<NOM> nom = topicItr->second;

		// header
		nom->setValue(L"Header.TopicLabel", &NUShort(topic->Header.TopicLabel));
		nom->setValue(L"Header.TopicSize", &NUShort(topic->Header.TopicSize));
		nom->setValue(L"Header.SourceID", &NByte(topic->Header.SourceID));
		nom->setValue(L"Header.TopicClass", &NByte(topic->Header.TopicClass));
		nom->setValue(L"Header.TopicNumber", &NUShort(topic->Header.TopicNumber));
		nom->setValue(L"Header.SystemTime", &NUInteger64(topic->Header.SystemTime));

		// body
		nom->setValue(L"MFRAttitudeMessage.MFRAntennaRoll", &NFloat(topic->MFRAttitudeMessage.MFRAntennaRoll));
		nom->setValue(L"MFRAttitudeMessage.MFRAntennaPitch", &NFloat(topic->MFRAttitudeMessage.MFRAntennaPitch));
		nom->setValue(L"MFRAttitudeMessage.MFRAntennaHeading", &NFloat(topic->MFRAttitudeMessage.MFRAntennaHeading));

		user->updateMsg(nom);
	}
}


// test
//void
//DDSMessageHandler::testDDSConnectReceived(byte* instance)
//{
//	// [2022.05.24] ksy
//	TestDDSConnection* topic = nullptr;
//	topic = reinterpret_cast<TestDDSConnection*>(instance);
//	std::shared_ptr<NOM> nomMsg;
//
//	nomMsg = user->registerMsg(L"TestDDSConnection");
//	
//	nomMsg->setValue(L"TestParam", &NUShort(topic->TestParam));
//	tcout << L"DDS Received Message!"; // [23.10.25] 받는 부분 코드 수정 - hs
//
//	user->updateMsg(nomMsg);
//}