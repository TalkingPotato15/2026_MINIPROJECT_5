#pragma once

#include "RSSInfoTypes.h"
#include <set>

class DetonationManager
{
public:
	void reset();
	bool isDestroyed(uint32_t targetId) const;
	void markDestroyed(uint32_t targetId);

	double getDistance(const CachedATSInfo& atsInfo, const CachedMSSInfo& mssInfo) const;
	bool isIntercepted(const CachedATSInfo& atsInfo, const CachedMSSInfo& mssInfo) const;

private:
	static constexpr double INTERCEPT_DISTANCE_THRESHOLD = 0.1;
	std::set<uint32_t> destroyedTargetIds;
};
