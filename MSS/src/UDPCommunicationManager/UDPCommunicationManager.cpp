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
    mec = new MECComponent;
    mec->setUser(this);
    commConfig = new CommunicationConfig;
    commConfig->setIni(_T("CommLinkInfo.ini"));
    tstring schRegFilePath = current_path().c_str();
    schRegFilePath += _T("\\..\\SchemaRegistryData.xml");
    nomParser = std::make_unique<NOMParser>();
    nomParser->setNOMFile(schRegFilePath);
    nomParser->parseNote();
    auto noteMap = nomParser->getNoteMap();
    nomParser->parseDataType();
    auto dataTypeMap = nomParser->getDataTypeMap();
    tstring nomFilePath = current_path().c_str();
    nomFilePath += _T("\\");
    nomFilePath += getUserName();
    nomFilePath += _T(".xml");
    nomParser->setNOMFile(nomFilePath);
    if (nomParser->parse(dataTypeMap, noteMap))
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
    if (itr != discoveredMsg.end())
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
    mec->sendMsg(nomMsg);
}
void
UDPCommunicationManager::recvMsg(shared_ptr<NOM> nomMsg)
{
    if (auto iter = funcMap.find(nomMsg->getName()); iter != funcMap.end())
    {
        iter->second(nomMsg);
    }
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
    commInterface = new NCommInterface(this);
    commInterface->setMEBComponent(meb);
    MessageProcessor msgProcessor = bind(&UDPCommunicationManager::processRecvMessage, this, placeholders::_1, placeholders::_2);
    commConfig->setMsgProcessor(msgProcessor);
    commInterface->initNetEnv(commConfig);
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
    delete commInterface;
    return true;
}
void
UDPCommunicationManager::setMEBComponent(IMEBComponent* realMEB)
{
    meb = realMEB;
    mec->setMEB(meb);
}
/************************************************************************
    funcMapInit - MSS 수신 메시지 등록
************************************************************************/
void UDPCommunicationManager::funcMapInit()
{
    function<void(shared_ptr<NOM>)> msgProc;
    // ── 네트워크 수신 메시지 (OC / MLS → MSS) ──────────────────────────
    msgProc = bind(&UDPCommunicationManager::recvScenario, this, placeholders::_1);
    funcMap.insert({ _T("Scenario"), msgProc });                     // 0x01
    msgProc = bind(&UDPCommunicationManager::recvStartSimulation, this, placeholders::_1);
    funcMap.insert({ _T("StartSimulation"), msgProc });              // 0x06
    // [추가] IgnitionCommand (0x0a) : MLS → MSS 발사 명령
    msgProc = bind(&UDPCommunicationManager::recvIgnitionCommand, this, placeholders::_1);
    funcMap.insert({ _T("IgnitionCommand"), msgProc });              // 0x0a
    // [추가] SimulatorState (0x0b) : RSS → MSS ATS 표적 위치 업링크
    msgProc = bind(&UDPCommunicationManager::recvSimulatorState, this, placeholders::_1);
    funcMap.insert({ _T("SimulatorState"), msgProc });               // 0x0b
    // [추가] MSSInterceptionResult (0x0f) : OC → MSS 요격 결과
    msgProc = bind(&UDPCommunicationManager::recvMSSInterceptionResult, this, placeholders::_1);
    funcMap.insert({ _T("MSSInterceptionResult"), msgProc });        // 0x0f
    msgProc = bind(&UDPCommunicationManager::recvStop, this, placeholders::_1);
    funcMap.insert({ _T("Stop"), msgProc });                         // 0x10
    msgProc = bind(&UDPCommunicationManager::recvMissionFailed, this, placeholders::_1);
    funcMap.insert({ _T("MissionFailed"), msgProc });                // 0x11
    // ── 내부 메시지 (Inner) ─────────────────────────────────────────────
    msgProc = bind(&UDPCommunicationManager::recvInnerSimulatorStateComm, this, placeholders::_1);
    funcMap.insert({ _T("SimulatorStateToComm"), msgProc });         // Inner 0x20
    msgProc = bind(&UDPCommunicationManager::recvInnerSendScenarioAck, this, placeholders::_1);
    funcMap.insert({ _T("InnerSendScenarioAck"), msgProc });         // Inner 0x22
    msgProc = bind(&UDPCommunicationManager::recvInnerStartSimulationAck, this, placeholders::_1);
    funcMap.insert({ _T("InnerStartSimulationAck"), msgProc });      // Inner 0x25
    msgProc = bind(&UDPCommunicationManager::recvInnerStopSimulationAck, this, placeholders::_1);
    funcMap.insert({ _T("InnerStopSimulationAck"), msgProc });       // Inner 0x28
    // [추가] InnerMissileInfoToComm (Inner 0x60) : 유도탄 상태 → MSSStatus (0x04) 발행
    msgProc = bind(&UDPCommunicationManager::recvInnerMissileInfoToComm, this, placeholders::_1);
    funcMap.insert({ _T("InnerMissileInfoToComm"), msgProc });       // Inner 0x60
}
/************************************************************************
    Network Receive Handlers
************************************************************************/
// 0x01 Scenario : OC → MSS (발사대 위치, 레이더 위치 추출)
void UDPCommunicationManager::recvScenario(shared_ptr<NOM> nomMsg)
{
    auto nomMsg_new = meb->getNOMInstance(name, _T("InnerSendScenario"));
    if (!nomMsg_new.get())
    {
        tcerr << _T("[UDPCommunicationManager] InnerSendScenario NOM is undefined.") << endl;
        return;
    }
    // WayPoint는 MSS 모델 내부에서 처리하므로 0으로 초기화
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
    // MSS 발사대 위치 (mlsPos)
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
    // 레이더(RSS) 위치 참조용 (rssPos)
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
    this->sendMsg(nomMsg_new);
}
// 0x06 StartSimulation : OC → MSS
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
// [추가] 0x0a IgnitionCommand : MLS → MSS 발사 명령
void UDPCommunicationManager::recvIgnitionCommand(shared_ptr<NOM> nomMsg)
{
    auto nomMsg_new = meb->getNOMInstance(name, _T("InnerFireMissileToMiss"));
    if (!nomMsg_new.get())
    {
        tcerr << _T("[UDPCommunicationManager] InnerFireMissileToMiss NOM is undefined.") << endl;
        return;
    }
    if (auto value = nomMsg->getValue(_T("missileID")))
    {
        NUInteger missileID(value->toUInt());
        nomMsg_new->setValue(_T("missileID"), &missileID);
    }
    if (auto value = nomMsg->getValue(_T("targetID")))
    {
        NUInteger targetID(value->toUInt());
        nomMsg_new->setValue(_T("targetID"), &targetID);
    }
    if (auto value = nomMsg->getValue(_T("launchPos.x")))
    {
        NDouble x(value->toDouble());
        nomMsg_new->setValue(_T("launchPos.x"), &x);
    }
    if (auto value = nomMsg->getValue(_T("launchPos.y")))
    {
        NDouble y(value->toDouble());
        nomMsg_new->setValue(_T("launchPos.y"), &y);
    }
    if (auto value = nomMsg->getValue(_T("launchPos.z")))
    {
        NDouble z(value->toDouble());
        nomMsg_new->setValue(_T("launchPos.z"), &z);
    }
    this->sendMsg(nomMsg_new);
}
// [추가] 0x0b SimulatorState : RSS → MSS ATS 표적 위치 업링크
void UDPCommunicationManager::recvSimulatorState(shared_ptr<NOM> nomMsg)
{
    auto nomMsg_new = meb->getNOMInstance(name, _T("InnerUplinkInfoToMiss"));
    if (!nomMsg_new.get())
    {
        tcerr << _T("[UDPCommunicationManager] InnerUplinkInfoToMiss NOM is undefined.") << endl;
        return;
    }
    if (auto value = nomMsg->getValue(_T("SimulatorID")))
    {
        NUShort simulatorID(value->toUShort());
        nomMsg_new->setValue(_T("SimulatorID"), &simulatorID);
    }
    this->sendMsg(nomMsg_new);
}
// [추가] 0x0f MSSInterceptionResult : OC → MSS 요격 결과
void UDPCommunicationManager::recvMSSInterceptionResult(shared_ptr<NOM> nomMsg)
{
    auto nomMsg_new = meb->getNOMInstance(name, _T("InnerMissileDetonationToMiss"));
    if (!nomMsg_new.get())
    {
        tcerr << _T("[UDPCommunicationManager] InnerMissileDetonationToMiss NOM is undefined.") << endl;
        return;
    }
    if (auto value = nomMsg->getValue(_T("missileID")))
    {
        NUInteger missileID(value->toUInt());
        nomMsg_new->setValue(_T("missileID"), &missileID);
    }
    if (auto value = nomMsg->getValue(_T("isIntercepted")))
    {
        NBool isIntercepted(value->toByte());
        nomMsg_new->setValue(_T("isIntercepted"), &isIntercepted);
    }
    this->sendMsg(nomMsg_new);
}
// 0x10 Stop : OC → MSS
void UDPCommunicationManager::recvStop(shared_ptr<NOM> nomMsg)
{
    recvStopSimulation(nomMsg);
}
// 0x11 MissionFailed : OC → MSS
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
// 모의 중지 공통 처리 (InnerStopSimulation 전달)
void UDPCommunicationManager::recvStopSimulation(shared_ptr<NOM> nomMsg)
{
    auto nomMsg_new = meb->getNOMInstance(name, _T("InnerStopSimulation"));
    this->sendMsg(nomMsg_new);
}
/************************************************************************
    Inner Message Handlers
************************************************************************/
// Inner 0x20 → SimulatorState (0x0b) 외부 송신 : MSS 모의기 상태 보고
void UDPCommunicationManager::recvInnerSimulatorStateComm(shared_ptr<NOM> nomMsg)
{
    auto nomMsg_new = meb->getNOMInstance(name, _T("SimulatorState"));
    NUShort msgID = NUShort((ushort)ICD_MessageID::SimulatorState);
    NUShort simulatorID = nomMsg->getValue(_T("SimulatorID"))->toUShort();
    nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
    nomMsg_new->setValue(_T("SimulatorID"), &simulatorID);
    commInterface->sendCommMsg(nomMsg_new);
}
// Inner 0x22 SendScenarioAck : 새 OC ICD에 Ack 없으므로 로그만 출력
void UDPCommunicationManager::recvInnerSendScenarioAck(shared_ptr<NOM> nomMsg)
{
    tcout << _T("[UDPCommunicationManager] OC ICD has no SendScenarioAck message. Skip external send.") << endl;
}
// Inner 0x25 StartSimulationAck : 새 OC ICD에 Ack 없으므로 로그만 출력
void UDPCommunicationManager::recvInnerStartSimulationAck(shared_ptr<NOM> nomMsg)
{
    tcout << _T("[UDPCommunicationManager] OC ICD has no StartSimulationAck message. Skip external send.") << endl;
}
// Inner 0x28 StopSimulationAck : 새 OC ICD에 Ack 없으므로 로그만 출력
void UDPCommunicationManager::recvInnerStopSimulationAck(shared_ptr<NOM> nomMsg)
{
    tcout << _T("[UDPCommunicationManager] OC ICD has no StopSimulationAck message. Skip external send.") << endl;
}
// [추가] Inner 0x60 InnerMissileInfoToComm → MSSStatus (0x04) 외부 송신
void UDPCommunicationManager::recvInnerMissileInfoToComm(shared_ptr<NOM> nomMsg)
{
    auto nomMsg_new = meb->getNOMInstance(name, _T("MSSStatus"));
    if (!nomMsg_new.get())
    {
        tcerr << _T("[UDPCommunicationManager] MSSStatus NOM is undefined.") << endl;
        return;
    }
    NUShort msgID((ushort)ICD_MessageID::MSSStatus);
    nomMsg_new->setValue(_T("Header.MessageID"), &msgID);
    if (auto value = nomMsg->getValue(_T("status")))
    {
        NInteger status(value->toInt());
        nomMsg_new->setValue(_T("status"), &status);
    }
    if (auto cntValue = nomMsg->getValue(_T("missileCount")))
    {
        NUInteger missileCount(cntValue->toUInt());
        nomMsg_new->setValue(_T("missileCount"), &missileCount);
        uint32_t count = cntValue->toUInt();
        for (uint32_t i = 0; i < count && i < 4; i++)
        {
            tstring idx = _T("[") + to_tstring(i) + _T("]");
            if (auto v = nomMsg->getValue(_T("missileInfo") + idx + _T(".missileID")))
            {
                NUInteger val(v->toUInt());
                nomMsg_new->setValue(_T("missileInfo") + idx + _T(".missileID"), &val);
            }
            if (auto v = nomMsg->getValue(_T("missileInfo") + idx + _T(".targetID")))
            {
                NUInteger val(v->toUInt());
                nomMsg_new->setValue(_T("missileInfo") + idx + _T(".targetID"), &val);
            }
            if (auto v = nomMsg->getValue(_T("missileInfo") + idx + _T(".pos.x")))
            {
                NDouble val(v->toDouble());
                nomMsg_new->setValue(_T("missileInfo") + idx + _T(".pos.x"), &val);
            }
            if (auto v = nomMsg->getValue(_T("missileInfo") + idx + _T(".pos.y")))
            {
                NDouble val(v->toDouble());
                nomMsg_new->setValue(_T("missileInfo") + idx + _T(".pos.y"), &val);
            }
            if (auto v = nomMsg->getValue(_T("missileInfo") + idx + _T(".pos.z")))
            {
                NDouble val(v->toDouble());
                nomMsg_new->setValue(_T("missileInfo") + idx + _T(".pos.z"), &val);
            }
            if (auto v = nomMsg->getValue(_T("missileInfo") + idx + _T(".mssStatus")))
            {
                NInteger val(v->toInt());
                nomMsg_new->setValue(_T("missileInfo") + idx + _T(".mssStatus"), &val);
            }
            if (auto v = nomMsg->getValue(_T("missileInfo") + idx + _T(".isIntercepted")))
            {
                NBool val(v->toByte());
                nomMsg_new->setValue(_T("missileInfo") + idx + _T(".isIntercepted"), &val);
            }
        }
    }
    commInterface->sendCommMsg(nomMsg_new);
}
/************************************************************************
    Utility
************************************************************************/
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
    auto IDPos = commConfig->getHeaderIDPos();
    auto IDSize = commConfig->getHeaderIDSize();
    auto msgID = 0;
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