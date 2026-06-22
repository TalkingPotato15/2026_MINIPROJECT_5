#include "Scenario.h"

#include <cmath>

bool Scenario::validate() const
{
    if (speed == 0 || route.size() < 2 || route.size() > 8)
    {
        return false;
    }

    for (const auto& point : route)
    {
        if (!std::isfinite(point.x) || !std::isfinite(point.y) || !std::isfinite(point.z))
        {
            return false;
        }
    }
    return true;
}
