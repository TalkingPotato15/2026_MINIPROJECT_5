#include "NOMMessageHandler.h"
#include "ATSMessageProcessor.h"

void
NOMMessageHandler::initialize()
{
	// if necessary
	IMessageProcessor* messageProcessor = new ATSMessageProcessor;
	messageIDMap.insert(std::make_pair("msgID", messageProcessor));
}

void
NOMMessageHandler::release()
{

}