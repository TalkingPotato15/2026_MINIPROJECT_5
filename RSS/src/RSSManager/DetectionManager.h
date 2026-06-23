#pragma once

#include "RSSInfoTypes.h"
#include <map>
#include <set>

class DetectionManager
{
public:
	void reset();
	void setDetectionArea(double x, double y, double z, double radius);

	bool hasDetectionArea() const;
	double getDistanceToRSS(const CachedATSInfo& atsInfo) const;
	bool isInRange(const CachedATSInfo& atsInfo) const;

	bool isDetected(uint32_t targetId) const;
	void markDetected(const CachedATSInfo& atsInfo);
	void updateDetectedTarget(const CachedATSInfo& atsInfo);
	void removeDetectedTarget(uint32_t targetId);
	const CachedATSInfo* findDetectedTarget(uint32_t targetId) const;

private:
	std::set<uint32_t> detectedTargetIds;
	std::map<uint32_t, CachedATSInfo> detectedTargetInfoMap;

	bool hasRSSDetectionArea = false;
	double rssPosX = 0.0;
	double rssPosY = 0.0;
	double rssPosZ = 0.0;
	double rssRadius = 0.0;
};
