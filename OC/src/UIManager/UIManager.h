#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <map>
#include <functional>

using namespace nframework;
using namespace nom;

/**
 * @class  UIManager
 * @brief  WPF GUI ↔ nFramework 브릿지 Manager
 *         - WPF(NOMHandler)에서 송신 요청이 오면 해당 NOM을 내부 버스로 발행
 *         - 내부 버스에서 수신된 NOM을 WPF로 라우팅
 */
class BASEMGRDLL_API UIManager : public BaseManager
{
public:
	UIManager(void);
	~UIManager(void);

public:
	// inherited from the BaseManager class
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
	void funcMapInit();

	// 수신 메시지 처리 핸들러
	void onATSStatus(std::shared_ptr<NOM> nomMsg);
	void onRSSStatus(std::shared_ptr<NOM> nomMsg);
	void onMSSStatus(std::shared_ptr<NOM> nomMsg);
	void onMLSStatus(std::shared_ptr<NOM> nomMsg);
	void onTargetDetection(std::shared_ptr<NOM> nomMsg);
	void onTargetDestroyed(std::shared_ptr<NOM> nomMsg);

private:
	IMEBComponent* meb = nullptr;
	MECComponent*  mec = nullptr;
	tstring        name;

	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsgMap;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsgMap;

	// 메시지명 → 처리 함수 바인딩 맵
	std::map<tstring, std::function<void(std::shared_ptr<NOM>)>> funcMap;
};
