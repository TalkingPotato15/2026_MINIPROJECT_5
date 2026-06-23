#include "DetonationManager.h"
#include <cmath>

void DetonationManager::reset()
{
	destroyedTargetIds.clear();
}

bool DetonationManager::isDestroyed(uint32_t targetId) const
{
	return destroyedTargetIds.find(targetId) != destroyedTargetIds.end();
}

void DetonationManager::markDestroyed(uint32_t targetId)
{
	destroyedTargetIds.insert(targetId);
}

double DetonationManager::getDistance(const CachedATSInfo& atsInfo, const CachedMSSInfo& mssInfo) const
{
	double dx = atsInfo.x - mssInfo.x;
	double dy = atsInfo.y - mssInfo.y;
	double dz = atsInfo.z - mssInfo.z;

	return std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

bool DetonationManager::isIntercepted(const CachedATSInfo& atsInfo, const CachedMSSInfo& mssInfo) const
{
	return getDistance(atsInfo, mssInfo) <= INTERCEPT_DISTANCE_THRESHOLD;
}
