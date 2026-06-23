#pragma once

#include <cstdint>

struct CachedATSInfo
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	uint32_t speed = 0;
	uint32_t targetId = 0;
	uint32_t atsStatus = 0;
};

struct CachedMSSInfo
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	uint32_t targetId = 0;
	uint32_t missileId = 0;
};
