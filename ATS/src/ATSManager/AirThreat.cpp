#include "AirThreat.h"

#include <algorithm>
#include <cmath>

namespace
{
constexpr double kPositionEpsilon = 1.0e-6;
}

bool AirThreat::initialize(
    std::uint32_t targetId,
    double speed,
    const std::vector<Position>& route)
{
    if (speed <= 0.0 || route.size() < 2)
    {
        return false;
    }

    targetId_ = targetId;
    speed_ = speed;
    route_ = route;
    nextPointIndex_ = 1;
    position_ = route_.front();
    velocity_ = {};
    state_ = AirThreatState::Ready;
    initialized_ = true;
    active_ = false;
    return true;
}

void AirThreat::start()
{
    if (!initialized_ || state_ == AirThreatState::Intercepted || state_ == AirThreatState::Completed)
    {
        return;
    }

    state_ = AirThreatState::Flying;
    active_ = true;
}

void AirThreat::stop()
{
    active_ = false;
    velocity_ = {};

    if (initialized_ && state_ == AirThreatState::Flying)
    {
        state_ = AirThreatState::Ready;
    }
}

void AirThreat::advance(double deltaSeconds)
{
    if (!active_ || deltaSeconds <= 0.0)
    {
        return;
    }

    double remainingDistance = speed_ * deltaSeconds;

    while (remainingDistance > kPositionEpsilon && nextPointIndex_ < route_.size())
    {
        const Position& destination = route_[nextPointIndex_];
        const double dx = destination.x - position_.x;
        const double dy = destination.y - position_.y;
        const double dz = destination.z - position_.z;
        const double distance = std::sqrt((dx * dx) + (dy * dy) + (dz * dz));

        if (distance <= kPositionEpsilon)
        {
            position_ = destination;
            ++nextPointIndex_;
            continue;
        }

        const double ux = dx / distance;
        const double uy = dy / distance;
        const double uz = dz / distance;
        velocity_ = { ux * speed_, uy * speed_, uz * speed_ };

        const double travel = std::min(remainingDistance, distance);
        position_.x += ux * travel;
        position_.y += uy * travel;
        position_.z += uz * travel;
        remainingDistance -= travel;

        if (travel + kPositionEpsilon >= distance)
        {
            position_ = destination;
            ++nextPointIndex_;
        }
    }

    if (nextPointIndex_ >= route_.size())
    {
        active_ = false;
        velocity_ = {};
        state_ = AirThreatState::Completed;
    }
}

void AirThreat::markIntercepted()
{
    if (!initialized_)
    {
        return;
    }

    active_ = false;
    velocity_ = {};
    state_ = AirThreatState::Intercepted;
}

bool AirThreat::isInitialized() const { return initialized_; }
bool AirThreat::isActive() const { return active_; }
bool AirThreat::isIntercepted() const { return state_ == AirThreatState::Intercepted; }
std::uint32_t AirThreat::targetId() const { return targetId_; }
double AirThreat::speed() const { return speed_; }
const Position& AirThreat::position() const { return position_; }
const Position& AirThreat::velocity() const { return velocity_; }
AirThreatState AirThreat::state() const { return state_; }
