#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>

struct Position
{
    double x{ 0.0 };
    double y{ 0.0 };
    double z{ 0.0 };
};

enum class AirThreatState : std::uint16_t
{
    Ready = 0,
    Flying,
    Intercepted,
    Completed
};

class AirThreat
{
public:
    bool initialize(std::uint32_t targetId, double speed, const std::vector<Position>& route);
    void start();
    void stop();
    void advance(double deltaSeconds);
    void markIntercepted();

    bool isInitialized() const;
    bool isActive() const;
    bool isIntercepted() const;
    std::uint32_t targetId() const;
    double speed() const;
    const Position& position() const;
    const Position& velocity() const;
    AirThreatState state() const;

private:
    std::uint32_t targetId_{ 0 };
    double speed_{ 0.0 };
    std::vector<Position> route_;
    std::size_t nextPointIndex_{ 0 };
    Position position_{};
    Position velocity_{};
    AirThreatState state_{ AirThreatState::Ready };
    bool initialized_{ false };
    bool active_{ false };
};
