#include "VerticalLauncherModel.h"
#include <iostream>
#include <format>

void VerticalLauncherModel::init()
{
	std::cout << "[VerticalLauncherModel - init]\n";

	simulationStatus = SIMULATION_STATUS::IDLE;

	launcherInfo.missileStatus1 = MSS_STATUS::READY;
	launcherInfo.missileStatus2 = MSS_STATUS::READY;
	launcherInfo.missileStatus3 = MSS_STATUS::READY;
	launcherInfo.missileStatus4 = MSS_STATUS::READY;

	currentPos.x = 0;
	currentPos.y = 0;
	currentPos.z = 0;

	currentTime = 0;

	currentStock = 0;
}

void VerticalLauncherModel::setting(POSITION pos)
{
	std::cout << std::format("[VerticalLauncherModel - setting] : {} {} {}\n", pos.x, pos.y, pos.z);

	simulationStatus = SIMULATION_STATUS::READY;

	launcherInfo.missileStatus1 = MSS_STATUS::READY;
	launcherInfo.missileStatus2 = MSS_STATUS::READY;
	launcherInfo.missileStatus3 = MSS_STATUS::READY;
	launcherInfo.missileStatus4 = MSS_STATUS::READY;

	currentPos = pos;

	currentTime = 0;

	currentStock = 4;
}

void VerticalLauncherModel::start()
{
	std::cout << "[VerticalLauncherModel - start]\n";
	simulationStatus = SIMULATION_STATUS::RUNNING;
}

void VerticalLauncherModel::stop()
{
	std::cout << "[VerticalLauncherModel - stop]\n";
	init();
}

void VerticalLauncherModel::update(double tick)
{
	currentTime += tick;
}

int VerticalLauncherModel::fireMissile(unsigned int targetID)
{
	if (currentStock <= 0)
	{
		std::cout << "[VerticalLauncherModel - fireMissile] : currentStock = 0\n";
		return 0;
	}

	if (launcherInfo.missileStatus1 == MSS_STATUS::READY)
	{
		std::cout << "[VerticalLauncherModel - fireMissile] : missileID = 1\n";

		launcherInfo.missileStatus1 = MSS_STATUS::LAUNCHED;
		currentStock -= 1;

		return 1;
	}
	else if (launcherInfo.missileStatus2 == MSS_STATUS::READY)
	{
		std::cout << "[VerticalLauncherModel - fireMissile] : currentID = 2\n";

		launcherInfo.missileStatus2 = MSS_STATUS::LAUNCHED;
		currentStock -= 1;

		return 2;
	}
	else if (launcherInfo.missileStatus3 == MSS_STATUS::READY)
	{
		std::cout << "[VerticalLauncherModel - fireMissile] : currentID = 3\n";

		launcherInfo.missileStatus3 = MSS_STATUS::LAUNCHED;
		currentStock -= 1;

		return 3;
	}
	else if (launcherInfo.missileStatus4 == MSS_STATUS::READY)
	{
		std::cout << "[VerticalLauncherModel - fireMissile] : currentID = 4\n";

		launcherInfo.missileStatus4 = MSS_STATUS::LAUNCHED;
		currentStock -= 1;

		return 4;
	}
	else {
		std::cout << "[VerticalLauncherModel - fireMissile] : WrongFireMissile\n";
		return 0;
	}
}

MLS_STATUS VerticalLauncherModel::mlsStatus()
{
	MLS_STATUS mlsStatus;

	mlsStatus.simulationStatus = simulationStatus;
	mlsStatus.launcherInfo = launcherInfo;
	mlsStatus.missileStock = currentStock;

	/*std::cout << std::format(
		"[VerticalLauncherModel - mlsStatus] : "
		"simulationStatus : {} "
		"[{}, {}, {}, {}] "
		"missileStock : {}\n",
		static_cast<unsigned int>(mlsStatus.simulationStatus),
		static_cast<unsigned int>(mlsStatus.launcherInfo.missileStatus1),
		static_cast<unsigned int>(mlsStatus.launcherInfo.missileStatus2),
		static_cast<unsigned int>(mlsStatus.launcherInfo.missileStatus3),
		static_cast<unsigned int>(mlsStatus.launcherInfo.missileStatus4),
		mlsStatus.missileStock
	);*/

	return mlsStatus;
}

POSITION VerticalLauncherModel::currentPosition()
{
	return currentPos;
}
