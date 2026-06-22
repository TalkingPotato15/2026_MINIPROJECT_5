#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <map>
#include <functional>

using namespace nframework;
using namespace nom;

/**
 * @class  ScenarioManager
 * @brief  시나리오 배포 Manager
 *         - WPF에서 시나리오 입력 수신 (setData 또는 내부 메시지)
 *         - Scenario message(0x01) publish to UDPCommunicationManager
 */
class BASEMGRDLL_API ScenarioManager : public BaseManager
{
public:
	ScenarioManager(void);
	~ScenarioManager(void);

public:
	virtual std::shared_ptr<NOM> registerMsg(tstring) override;
	virtual void discoverMsg(std::shared_ptr<NOM>) override;
	virtual void updateMsg(std::shared_ptr<NOM>) override;
	virtual void reflectMsg(std::shared_ptr<NOM>) override;
	virtual void deleteMsg(std::shared_ptr<NOM>) override;
	virtual void removeMsg(std::shared_ptr<NOM>) override;
	virtual void sendMsg(std::shared_ptr<NOM>) override;
	virtual void recvMsg(std::shared_ptr<NOM>) override;
	virtual void setUserName(tstring) override;
	virtual tstring getUserName() override;
	virtual void setData(void*) override;
	virtual bool start() override;
	virtual bool stop() override;
	virtual void setMEBComponent(IMEBComponent*) override;

private:
	void initialize();
	void release();

private:
	IMEBComponent* meb = nullptr;
	MECComponent*  mec = nullptr;
	tstring        name;

	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;
};
