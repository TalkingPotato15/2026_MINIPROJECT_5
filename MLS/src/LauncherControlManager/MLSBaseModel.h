#pragma once

#include "MLS_STRUCT.h"

class MLSBaseModel
{
public:
	MLSBaseModel() = default;
	~MLSBaseModel() = default;

	virtual void init() = 0;
	virtual void setting(POSITION pos) = 0;
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void update(double tick) = 0;
	virtual int fireMissile(unsigned int targetID) = 0;
	virtual MLS_STATUS mlsStatus() = 0;

protected:
	MLS_INFOMATION launcherInfo;
	POSITION currentPos;
	double currentTime;
	unsigned int currentStock;
	SIMULATION_STATUS simulationStatus;
};
