#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

constexpr std::size_t kAirThreatRoutePointCount = 4;

struct Position
{
    double x{ 0.0 };
    double y{ 0.0 };
    double z{ 0.0 };
};

enum class AirThreatStatus : std::uint32_t
{
    Ready = 0,
    Flying = 1,
    Destroyed = 2
};

class AirThreat
{
public:
    void reset(std::uint32_t targetId);
    bool initialize(
        std::uint32_t targetId,
        std::uint32_t speed,
        const std::array<Position, kAirThreatRoutePointCount>& route);
    void start();
    void stop();
    void advance(double deltaSeconds);
    void destroy();

    bool isConfigured() const;
    bool isFlying() const;
    std::uint32_t targetId() const;
    std::uint32_t speed() const;
    const Position& position() const;
    AirThreatStatus status() const;

private:
    std::uint32_t targetId_{ 0 };
    std::uint32_t speed_{ 0 };
    std::array<Position, kAirThreatRoutePointCount> route_{};
    std::size_t nextPointIndex_{ 1 };
    Position position_{};
    Position velocity_{};
    AirThreatStatus status_{ AirThreatStatus::Ready };
    bool configured_{ false };
};
