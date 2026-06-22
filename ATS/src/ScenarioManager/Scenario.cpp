#include "Scenario.h"

#include <cmath>

namespace
{
constexpr double kPositionEpsilon = 1.0e-6;
}

bool ScenarioTarget::isConfigured() const
{
    if (speed > 0)
    {
        return true;
    }

    for (const auto& point : route)
    {
        if (std::abs(point.x) > kPositionEpsilon ||
            std::abs(point.y) > kPositionEpsilon ||
            std::abs(point.z) > kPositionEpsilon)
        {
            return true;
        }
    }
    return false;
}

bool ScenarioTarget::validate() const
{
    if (!isConfigured())
    {
        return true;
    }

    if (speed == 0)
    {
        return false;
    }

    bool hasMovementSegment = false;
    for (std::size_t index = 0; index < route.size(); ++index)
    {
        const auto& point = route[index];
        if (!std::isfinite(point.x) || !std::isfinite(point.y) || !std::isfinite(point.z))
        {
            return false;
        }

        if (index > 0)
        {
            const auto& previous = route[index - 1];
            const double dx = point.x - previous.x;
            const double dy = point.y - previous.y;
            const double dz = point.z - previous.z;
            if (std::sqrt((dx * dx) + (dy * dy) + (dz * dz)) > kPositionEpsilon)
            {
                hasMovementSegment = true;
            }
        }
    }
    return hasMovementSegment;
}

bool Scenario::validate() const
{
    bool hasConfiguredTarget = false;
    for (const auto& target : targets)
    {
        if (!target.validate())
        {
            return false;
        }
        hasConfiguredTarget = hasConfiguredTarget || target.isConfigured();
    }
    return hasConfiguredTarget;
}
