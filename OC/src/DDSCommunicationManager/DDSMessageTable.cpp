#include "DDSMessageTable.h"

/************************************************************************
	constructor / destructor
************************************************************************/
DDSMessageTable::DDSMessageTable(void)
{
	initialize();
}

DDSMessageTable::~DDSMessageTable(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
DDSMessageTable::initialize()
{
	createMsgNameTable();
}

void
DDSMessageTable::release()
{
	removeMsgNameTable();
}

/************************************************************************
	these methods for managing messages
************************************************************************/
void
DDSMessageTable::createMsgNameTable()
{
	IniHandler iniHandler;
	iniHandler.readIni(L"DDSCommunicationManager/ICD.ini");

	unsigned int numOfMessages = iniHandler.readInteger(L"ICD", L"Count");

	for (unsigned int cnt = 1; cnt <= numOfMessages; cnt++)
	{
		tstringstream msgPrefix;
		msgPrefix << L"Msg_" << cnt;

		std::wstring msgIdx;
		msgPrefix >> msgIdx;

		unsigned int msgID = iniHandler.readInteger(msgIdx, L"ID");
		std::wstring msgName = iniHandler.readString(msgIdx, L"Name");

		ID_NameTable.emplace(msgID, msgName);
	}
}

void
DDSMessageTable::removeMsgNameTable()
{
	ID_NameTable.clear();
}

std::wstring
DDSMessageTable::getMsgName(unsigned int msgID)
{
	std::wstring msgName;
	auto itr = ID_NameTable.find(msgID);

	if(itr != ID_NameTable.end())
	{
		msgName = itr->second;
	}
	else
	{
		msgName = L"";
	}

	return msgName;
}
