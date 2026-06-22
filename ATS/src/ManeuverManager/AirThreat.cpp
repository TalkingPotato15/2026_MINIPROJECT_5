#include "AirThreat.h"

#include <algorithm>
#include <cmath>

namespace
{
constexpr double kPositionEpsilon = 1.0e-6;
}

void AirThreat::reset(std::uint32_t targetId)
{
    targetId_ = targetId;
    speed_ = 0;
    route_ = {};
    nextPointIndex_ = 1;
    position_ = {};
    velocity_ = {};
    status_ = AirThreatStatus::Ready;
    configured_ = false;
}

bool AirThreat::initialize(
    std::uint32_t targetId,
    std::uint32_t speed,
    const std::array<Position, kAirThreatRoutePointCount>& route)
{
    if (speed == 0)
    {
        reset(targetId);
        return false;
    }

    targetId_ = targetId;
    speed_ = speed;
    route_ = route;
    nextPointIndex_ = 1;
    position_ = route_.front();
    velocity_ = {};
    status_ = AirThreatStatus::Ready;
    configured_ = true;
    return true;
}

void AirThreat::start()
{
    if (!configured_ || status_ == AirThreatStatus::Destroyed)
    {
        return;
    }
    status_ = AirThreatStatus::Flying;
}

void AirThreat::stop()
{
    velocity_ = {};
    if (configured_ && status_ != AirThreatStatus::Destroyed)
    {
        status_ = AirThreatStatus::Ready;
    }
}

void AirThreat::advance(double deltaSeconds)
{
    if (!configured_ || status_ != AirThreatStatus::Flying || deltaSeconds <= 0.0)
    {
        return;
    }

    double remainingDistance = static_cast<double>(speed_) * deltaSeconds;

    while (remainingDistance > kPositionEpsilon && nextPointIndex_ < route_.size())
    {
        const auto& destination = route_[nextPointIndex_];
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
        velocity_ = {
            ux * static_cast<double>(speed_),
            uy * static_cast<double>(speed_),
            uz * static_cast<double>(speed_)
        };

        const double travelDistance = std::min(remainingDistance, distance);
        position_.x += ux * travelDistance;
        position_.y += uy * travelDistance;
        position_.z += uz * travelDistance;
        remainingDistance -= travelDistance;

        if (travelDistance + kPositionEpsilon >= distance)
        {
            position_ = destination;
            ++nextPointIndex_;
        }
    }

    if (nextPointIndex_ >= route_.size())
    {
        velocity_ = {};
        status_ = AirThreatStatus::Ready;
    }
}

void AirThreat::destroy()
{
    if (!configured_)
    {
        return;
    }
    velocity_ = {};
    status_ = AirThreatStatus::Destroyed;
}

bool AirThreat::isConfigured() const { return configured_; }
bool AirThreat::isFlying() const { return status_ == AirThreatStatus::Flying; }
std::uint32_t AirThreat::targetId() const { return targetId_; }
std::uint32_t AirThreat::speed() const { return speed_; }
const Position& AirThreat::position() const { return position_; }
AirThreatStatus AirThreat::status() const { return status_; }
