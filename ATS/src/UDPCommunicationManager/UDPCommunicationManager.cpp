#include "UDPCommunicationManager.h"

#include <array>
#include <cstring>
#include <exception>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <utility>

using namespace std::filesystem;

namespace
{
constexpr std::size_t kTargetCount = 4;
constexpr std::size_t kRoutePointCount = 4;

tstring makeScenePath(std::size_t targetIndex, std::size_t pointIndex, const TCHAR* field)
{
    std::basic_ostringstream<TCHAR> path;
    path << _T("sceneInfo[") << targetIndex << _T("].ATSPos[")
         << pointIndex << _T("].") << field;
    return path.str();
}

tstring makeSceneSpeedPath(std::size_t targetIndex)
{
    std::basic_ostringstream<TCHAR> path;
    path << _T("sceneInfo[") << targetIndex << _T("].speed");
    return path.str();
}

tstring makeTargetPath(std::size_t targetIndex, const TCHAR* field)
{
    std::basic_ostringstream<TCHAR> path;
    path << _T("targetInfo[") << targetIndex << _T("].") << field;
    return path.str();
}
}

UDPCommunicationManager::UDPCommunicationManager()
{
    init();
}

UDPCommunicationManager::~UDPCommunicationManager()
{
    release();
}

void UDPCommunicationManager::init()
{
    setUserName(_T("UDPCommunicationManager"));

    mec = new MECComponent;
    mec->setUser(this);

    commConfig = new CommunicationConfig;
    commConfig->setIni(_T("CommLinkInfo.ini"));

    tstring schemaPath = current_path().c_str();
    schemaPath += _T("\\..\\SchemaRegistryData.xml");
    nomParser = make_unique<NOMParser>();
    nomParser->setNOMFile(schemaPath);
    nomParser->parseNote();
    const auto noteMap = nomParser->getNoteMap();
    nomParser->parseDataType();
    const auto dataTypeMap = nomParser->getDataTypeMap();

    tstring nomPath = current_path().c_str();
    nomPath += _T("\\");
    nomPath += getUserName();
    nomPath += _T(".xml");
    nomParser->setNOMFile(nomPath);

    if (nomParser->parse(dataTypeMap, noteMap))
    {
        for (auto* message : nomParser->getMessageList())
        {
            commMsgHandler.setIDNameTable(message->getMessageID(), message->getName());
        }
    }

    funcMapInit();
}

void UDPCommunicationManager::release()
{
    if (commInterface != nullptr)
    {
        commInterface->releaseNetEnv(commConfig);
        delete commInterface;
        commInterface = nullptr;
    }

    delete commConfig;
    commConfig = nullptr;
    delete mec;
    mec = nullptr;
    meb = nullptr;
    funcMap.clear();
}

shared_ptr<NOM> UDPCommunicationManager::registerMsg(tstring msgName)
{
    auto nomMsg = mec->registerMsg(msgName);
    registeredMsg.emplace(nomMsg->getInstanceID(), nomMsg);
    return nomMsg;
}

void UDPCommunicationManager::discoverMsg(shared_ptr<NOM> nomMsg)
{
    discoveredMsg.emplace(nomMsg->getInstanceID(), nomMsg);
    if (commInterface != nullptr)
    {
        commInterface->registerCommMsg(nomMsg);
    }
}

void UDPCommunicationManager::updateMsg(shared_ptr<NOM> nomMsg)
{
    const unsigned int objectId = getObjectInstanceID(nomMsg);
    if (objectId > 0)
    {
        nomMsg->setInstanceID(objectId);
        mec->updateMsg(nomMsg);
    }
}

void UDPCommunicationManager::reflectMsg(shared_ptr<NOM> nomMsg)
{
    if (commInterface != nullptr)
    {
        commInterface->updateCommMsg(nomMsg);
    }
}

void UDPCommunicationManager::deleteMsg(shared_ptr<NOM> nomMsg)
{
    mec->deleteMsg(nomMsg);
    registeredMsg.erase(nomMsg->getInstanceID());
}

void UDPCommunicationManager::removeMsg(shared_ptr<NOM> nomMsg)
{
    discoveredMsg.erase(nomMsg->getInstanceID());
}

void UDPCommunicationManager::sendMsg(shared_ptr<NOM> nomMsg)
{
    mec->sendMsg(nomMsg);
}

void UDPCommunicationManager::recvMsg(shared_ptr<NOM> nomMsg)
{
    const auto handler = funcMap.find(nomMsg->getName());
    if (handler != funcMap.end())
    {
        handler->second(nomMsg);
    }
}

void UDPCommunicationManager::setUserName(tstring userName)
{
    name = std::move(userName);
}

tstring UDPCommunicationManager::getUserName()
{
    return name;
}

void UDPCommunicationManager::setData(void*)
{
}

bool UDPCommunicationManager::start()
{
    if (commInterface != nullptr)
    {
        return true;
    }

    commInterface = new NCommInterface(this);
    commInterface->setMEBComponent(meb);
    MessageProcessor processor = bind(
        &UDPCommunicationManager::processRecvMessage,
        this,
        placeholders::_1,
        placeholders::_2);
    commConfig->setMsgProcessor(processor);
    commInterface->initNetEnv(commConfig);

    for (const auto& [instanceId, nomMsg] : discoveredMsg)
    {
        commInterface->registerCommMsg(nomMsg);
    }

    for (auto* message : nomParser->getObjectList())
    {
        if (message->getSharing() == ESharing::ENUM_SHARING_PUBLISHSUBSCRIBE ||
            message->getSharing() == ESharing::ENUM_SHARING_PUBLISH)
        {
            registerMsg(message->getName());
        }
    }
    return true;
}

bool UDPCommunicationManager::stop()
{
    if (commInterface != nullptr)
    {
        commInterface->releaseNetEnv(commConfig);
        delete commInterface;
        commInterface = nullptr;
    }
    return true;
}

void UDPCommunicationManager::setMEBComponent(IMEBComponent* realMEB)
{
    meb = realMEB;
    mec->setMEB(meb);
}

void UDPCommunicationManager::funcMapInit()
{
    funcMap.emplace(
        _T("Scenario"),
        bind(&UDPCommunicationManager::recvScenario, this, placeholders::_1));
    funcMap.emplace(
        _T("StartSimulation"),
        bind(&UDPCommunicationManager::recvStartSimulation, this, placeholders::_1));
    funcMap.emplace(
        _T("Stop"),
        bind(&UDPCommunicationManager::recvStop, this, placeholders::_1));
    funcMap.emplace(
        _T("ATSInterceptionResult"),
        bind(&UDPCommunicationManager::recvATSInterceptionResult, this, placeholders::_1));
    funcMap.emplace(
        _T("InnerAirThreatInfoToComm"),
        bind(&UDPCommunicationManager::recvInnerAirThreatInfo, this, placeholders::_1));
}

void UDPCommunicationManager::recvScenario(shared_ptr<NOM> nomMsg)
{
    auto innerMessage = meb->getNOMInstance(name, _T("InnerSendScenario"));
    if (!innerMessage)
    {
        return;
    }

    for (std::size_t targetIndex = 0; targetIndex < kTargetCount; ++targetIndex)
    {
        std::uint32_t speedValue = 0;
        if (const auto value = nomMsg->getValue(makeSceneSpeedPath(targetIndex)))
        {
            speedValue = value->toUInt();
        }
        NUInteger speed(speedValue);
        innerMessage->setValue(makeSceneSpeedPath(targetIndex), &speed);

        for (std::size_t pointIndex = 0; pointIndex < kRoutePointCount; ++pointIndex)
        {
            double xValue = 0.0;
            double yValue = 0.0;
            double zValue = 0.0;
            if (const auto value = nomMsg->getValue(makeScenePath(targetIndex, pointIndex, _T("x")))) xValue = value->toDouble();
            if (const auto value = nomMsg->getValue(makeScenePath(targetIndex, pointIndex, _T("y")))) yValue = value->toDouble();
            if (const auto value = nomMsg->getValue(makeScenePath(targetIndex, pointIndex, _T("z")))) zValue = value->toDouble();

            NDouble x(xValue);
            NDouble y(yValue);
            NDouble z(zValue);
            innerMessage->setValue(makeScenePath(targetIndex, pointIndex, _T("x")), &x);
            innerMessage->setValue(makeScenePath(targetIndex, pointIndex, _T("y")), &y);
            innerMessage->setValue(makeScenePath(targetIndex, pointIndex, _T("z")), &z);
        }
    }
    mec->sendMsg(innerMessage);
}

void UDPCommunicationManager::recvStartSimulation(shared_ptr<NOM> nomMsg)
{
    const auto startFlag = nomMsg->getValue(_T("startFlag"));
    if (!startFlag || startFlag->toUInt() != 1)
    {
        return;
    }

    if (auto innerMessage = meb->getNOMInstance(name, _T("InnerStartSimulation")))
    {
        mec->sendMsg(innerMessage);
    }
}

void UDPCommunicationManager::recvStop(shared_ptr<NOM> nomMsg)
{
    const auto stopFlag = nomMsg->getValue(_T("stopFlag"));
    if (!stopFlag || stopFlag->toUInt() != 1)
    {
        return;
    }

    if (auto innerMessage = meb->getNOMInstance(name, _T("InnerStopSimulation")))
    {
        mec->sendMsg(innerMessage);
    }
}

void UDPCommunicationManager::recvATSInterceptionResult(shared_ptr<NOM> nomMsg)
{
    auto innerMessage = meb->getNOMInstance(name, _T("InnerAirThreatDetonationToATM"));
    if (!innerMessage)
    {
        return;
    }

    std::uint32_t targetIdValue = 0;
    std::uint32_t missionFlagValue = 1;
    if (const auto value = nomMsg->getValue(_T("targetID"))) targetIdValue = value->toUInt();
    if (const auto value = nomMsg->getValue(_T("missionFlag"))) missionFlagValue = value->toUInt();
    NUInteger targetId(targetIdValue);
    NUInteger missionFlag(missionFlagValue);
    innerMessage->setValue(_T("targetID"), &targetId);
    innerMessage->setValue(_T("missionFlag"), &missionFlag);
    mec->sendMsg(innerMessage);
}

void UDPCommunicationManager::recvInnerAirThreatInfo(shared_ptr<NOM> nomMsg)
{
    if (commInterface == nullptr)
    {
        return;
    }

    auto externalMessage = meb->getNOMInstance(name, _T("ATSStatus"));
    if (!externalMessage)
    {
        return;
    }

    NUShort messageId(static_cast<ushort>(ICD_MessageID::ATSStatus));
    externalMessage->setValue(_T("Header.MessageID"), &messageId);

    std::uint32_t statusValue = 0;
    if (const auto value = nomMsg->getValue(_T("status"))) statusValue = value->toUInt();
    NUInteger status(statusValue);
    externalMessage->setValue(_T("status"), &status);

    for (std::size_t index = 0; index < kTargetCount; ++index)
    {
        double xValue = 0.0;
        double yValue = 0.0;
        double zValue = 0.0;
        std::uint32_t speedValue = 0;
        std::uint32_t targetIdValue = static_cast<std::uint32_t>(index);
        std::uint32_t atsStatusValue = 0;

        if (const auto value = nomMsg->getValue(makeTargetPath(index, _T("ATSPos.x")))) xValue = value->toDouble();
        if (const auto value = nomMsg->getValue(makeTargetPath(index, _T("ATSPos.y")))) yValue = value->toDouble();
        if (const auto value = nomMsg->getValue(makeTargetPath(index, _T("ATSPos.z")))) zValue = value->toDouble();
        if (const auto value = nomMsg->getValue(makeTargetPath(index, _T("speed")))) speedValue = value->toUInt();
        if (const auto value = nomMsg->getValue(makeTargetPath(index, _T("targetId")))) targetIdValue = value->toUInt();
        if (const auto value = nomMsg->getValue(makeTargetPath(index, _T("atsStatus")))) atsStatusValue = value->toUInt();

        NDouble x(xValue);
        NDouble y(yValue);
        NDouble z(zValue);
        NUInteger speed(speedValue);
        NUInteger targetId(targetIdValue);
        NUInteger atsStatus(atsStatusValue);
        externalMessage->setValue(makeTargetPath(index, _T("ATSPos.x")), &x);
        externalMessage->setValue(makeTargetPath(index, _T("ATSPos.y")), &y);
        externalMessage->setValue(makeTargetPath(index, _T("ATSPos.z")), &z);
        externalMessage->setValue(makeTargetPath(index, _T("speed")), &speed);
        externalMessage->setValue(makeTargetPath(index, _T("targetId")), &targetId);
        externalMessage->setValue(makeTargetPath(index, _T("atsStatus")), &atsStatus);
    }
    commInterface->sendCommMsg(externalMessage);
}

void UDPCommunicationManager::sendInnerMsg(shared_ptr<NOM> nomMsg)
{
    const auto handler = funcMap.find(nomMsg->getName());
    if (handler != funcMap.end())
    {
        handler->second(nomMsg);
        tcout << _T("[UDP RX] ATS handler executed. name=")
              << nomMsg->getName() << std::endl;
    }
    else
    {
        tcout << _T("[UDP RX] No ATS handler; message ignored. name=")
              << nomMsg->getName() << std::endl;
    }
}

void UDPCommunicationManager::processRecvMessage(unsigned char* data, int size)
{
    const auto idPosition = commConfig->getHeaderIDPos();
    const auto idSize = commConfig->getHeaderIDSize();

    if (data == nullptr || idSize != 2 || size < static_cast<int>(idPosition + idSize))
    {
        tcerr << _T("[UDP RX] Invalid header. idPosition=") << idPosition
              << _T(", idSize=") << idSize
              << _T(", packetSize=") << size << std::endl;
        return;
    }

    unsigned short networkMessageId = 0;
    memcpy(&networkMessageId, data + idPosition, idSize);
    const unsigned short messageId = ntohs(networkMessageId);
    const tstring messageName = commMsgHandler.getMsgName(messageId);

    if (messageName.empty())
    {
        tcerr << _T("[UDP RX] Message ID is not defined in UDPCommunicationManager.xml.")
              << std::endl;
        return;
    }

    const bool isOcToAtsMessage =
        messageName == _T("Scenario") ||
        messageName == _T("StartSimulation") ||
        messageName == _T("ATSInterceptionResult") ||
        messageName == _T("Stop");

    // Multicast packets sent by RSS/MLS/MSS are received by ATS as well.
    // Ignore those known messages silently because ATS only processes OC commands.
    if (!isOcToAtsMessage)
    {
        return;
    }

    tcout << _T("[UDP RX] Datagram received. size=") << size << std::endl;
    tcout << _T("[UDP RX] Message ID=0x")
          << std::hex << std::uppercase << messageId
          << std::dec << std::nouppercase
          << _T(", name=") << messageName << std::endl;

    auto nomMsg = meb->getNOMInstance(name, messageName);
    if (!nomMsg)
    {
        tcerr << _T("[UDP RX] NOM instance is unavailable. name=")
              << messageName << std::endl;
        return;
    }

    try
    {
        if (nomMsg->getType() == ENOMType::NOM_TYPE_OBJECT)
        {
            nomMsg->deserialize(data, size);
            updateMsg(nomMsg);
            tcout << _T("[UDP RX] Object updated. name=")
                  << messageName << std::endl;
        }
        else
        {
            auto receivedMessage = nomMsg->clone();
            receivedMessage->deserialize(data, size);
            receivedMessage->setOwner(name);
            sendInnerMsg(receivedMessage);
            tcout << _T("[UDP RX] Interaction deserialized. name=")
                  << messageName << std::endl;
        }
    }
    catch (const std::exception&)
    {
        tcerr << _T("[UDP RX] Deserialization failed. name=")
              << messageName << std::endl;
    }
    catch (...)
    {
        tcerr << _T("[UDP RX] Deserialization failed with an unknown exception. name=")
              << messageName << std::endl;
    }
}

unsigned int UDPCommunicationManager::getObjectInstanceID(shared_ptr<NOM> nomMsg)
{
    for (const auto& [instanceId, registered] : registeredMsg)
    {
        if (registered->getMessageID() == nomMsg->getMessageID())
        {
            return instanceId;
        }
    }
    return 0;
}

extern "C" BASEMGRDLL_API BaseManager* createObject()
{
    return new UDPCommunicationManager;
}

extern "C" BASEMGRDLL_API void deleteObject(BaseManager* userManager)
{
    delete userManager;
}
