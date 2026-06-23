#pragma once

#include "MLSBaseModel.h"

class VerticalLauncherModel : public MLSBaseModel
{
public:
	void init() override;
	void setting(POSITION pos) override;
	void start() override;
	void stop() override;
	void update(double tick) override;
	int fireMissile(unsigned int targetID) override;
	MLS_STATUS mlsStatus() override;
	POSITION currentPosition() override;

private:
	static constexpr unsigned int MAX_HOT_INVENTORY = 4;
};

