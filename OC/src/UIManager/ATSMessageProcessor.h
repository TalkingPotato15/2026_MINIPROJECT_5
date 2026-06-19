#pragma once
#include "IMessageProcessor.h"

class ATSMessageProcessor : public IMessageProcessor
{
public:
	ATSMessageProcessor() = default;
	~ATSMessageProcessor() = default;

public:
	// inherited function ±¸Çö
	void processMessage() override;
};

