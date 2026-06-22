#pragma once

#include <cstdint>
#include <vector>

struct ScenarioPosition
{
    double x{ 0.0 };
    double y{ 0.0 };
    double z{ 0.0 };
};

class Scenario
{
public:
    std::uint32_t targetId{ 0 };
    std::uint32_t speed{ 0 };
    std::vector<ScenarioPosition> route;
    ScenarioPosition radarPosition;
    double radarRadius{ 0.0 };
    ScenarioPosition launcherPosition;

    bool validate() const;
};
