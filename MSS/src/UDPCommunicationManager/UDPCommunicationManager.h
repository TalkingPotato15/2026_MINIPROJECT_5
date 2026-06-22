#pragma once
#include <nFramework/mec/MECComponent.h>
#include <nFramework/comm/NCommInterface.h>
#include "CommMessageHandler.h"
#include <nFramework/nom/NOMParser.h>
#include <nFramework/nLineStream/NLineStreamMain.h>

#include "MFRSHeader.h"

using namespace std;
using namespace nframework;
using namespace nom;
using namespace ncomm;

class BASEMGRDLL_API UDPCommunicationManager : public BaseManager
{
public:
	UDPCommunicationManager(void);
	~UDPCommunicationManager(void);

public:
	// inherited from the BaseManager class
	virtual shared_ptr<NOM> registerMsg(tstring) override;
	virtual void discoverMsg(shared_ptr<NOM>) override;
	virtual void updateMsg(shared_ptr<NOM>) override;
	virtual void reflectMsg(shared_ptr<NOM>) override;
	virtual void deleteMsg(shared_ptr<NOM>) override;
	virtual void removeMsg(shared_ptr<NOM>) override;
	virtual void sendMsg(shared_ptr<NOM>) override;
	virtual void recvMsg(shared_ptr<NOM>) override;
	virtual void setUserName(tstring) override;
	virtual tstring getUserName() override;
	virtual void setData(void*) override;
	virtual bool start() override;
	virtual bool stop() override;
	virtual void setMEBComponent(IMEBComponent*) override;

public:
	void processRecvMessage(unsigned char* data, int size);
	unsigned int getObjectInstanceID(shared_ptr<NOM> nomMsg);

private:
	void init();
	void release();
	void sendInnerMsg(shared_ptr<NOM> nomMsg);
	void funcMapInit();

private:
	// 네트워크 수신 (OC / MLS → MSS)
	void recvScenario(shared_ptr<NOM> nomMsg);              // 0x01 시나리오 수신
	void recvStartSimulation(shared_ptr<NOM> nomMsg);       // 0x06 모의 시작 수신
	void recvIgnitionCommand(shared_ptr<NOM> nomMsg);       // [추가] 0x0a 발사 명령 수신 (MLS → MSS)
	void recvSimulatorState(shared_ptr<NOM> nomMsg);        // [추가] 0x0b ATS 표적 위치 수신 (RSS → MSS)
	void recvMSSInterceptionResult(shared_ptr<NOM> nomMsg); // [추가] 0x0f 요격 결과 수신 (OC → MSS)
	void recvStop(shared_ptr<NOM> nomMsg);                  // 0x10 모의 중지 수신
	void recvMissionFailed(shared_ptr<NOM> nomMsg);         // 0x11 임무 실패 수신

	// 내부 공통 헬퍼
	void recvStopSimulation(shared_ptr<NOM> nomMsg);        // [추가] InnerStopSimulation 전달 공통 처리

	// 내부 메시지 수신 (Inner)
	void recvInnerSendScenarioAck(shared_ptr<NOM> nomMsg);    // Inner 0x22
	void recvInnerStartSimulationAck(shared_ptr<NOM> nomMsg); // Inner 0x25
	void recvInnerStopSimulationAck(shared_ptr<NOM> nomMsg);  // Inner 0x28
	void recvInnerSimulatorStateComm(shared_ptr<NOM> nomMsg); // Inner 0x20 모의기 상태
	void recvInnerMissileInfoToComm(shared_ptr<NOM> nomMsg);  // [추가] Inner 0x60 → MSSStatus (0x04) 발행

public:
	std::unique_ptr<NOMParser> nomParser;

private:
	IMEBComponent* meb;
	MECComponent* mec;
	tstring name;
	map<unsigned int, shared_ptr<NOM>> registeredMsg;
	map<unsigned int, shared_ptr<NOM>> discoveredMsg;
	map<tstring, function<void(shared_ptr<NOM>)>> funcMap;

	CommunicationInterface* commInterface;
	CommunicationConfig* commConfig;
	CommMessageHandler commMsgHandler;
	tstring routeString;
};