#pragma once

struct POSITION
{
	double x = 0;
	double y = 0;
	double z = 0;
};

enum class SIMULATION_STATUS : unsigned int
{
	IDLE,
	READY,
	RUNNING
};

enum class MSS_STATUS : unsigned int
{
	READY,
	LAUNCHED,
	EMPTY
};

struct MLS_INFOMATION
{
	MSS_STATUS missileStatus1;
	MSS_STATUS missileStatus2;
	MSS_STATUS missileStatus3;
	MSS_STATUS missileStatus4;
};

struct MLS_STATUS
{
	SIMULATION_STATUS simulationStatus;
	MLS_INFOMATION launcherInfo;
	unsigned int missileStock;
};

enum class MLS_TYPE : unsigned int
{
	VERTICAL_LAUNCHER
};