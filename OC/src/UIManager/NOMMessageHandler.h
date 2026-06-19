#pragma once
#include "IMessageProcessor.h"
#include <map>
#include <string>

class NOMMessageHandler
{
public : 
	NOMMessageHandler() = default;
	~NOMMessageHandler() = default;

private:
	void initialize();
	void release();

private:
	std::map<std::string, IMessageProcessor*> messageIDMap;
};

