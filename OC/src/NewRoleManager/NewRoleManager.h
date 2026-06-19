#pragma once
#include <afxwin.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>
#include <nFramework/BaseManager.h>
#include "UITrackHandler.h"
#include <nFramework/Log4nF/Loggable.h>

using namespace nframework;
using namespace nom;
using namespace log4nf;

struct NOMInfo
{
	TCHAR MsgName[1024];
	unsigned int MsgID;
	unsigned int MsgInstanceID;
	int MsgLen;
};

class BASEMGRDLL_API NewRoleManager : public BaseManager
{
public:
	NewRoleManager(void);
	~NewRoleManager(void);

	// inherited from the BaseManager class
	std::shared_ptr<NOM> registerMsg(std::wstring) override;
	void discoverMsg(std::shared_ptr<NOM>) override;
	void updateMsg(std::shared_ptr<NOM>) override;
	void reflectMsg(std::shared_ptr<NOM>) override;
	void deleteMsg(std::shared_ptr<NOM>) override;
	void removeMsg(std::shared_ptr<NOM>) override;
	void sendMsg(std::shared_ptr<NOM>) override;
	void recvMsg(std::shared_ptr<NOM>) override;
	void setUserName(std::wstring) override;
	tstring getUserName() override;
	void setData(void*) override;
	bool start() override;
	bool stop() override;
	void setMEBComponent(IMEBComponent*) override;

private:
	void initialize();
	void release();

private:
	IMEBComponent* meb;
	tstring managerName;
	std::map<unsigned int, std::shared_ptr<NOM>> registeredMsg;
	std::map<unsigned int, std::shared_ptr<NOM>> discoveredMsg;

	HWND winHandle;
	std::unique_ptr<UITrackHandler> uiTrackHandler;

	static inline Loggable l{ L"NewRoleManager" };

	// ※※※※ MEC가 가장 먼저 소멸되어야 함. ※※※※
	std::unique_ptr<MECComponent> mec;
};


