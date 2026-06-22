#pragma once

#include <nFramework/mec/MECComponent.h>
#include <nFramework/comm/NCommInterface.h>
#include <nFramework/nom/NOMParser.h>
#include <nFramework/nLineStream/NLineStreamMain.h>

#include <functional>
#include <map>
#include <memory>

#include "CommMessageHandler.h"
#include "MFRSHeader.h"

using namespace std;
using namespace nframework;
using namespace nom;
using namespace ncomm;

class BASEMGRDLL_API UDPCommunicationManager : public BaseManager
{
public:
    UDPCommunicationManager();
    ~UDPCommunicationManager() override;

    shared_ptr<NOM> registerMsg(tstring msgName) override;
    void discoverMsg(shared_ptr<NOM> nomMsg) override;
    void updateMsg(shared_ptr<NOM> nomMsg) override;
    void reflectMsg(shared_ptr<NOM> nomMsg) override;
    void deleteMsg(shared_ptr<NOM> nomMsg) override;
    void removeMsg(shared_ptr<NOM> nomMsg) override;
    void sendMsg(shared_ptr<NOM> nomMsg) override;
    void recvMsg(shared_ptr<NOM> nomMsg) override;
    void setUserName(tstring userName) override;
    tstring getUserName() override;
    void setData(void* data) override;
    bool start() override;
    bool stop() override;
    void setMEBComponent(IMEBComponent* realMEB) override;

    void processRecvMessage(unsigned char* data, int size);
    unsigned int getObjectInstanceID(shared_ptr<NOM> nomMsg);

private:
    void init();
    void release();
    void funcMapInit();
    void sendInnerMsg(shared_ptr<NOM> nomMsg);

    void recvScenario(shared_ptr<NOM> nomMsg);
    void recvStartSimulation(shared_ptr<NOM> nomMsg);
    void recvStop(shared_ptr<NOM> nomMsg);
    void recvATSInterceptionResult(shared_ptr<NOM> nomMsg);
    void recvInnerAirThreatInfo(shared_ptr<NOM> nomMsg);

public:
    unique_ptr<NOMParser> nomParser;

private:
    IMEBComponent* meb{ nullptr };
    MECComponent* mec{ nullptr };
    tstring name;
    map<unsigned int, shared_ptr<NOM>> registeredMsg;
    map<unsigned int, shared_ptr<NOM>> discoveredMsg;
    map<tstring, function<void(shared_ptr<NOM>)>> funcMap;

    CommunicationInterface* commInterface{ nullptr };
    CommunicationConfig* commConfig{ nullptr };
    CommMessageHandler commMsgHandler;
};
