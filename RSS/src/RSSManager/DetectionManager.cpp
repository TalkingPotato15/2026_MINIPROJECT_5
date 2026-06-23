#include "DetectionManager.h"
#include <cmath>

void DetectionManager::reset()
{
	detectedTargetIds.clear();
	detectedTargetInfoMap.clear();
}

void DetectionManager::setDetectionArea(double x, double y, double z, double radius)
{
	rssPosX = x;
	rssPosY = y;
	rssPosZ = z;
	rssRadius = radius;
	hasRSSDetectionArea = rssRadius > 0.0;
	reset();
}

bool DetectionManager::hasDetectionArea() const
{
	return hasRSSDetectionArea;
}

double DetectionManager::getDistanceToRSS(const CachedATSInfo& atsInfo) const
{
	double dx = atsInfo.x - rssPosX;
	double dy = atsInfo.y - rssPosY;
	double dz = atsInfo.z - rssPosZ;

	return std::sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

bool DetectionManager::isInRange(const CachedATSInfo& atsInfo) const
{
	if (!hasRSSDetectionArea)
	{
		return false;
	}

	return getDistanceToRSS(atsInfo) <= rssRadius;
}

bool DetectionManager::isDetected(uint32_t targetId) const
{
	return detectedTargetIds.find(targetId) != detectedTargetIds.end();
}

void DetectionManager::markDetected(const CachedATSInfo& atsInfo)
{
	detectedTargetIds.insert(atsInfo.targetId);
	detectedTargetInfoMap[atsInfo.targetId] = atsInfo;
}

void DetectionManager::updateDetectedTarget(const CachedATSInfo& atsInfo)
{
	if (isDetected(atsInfo.targetId))
	{
		detectedTargetInfoMap[atsInfo.targetId] = atsInfo;
	}
}

void DetectionManager::removeDetectedTarget(uint32_t targetId)
{
	detectedTargetIds.erase(targetId);
	detectedTargetInfoMap.erase(targetId);
}

const CachedATSInfo* DetectionManager::findDetectedTarget(uint32_t targetId) const
{
	auto target = detectedTargetInfoMap.find(targetId);
	if (target == detectedTargetInfoMap.end())
	{
		return nullptr;
	}

	return &target->second;
}
