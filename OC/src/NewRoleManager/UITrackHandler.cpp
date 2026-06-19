#include "UITrackHandler.h"
#include "NewRoleManagerIntelliVal.h"

using namespace intellival;
namespace gui = BaseEntity_PhysicalEntity_Munition_GUI;

UITrackHandler::UITrackHandler(BaseManager* userMgr) : userMgr(userMgr)
{
	initialize();
}

UITrackHandler::~UITrackHandler()
{
	release();
}

void
UITrackHandler::initialize()
{
	timer = &(NTimer::getInstance());
	time = 0;
}

void
UITrackHandler::release()
{

}

void
UITrackHandler::addTime(void *arg)
{
	time++;
}

std::shared_ptr<NOM>
UITrackHandler::discoverUITrack(std::shared_ptr<NOM> nomMsg)
{
	std::shared_ptr uiNom = userMgr->registerMsg(nomMsg->getName() + L"_GUI");
	registeredUIMsg.emplace(nomMsg->getInstanceID(), uiNom);
	uiNom->setValue(L"LogicalTime", &gui::v_LogicalTime(-1));
	return uiNom;
}

std::shared_ptr<NOM>
UITrackHandler::reflectUITrack(std::shared_ptr<NOM> nomMsg)
{
	auto UINom = registeredUIMsg[nomMsg->getInstanceID()];
	if (UINom == nullptr)
	{
		return nullptr;
	}

	//UINom->setValue(L"LogicalTime", &NUInteger(time));

	auto LogicalTime = UINom->getValue(L"LogicalTime")->toUInt();
	if(LogicalTime == -1)
		UINom->setValue(L"LogicalTime", &gui::v_LogicalTime(time));
	else
		UINom->setValue(L"LogicalTime", &gui::v_LogicalTime(LogicalTime + 1));
	
	auto pathList = nomMsg->getPathList();
	for (auto itr = pathList.begin(); itr != pathList.end(); itr++)
	{
		UINom->setValue(*itr, nomMsg->getValue(*itr));
	}

	return UINom;
}

std::shared_ptr<NOM>
UITrackHandler::removeUITrack(std::shared_ptr<NOM> nomMsg)
{
	auto UINom = registeredUIMsg[nomMsg->getInstanceID()];
	if (UINom == nullptr)
		return nullptr;

	UINom->setValue(L"LogicalTime", &gui::v_LogicalTime(time));
	auto pathList = nomMsg->getPathList();
	for (auto itr = pathList.begin(); itr != pathList.end(); itr++)
	{
		UINom->setValue(*itr, nomMsg->getValue(*itr));
	}
	registeredUIMsg.erase(nomMsg->getInstanceID());
	userMgr->removeMsg(UINom);

	return UINom;
}

void UITrackHandler::startTimer()
{
	time = 0;
	STDFUNCTION bindFunction;
	bindFunction = bind(&UITrackHandler::addTime, this, std::placeholders::_1);
	taskHandler = timer->addTask(E_TASK_TYPE::PERIODIC_TASK, 1000, bindFunction, nullptr);
}

void UITrackHandler::stopTimer()
{
	timer->removeTask(taskHandler);
	time = 0;
}