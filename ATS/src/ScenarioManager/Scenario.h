#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

constexpr std::size_t kATSMaxTargetCount = 4;
constexpr std::size_t kATSRoutePointCount = 4;

struct ScenarioPosition
{
    double x{ 0.0 };
    double y{ 0.0 };
    double z{ 0.0 };
};

struct ScenarioTarget
{
    std::array<ScenarioPosition, kATSRoutePointCount> route{};
    std::uint32_t speed{ 0 };

    bool isConfigured() const;
    bool validate() const;
};

class Scenario
{
public:
    std::array<ScenarioTarget, kATSMaxTargetCount> targets{};

    bool validate() const;
};
