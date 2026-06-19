#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-04-16 13:53:11

namespace nframework::intellival
{
namespace BaseEntity_PhysicalEntity_Platform_Aircraft
{
using v_AccelerationVector_XAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_YAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_ZAcceleration = nframework::nom::NFloat;
using v_EntityType_EntityKind = nframework::nom::NByte;
using v_EntityType_Domain = nframework::nom::NByte;
using v_EntityType_CountryCode = nframework::nom::NUShort;
using v_EntityType_Category = nframework::nom::NByte;
using v_EntityType_Subcategory = nframework::nom::NByte;
using v_EntityType_Specific = nframework::nom::NByte;
using v_EntityType_Extra = nframework::nom::NByte;
using v_EntityIdentifier_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_EntityIdentifier_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_EntityIdentifier_EntityNumber = nframework::nom::NUShort;
using v_IsFrozen = nframework::nom::NBool;
using v_Orientation_Psi = nframework::nom::NFloat;
using v_Orientation_Theta = nframework::nom::NFloat;
using v_Orientation_Phi = nframework::nom::NFloat;
using v_WorldLocation_X = nframework::nom::NDouble;
using v_WorldLocation_Y = nframework::nom::NDouble;
using v_WorldLocation_Z = nframework::nom::NDouble;
using v_VelocityVector_XVelocity = nframework::nom::NFloat;
using v_VelocityVector_YVelocity = nframework::nom::NFloat;
using v_VelocityVector_ZVelocity = nframework::nom::NFloat;
using v_ForceIdentifier = nframework::nom::NEnum;
auto t_AccelerationVector_XAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_YAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_ZAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_EntityType_EntityKind = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Domain = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_CountryCode = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityType_Category = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Subcategory = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Specific = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Extra = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityIdentifier_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_IsFrozen = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Orientation_Psi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Theta = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Phi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_WorldLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_VelocityVector_XVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_YVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_ZVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_ForceIdentifier = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
}

namespace BaseEntity_PhysicalEntity_Munition
{
using v_AccelerationVector_XAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_YAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_ZAcceleration = nframework::nom::NFloat;
using v_EntityType_EntityKind = nframework::nom::NByte;
using v_EntityType_Domain = nframework::nom::NByte;
using v_EntityType_CountryCode = nframework::nom::NUShort;
using v_EntityType_Category = nframework::nom::NByte;
using v_EntityType_Subcategory = nframework::nom::NByte;
using v_EntityType_Specific = nframework::nom::NByte;
using v_EntityType_Extra = nframework::nom::NByte;
using v_EntityIdentifier_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_EntityIdentifier_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_EntityIdentifier_EntityNumber = nframework::nom::NUShort;
using v_IsFrozen = nframework::nom::NBool;
using v_Orientation_Psi = nframework::nom::NFloat;
using v_Orientation_Theta = nframework::nom::NFloat;
using v_Orientation_Phi = nframework::nom::NFloat;
using v_WorldLocation_X = nframework::nom::NDouble;
using v_WorldLocation_Y = nframework::nom::NDouble;
using v_WorldLocation_Z = nframework::nom::NDouble;
using v_VelocityVector_XVelocity = nframework::nom::NFloat;
using v_VelocityVector_YVelocity = nframework::nom::NFloat;
using v_VelocityVector_ZVelocity = nframework::nom::NFloat;
using v_ForceIdentifier = nframework::nom::NEnum;
auto t_AccelerationVector_XAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_YAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_ZAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_EntityType_EntityKind = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Domain = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_CountryCode = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityType_Category = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Subcategory = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Specific = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Extra = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityIdentifier_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_IsFrozen = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Orientation_Psi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Theta = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Phi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_WorldLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_VelocityVector_XVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_YVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_ZVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_ForceIdentifier = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
}

namespace BaseEntity_PhysicalEntity_Sensor
{
using v_AccelerationVector_XAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_YAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_ZAcceleration = nframework::nom::NFloat;
using v_EntityType_EntityKind = nframework::nom::NByte;
using v_EntityType_Domain = nframework::nom::NByte;
using v_EntityType_CountryCode = nframework::nom::NUShort;
using v_EntityType_Category = nframework::nom::NByte;
using v_EntityType_Subcategory = nframework::nom::NByte;
using v_EntityType_Specific = nframework::nom::NByte;
using v_EntityType_Extra = nframework::nom::NByte;
using v_EntityIdentifier_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_EntityIdentifier_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_EntityIdentifier_EntityNumber = nframework::nom::NUShort;
using v_IsFrozen = nframework::nom::NBool;
using v_Orientation_Psi = nframework::nom::NFloat;
using v_Orientation_Theta = nframework::nom::NFloat;
using v_Orientation_Phi = nframework::nom::NFloat;
using v_WorldLocation_X = nframework::nom::NDouble;
using v_WorldLocation_Y = nframework::nom::NDouble;
using v_WorldLocation_Z = nframework::nom::NDouble;
using v_VelocityVector_XVelocity = nframework::nom::NFloat;
using v_VelocityVector_YVelocity = nframework::nom::NFloat;
using v_VelocityVector_ZVelocity = nframework::nom::NFloat;
using v_ForceIdentifier = nframework::nom::NEnum;
using v_AntennaRaised = nframework::nom::NBool;
using v_BlackoutLightsOn = nframework::nom::NBool;
using v_LightsOn = nframework::nom::NBool;
using v_InteriorLightsOn = nframework::nom::NBool;
using v_MissionKill = nframework::nom::NBool;
auto t_AccelerationVector_XAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_YAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_ZAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_EntityType_EntityKind = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Domain = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_CountryCode = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityType_Category = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Subcategory = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Specific = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Extra = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityIdentifier_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_IsFrozen = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Orientation_Psi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Theta = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Phi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_WorldLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_VelocityVector_XVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_YVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_ZVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_ForceIdentifier = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_AntennaRaised = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_BlackoutLightsOn = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_LightsOn = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_InteriorLightsOn = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_MissionKill = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
}

namespace BaseEntity_PhysicalEntity_Platform_GroundVehicle
{
using v_AccelerationVector_XAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_YAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_ZAcceleration = nframework::nom::NFloat;
using v_EntityType_EntityKind = nframework::nom::NByte;
using v_EntityType_Domain = nframework::nom::NByte;
using v_EntityType_CountryCode = nframework::nom::NUShort;
using v_EntityType_Category = nframework::nom::NByte;
using v_EntityType_Subcategory = nframework::nom::NByte;
using v_EntityType_Specific = nframework::nom::NByte;
using v_EntityType_Extra = nframework::nom::NByte;
using v_EntityIdentifier_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_EntityIdentifier_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_EntityIdentifier_EntityNumber = nframework::nom::NUShort;
using v_IsFrozen = nframework::nom::NBool;
using v_Orientation_Psi = nframework::nom::NFloat;
using v_Orientation_Theta = nframework::nom::NFloat;
using v_Orientation_Phi = nframework::nom::NFloat;
using v_WorldLocation_X = nframework::nom::NDouble;
using v_WorldLocation_Y = nframework::nom::NDouble;
using v_WorldLocation_Z = nframework::nom::NDouble;
using v_VelocityVector_XVelocity = nframework::nom::NFloat;
using v_VelocityVector_YVelocity = nframework::nom::NFloat;
using v_VelocityVector_ZVelocity = nframework::nom::NFloat;
using v_ForceIdentifier = nframework::nom::NEnum;
auto t_AccelerationVector_XAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_YAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_ZAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_EntityType_EntityKind = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Domain = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_CountryCode = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityType_Category = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Subcategory = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Specific = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Extra = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityIdentifier_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_IsFrozen = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Orientation_Psi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Theta = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Phi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_WorldLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_VelocityVector_XVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_YVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_ZVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_ForceIdentifier = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
}

namespace BaseEntity_PhysicalEntity_Platform_SurfaceVessel
{
using v_AccelerationVector_XAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_YAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_ZAcceleration = nframework::nom::NFloat;
using v_EntityType_EntityKind = nframework::nom::NByte;
using v_EntityType_Domain = nframework::nom::NByte;
using v_EntityType_CountryCode = nframework::nom::NUShort;
using v_EntityType_Category = nframework::nom::NByte;
using v_EntityType_Subcategory = nframework::nom::NByte;
using v_EntityType_Specific = nframework::nom::NByte;
using v_EntityType_Extra = nframework::nom::NByte;
using v_EntityIdentifier_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_EntityIdentifier_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_EntityIdentifier_EntityNumber = nframework::nom::NUShort;
using v_IsFrozen = nframework::nom::NBool;
using v_Orientation_Psi = nframework::nom::NFloat;
using v_Orientation_Theta = nframework::nom::NFloat;
using v_Orientation_Phi = nframework::nom::NFloat;
using v_WorldLocation_X = nframework::nom::NDouble;
using v_WorldLocation_Y = nframework::nom::NDouble;
using v_WorldLocation_Z = nframework::nom::NDouble;
using v_VelocityVector_XVelocity = nframework::nom::NFloat;
using v_VelocityVector_YVelocity = nframework::nom::NFloat;
using v_VelocityVector_ZVelocity = nframework::nom::NFloat;
using v_ForceIdentifier = nframework::nom::NEnum;
auto t_AccelerationVector_XAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_YAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_ZAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_EntityType_EntityKind = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Domain = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_CountryCode = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityType_Category = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Subcategory = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Specific = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Extra = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityIdentifier_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_IsFrozen = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Orientation_Psi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Theta = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Phi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_WorldLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_VelocityVector_XVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_YVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_ZVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_ForceIdentifier = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
}

namespace BaseEntity_PhysicalEntity_Platform_Aircraft_GUI
{
using v_LogicalTime = nframework::nom::NUInteger;
using v_AccelerationVector_XAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_YAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_ZAcceleration = nframework::nom::NFloat;
using v_EntityType_EntityKind = nframework::nom::NByte;
using v_EntityType_Domain = nframework::nom::NByte;
using v_EntityType_CountryCode = nframework::nom::NUShort;
using v_EntityType_Category = nframework::nom::NByte;
using v_EntityType_Subcategory = nframework::nom::NByte;
using v_EntityType_Specific = nframework::nom::NByte;
using v_EntityType_Extra = nframework::nom::NByte;
using v_EntityIdentifier_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_EntityIdentifier_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_EntityIdentifier_EntityNumber = nframework::nom::NUShort;
using v_IsFrozen = nframework::nom::NBool;
using v_Orientation_Psi = nframework::nom::NFloat;
using v_Orientation_Theta = nframework::nom::NFloat;
using v_Orientation_Phi = nframework::nom::NFloat;
using v_WorldLocation_X = nframework::nom::NDouble;
using v_WorldLocation_Y = nframework::nom::NDouble;
using v_WorldLocation_Z = nframework::nom::NDouble;
using v_VelocityVector_XVelocity = nframework::nom::NFloat;
using v_VelocityVector_YVelocity = nframework::nom::NFloat;
using v_VelocityVector_ZVelocity = nframework::nom::NFloat;
using v_ForceIdentifier = nframework::nom::NEnum;
auto t_LogicalTime = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AccelerationVector_XAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_YAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_ZAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_EntityType_EntityKind = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Domain = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_CountryCode = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityType_Category = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Subcategory = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Specific = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Extra = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityIdentifier_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_IsFrozen = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Orientation_Psi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Theta = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Phi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_WorldLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_VelocityVector_XVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_YVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_ZVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_ForceIdentifier = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
}

namespace BaseEntity_PhysicalEntity_Munition_GUI
{
using v_LogicalTime = nframework::nom::NUInteger;
using v_AccelerationVector_XAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_YAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_ZAcceleration = nframework::nom::NFloat;
using v_EntityType_EntityKind = nframework::nom::NByte;
using v_EntityType_Domain = nframework::nom::NByte;
using v_EntityType_CountryCode = nframework::nom::NUShort;
using v_EntityType_Category = nframework::nom::NByte;
using v_EntityType_Subcategory = nframework::nom::NByte;
using v_EntityType_Specific = nframework::nom::NByte;
using v_EntityType_Extra = nframework::nom::NByte;
using v_EntityIdentifier_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_EntityIdentifier_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_EntityIdentifier_EntityNumber = nframework::nom::NUShort;
using v_IsFrozen = nframework::nom::NBool;
using v_Orientation_Psi = nframework::nom::NFloat;
using v_Orientation_Theta = nframework::nom::NFloat;
using v_Orientation_Phi = nframework::nom::NFloat;
using v_WorldLocation_X = nframework::nom::NDouble;
using v_WorldLocation_Y = nframework::nom::NDouble;
using v_WorldLocation_Z = nframework::nom::NDouble;
using v_VelocityVector_XVelocity = nframework::nom::NFloat;
using v_VelocityVector_YVelocity = nframework::nom::NFloat;
using v_VelocityVector_ZVelocity = nframework::nom::NFloat;
using v_ForceIdentifier = nframework::nom::NEnum;
auto t_LogicalTime = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AccelerationVector_XAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_YAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_ZAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_EntityType_EntityKind = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Domain = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_CountryCode = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityType_Category = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Subcategory = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Specific = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Extra = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityIdentifier_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_IsFrozen = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Orientation_Psi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Theta = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Phi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_WorldLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_VelocityVector_XVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_YVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_ZVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_ForceIdentifier = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
}

namespace BaseEntity_PhysicalEntity_Sensor_GUI
{
using v_LogicalTime = nframework::nom::NUInteger;
using v_AccelerationVector_XAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_YAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_ZAcceleration = nframework::nom::NFloat;
using v_EntityType_EntityKind = nframework::nom::NByte;
using v_EntityType_Domain = nframework::nom::NByte;
using v_EntityType_CountryCode = nframework::nom::NUShort;
using v_EntityType_Category = nframework::nom::NByte;
using v_EntityType_Subcategory = nframework::nom::NByte;
using v_EntityType_Specific = nframework::nom::NByte;
using v_EntityType_Extra = nframework::nom::NByte;
using v_EntityIdentifier_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_EntityIdentifier_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_EntityIdentifier_EntityNumber = nframework::nom::NUShort;
using v_IsFrozen = nframework::nom::NBool;
using v_Orientation_Psi = nframework::nom::NFloat;
using v_Orientation_Theta = nframework::nom::NFloat;
using v_Orientation_Phi = nframework::nom::NFloat;
using v_WorldLocation_X = nframework::nom::NDouble;
using v_WorldLocation_Y = nframework::nom::NDouble;
using v_WorldLocation_Z = nframework::nom::NDouble;
using v_VelocityVector_XVelocity = nframework::nom::NFloat;
using v_VelocityVector_YVelocity = nframework::nom::NFloat;
using v_VelocityVector_ZVelocity = nframework::nom::NFloat;
using v_ForceIdentifier = nframework::nom::NEnum;
using v_AntennaRaised = nframework::nom::NBool;
using v_BlackoutLightsOn = nframework::nom::NBool;
using v_LightsOn = nframework::nom::NBool;
using v_InteriorLightsOn = nframework::nom::NBool;
using v_MissionKill = nframework::nom::NBool;
auto t_LogicalTime = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AccelerationVector_XAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_YAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_ZAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_EntityType_EntityKind = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Domain = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_CountryCode = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityType_Category = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Subcategory = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Specific = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Extra = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityIdentifier_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_IsFrozen = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Orientation_Psi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Theta = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Phi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_WorldLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_VelocityVector_XVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_YVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_ZVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_ForceIdentifier = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_AntennaRaised = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_BlackoutLightsOn = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_LightsOn = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_InteriorLightsOn = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_MissionKill = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
}

namespace BaseEntity_PhysicalEntity_Platform_GroundVehicle_GUI
{
using v_LogicalTime = nframework::nom::NUInteger;
using v_AccelerationVector_XAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_YAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_ZAcceleration = nframework::nom::NFloat;
using v_EntityType_EntityKind = nframework::nom::NByte;
using v_EntityType_Domain = nframework::nom::NByte;
using v_EntityType_CountryCode = nframework::nom::NUShort;
using v_EntityType_Category = nframework::nom::NByte;
using v_EntityType_Subcategory = nframework::nom::NByte;
using v_EntityType_Specific = nframework::nom::NByte;
using v_EntityType_Extra = nframework::nom::NByte;
using v_EntityIdentifier_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_EntityIdentifier_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_EntityIdentifier_EntityNumber = nframework::nom::NUShort;
using v_IsFrozen = nframework::nom::NBool;
using v_Orientation_Psi = nframework::nom::NFloat;
using v_Orientation_Theta = nframework::nom::NFloat;
using v_Orientation_Phi = nframework::nom::NFloat;
using v_WorldLocation_X = nframework::nom::NDouble;
using v_WorldLocation_Y = nframework::nom::NDouble;
using v_WorldLocation_Z = nframework::nom::NDouble;
using v_VelocityVector_XVelocity = nframework::nom::NFloat;
using v_VelocityVector_YVelocity = nframework::nom::NFloat;
using v_VelocityVector_ZVelocity = nframework::nom::NFloat;
using v_ForceIdentifier = nframework::nom::NEnum;
auto t_LogicalTime = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AccelerationVector_XAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_YAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_ZAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_EntityType_EntityKind = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Domain = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_CountryCode = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityType_Category = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Subcategory = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Specific = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Extra = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityIdentifier_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_IsFrozen = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Orientation_Psi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Theta = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Phi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_WorldLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_VelocityVector_XVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_YVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_ZVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_ForceIdentifier = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
}

namespace BaseEntity_PhysicalEntity_Platform_SurfaceVessel_GUI
{
using v_LogicalTime = nframework::nom::NUInteger;
using v_AccelerationVector_XAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_YAcceleration = nframework::nom::NFloat;
using v_AccelerationVector_ZAcceleration = nframework::nom::NFloat;
using v_EntityType_EntityKind = nframework::nom::NByte;
using v_EntityType_Domain = nframework::nom::NByte;
using v_EntityType_CountryCode = nframework::nom::NUShort;
using v_EntityType_Category = nframework::nom::NByte;
using v_EntityType_Subcategory = nframework::nom::NByte;
using v_EntityType_Specific = nframework::nom::NByte;
using v_EntityType_Extra = nframework::nom::NByte;
using v_EntityIdentifier_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_EntityIdentifier_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_EntityIdentifier_EntityNumber = nframework::nom::NUShort;
using v_IsFrozen = nframework::nom::NBool;
using v_Orientation_Psi = nframework::nom::NFloat;
using v_Orientation_Theta = nframework::nom::NFloat;
using v_Orientation_Phi = nframework::nom::NFloat;
using v_WorldLocation_X = nframework::nom::NDouble;
using v_WorldLocation_Y = nframework::nom::NDouble;
using v_WorldLocation_Z = nframework::nom::NDouble;
using v_VelocityVector_XVelocity = nframework::nom::NFloat;
using v_VelocityVector_YVelocity = nframework::nom::NFloat;
using v_VelocityVector_ZVelocity = nframework::nom::NFloat;
using v_ForceIdentifier = nframework::nom::NEnum;
auto t_LogicalTime = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AccelerationVector_XAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_YAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_AccelerationVector_ZAcceleration = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_EntityType_EntityKind = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Domain = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_CountryCode = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityType_Category = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Subcategory = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Specific = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityType_Extra = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_EntityIdentifier_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EntityIdentifier_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_IsFrozen = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Orientation_Psi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Theta = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_Orientation_Phi = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_WorldLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_WorldLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_VelocityVector_XVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_YVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_VelocityVector_ZVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_ForceIdentifier = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
}

namespace EventReport
{
using v_OriginatingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_OriginatingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_OriginatingEntity_EntityNumber = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_ReceivingEntity_EntityNumber = nframework::nom::NUShort;
using v_EventType = nframework::nom::NEnum;
using v_VariableDatumSet_NumberOfVariableDatums = nframework::nom::NUInteger;
using v_VariableDatumSet_VariableDatums_DatumID = nframework::nom::NEnum;
using v_VariableDatumSet_VariableDatums_DatumLength = nframework::nom::NUInteger;
using v_VariableDatumSet_VariableDatums_DatumValue = nframework::nom::NVariable;
using v_VariableDatumSet_VariableDatums_Padding = nframework::nom::NByte;
auto t_OriginatingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_EventType = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_VariableDatumSet_NumberOfVariableDatums = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_VariableDatumSet_VariableDatums_DatumID = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_VariableDatumSet_VariableDatums_DatumLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_VariableDatumSet_VariableDatums_Padding = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
}

namespace ActionRequest
{
using v_OriginatingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_OriginatingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_OriginatingEntity_EntityNumber = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_ReceivingEntity_EntityNumber = nframework::nom::NUShort;
using v_RequestIdentifier = nframework::nom::NUInteger;
using v_ActionRequestCode = nframework::nom::NEnum;
using v_VariableDatumSet_NumberOfVariableDatums = nframework::nom::NUInteger;
using v_VariableDatumSet_VariableDatums_DatumID = nframework::nom::NEnum;
using v_VariableDatumSet_VariableDatums_DatumLength = nframework::nom::NUInteger;
using v_VariableDatumSet_VariableDatums_DatumValue = nframework::nom::NVariable;
using v_VariableDatumSet_VariableDatums_Padding = nframework::nom::NByte;
auto t_OriginatingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_RequestIdentifier = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_ActionRequestCode = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_VariableDatumSet_NumberOfVariableDatums = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_VariableDatumSet_VariableDatums_DatumID = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_VariableDatumSet_VariableDatums_DatumLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_VariableDatumSet_VariableDatums_Padding = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
}

namespace ActionResponse
{
using v_OriginatingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_OriginatingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_OriginatingEntity_EntityNumber = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_ReceivingEntity_EntityNumber = nframework::nom::NUShort;
using v_RequestIdentifier = nframework::nom::NUInteger;
using v_RequestStatus = nframework::nom::NEnum;
using v_VariableDatumSet_NumberOfVariableDatums = nframework::nom::NUInteger;
using v_VariableDatumSet_VariableDatums_DatumID = nframework::nom::NEnum;
using v_VariableDatumSet_VariableDatums_DatumLength = nframework::nom::NUInteger;
using v_VariableDatumSet_VariableDatums_DatumValue = nframework::nom::NVariable;
using v_VariableDatumSet_VariableDatums_Padding = nframework::nom::NByte;
auto t_OriginatingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_RequestIdentifier = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_RequestStatus = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_VariableDatumSet_NumberOfVariableDatums = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_VariableDatumSet_VariableDatums_DatumID = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_VariableDatumSet_VariableDatums_DatumLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_VariableDatumSet_VariableDatums_Padding = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
}

namespace SetData
{
using v_OriginatingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_OriginatingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_OriginatingEntity_EntityNumber = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_ReceivingEntity_EntityNumber = nframework::nom::NUShort;
using v_RequestIdentifier = nframework::nom::NUInteger;
using v_VariableDatumSet_NumberOfVariableDatums = nframework::nom::NUInteger;
using v_VariableDatumSet_VariableDatums_DatumID = nframework::nom::NEnum;
using v_VariableDatumSet_VariableDatums_DatumLength = nframework::nom::NUInteger;
using v_VariableDatumSet_VariableDatums_DatumValue = nframework::nom::NVariable;
using v_VariableDatumSet_VariableDatums_Padding = nframework::nom::NByte;
auto t_OriginatingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_RequestIdentifier = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_VariableDatumSet_NumberOfVariableDatums = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_VariableDatumSet_VariableDatums_DatumID = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_VariableDatumSet_VariableDatums_DatumLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_VariableDatumSet_VariableDatums_Padding = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
}

namespace Data
{
using v_OriginatingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_OriginatingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_OriginatingEntity_EntityNumber = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_ReceivingEntity_EntityNumber = nframework::nom::NUShort;
using v_RequestIdentifier = nframework::nom::NUInteger;
auto t_OriginatingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_RequestIdentifier = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace StartResume
{
using v_OriginatingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_OriginatingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_OriginatingEntity_EntityNumber = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_ReceivingEntity_EntityNumber = nframework::nom::NUShort;
using v_RequestIdentifier = nframework::nom::NUInteger;
auto t_OriginatingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_RequestIdentifier = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace StopFreeze
{
using v_OriginatingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_OriginatingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_OriginatingEntity_EntityNumber = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_ReceivingEntity_EntityNumber = nframework::nom::NUShort;
using v_RequestIdentifier = nframework::nom::NUInteger;
auto t_OriginatingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_RequestIdentifier = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace Acknowledge
{
using v_OriginatingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_OriginatingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_OriginatingEntity_EntityNumber = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_SiteID = nframework::nom::NUShort;
using v_ReceivingEntity_FederateIdentifier_ApplicationID = nframework::nom::NUShort;
using v_ReceivingEntity_EntityNumber = nframework::nom::NUShort;
using v_RequestIdentifier = nframework::nom::NUInteger;
using v_AcknowledgeFlag = nframework::nom::NEnum;
using v_ResponseFlag = nframework::nom::NEnum;
auto t_OriginatingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_OriginatingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_SiteID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_FederateIdentifier_ApplicationID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ReceivingEntity_EntityNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_RequestIdentifier = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AcknowledgeFlag = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_ResponseFlag = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
}

namespace WeaponFire
{
using v_FireMissionIndex = nframework::nom::NUInteger;
using v_FiringLocation_X = nframework::nom::NDouble;
using v_FiringLocation_Y = nframework::nom::NDouble;
using v_FiringLocation_Z = nframework::nom::NDouble;
using v_FiringObjectIdentifier_ScenarioObjectID = nframework::nom::NUShort;
using v_FiringObjectIdentifier_SimulationObjectID = nframework::nom::NUShort;
using v_MunitionObjectIdentifier_ScenarioObjectID = nframework::nom::NUShort;
using v_MunitionObjectIdentifier_SimulationObjectID = nframework::nom::NUShort;
using v_MunitionType_EntityKind = nframework::nom::NByte;
using v_MunitionType_Domain = nframework::nom::NByte;
using v_MunitionType_CountryCode = nframework::nom::NUShort;
using v_MunitionType_Category = nframework::nom::NByte;
using v_MunitionType_Subcategory = nframework::nom::NByte;
using v_MunitionType_Specific = nframework::nom::NByte;
using v_MunitionType_Extra = nframework::nom::NByte;
using v_TargetObjectIdentifier_ScenarioObjectID = nframework::nom::NUShort;
using v_TargetObjectIdentifier_SimulationObjectID = nframework::nom::NUShort;
using v_VariableDatumSet_NumberOfVariableDatums = nframework::nom::NUInteger;
using v_VariableDatumSet_VariableDatums_DatumID = nframework::nom::NEnum;
using v_VariableDatumSet_VariableDatums_DatumLength = nframework::nom::NUInteger;
using v_VariableDatumSet_VariableDatums_DatumValue = nframework::nom::NVariable;
using v_VariableDatumSet_VariableDatums_Padding = nframework::nom::NByte;
auto t_FireMissionIndex = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_FiringLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_FiringLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_FiringLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_FiringObjectIdentifier_ScenarioObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_FiringObjectIdentifier_SimulationObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_MunitionObjectIdentifier_ScenarioObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_MunitionObjectIdentifier_SimulationObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_MunitionType_EntityKind = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_MunitionType_Domain = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_MunitionType_CountryCode = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_MunitionType_Category = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_MunitionType_Subcategory = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_MunitionType_Specific = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_MunitionType_Extra = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_TargetObjectIdentifier_ScenarioObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_TargetObjectIdentifier_SimulationObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_VariableDatumSet_NumberOfVariableDatums = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_VariableDatumSet_VariableDatums_DatumID = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_VariableDatumSet_VariableDatums_DatumLength = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_VariableDatumSet_VariableDatums_Padding = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
}

namespace Collision
{
using v_CollidingObjectIdentifier_ScenarioObjectID = nframework::nom::NUShort;
using v_CollidingObjectIdentifier_SimulationObjectID = nframework::nom::NUShort;
using v_CollisionType = nframework::nom::NEnum;
using v_CollisionLocation_BodyXDistance = nframework::nom::NFloat;
using v_CollisionLocation_BodyYDistance = nframework::nom::NFloat;
using v_CollisionLocation_BodyZDistance = nframework::nom::NFloat;
auto t_CollidingObjectIdentifier_ScenarioObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_CollidingObjectIdentifier_SimulationObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_CollisionType = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_CollisionLocation_BodyXDistance = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_CollisionLocation_BodyYDistance = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_CollisionLocation_BodyZDistance = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
}

namespace MunitionDetonation
{
using v_DetonationLocation_X = nframework::nom::NDouble;
using v_DetonationLocation_Y = nframework::nom::NDouble;
using v_DetonationLocation_Z = nframework::nom::NDouble;
using v_DetonationResultCode = nframework::nom::NEnum;
using v_FinalVelocityVector_XVelocity = nframework::nom::NFloat;
using v_FinalVelocityVector_YVelocity = nframework::nom::NFloat;
using v_FinalVelocityVector_ZVelocity = nframework::nom::NFloat;
using v_MunitionObjectIdentifier_ScenarioObjectID = nframework::nom::NUShort;
using v_MunitionObjectIdentifier_SimulationObjectID = nframework::nom::NUShort;
using v_RelativeDetonationLocation_BodyXDistance = nframework::nom::NFloat;
using v_RelativeDetonationLocation_BodyYDistance = nframework::nom::NFloat;
using v_RelativeDetonationLocation_BodyZDistance = nframework::nom::NFloat;
using v_TargetObjectIdentifier_ScenarioObjectID = nframework::nom::NUShort;
using v_TargetObjectIdentifier_SimulationObjectID = nframework::nom::NUShort;
auto t_DetonationLocation_X = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_DetonationLocation_Y = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_DetonationLocation_Z = [](nframework::nom::NValueType* val)->float64_t { return val->toDouble(); };
auto t_DetonationResultCode = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_FinalVelocityVector_XVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_FinalVelocityVector_YVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_FinalVelocityVector_ZVelocity = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_MunitionObjectIdentifier_ScenarioObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_MunitionObjectIdentifier_SimulationObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_RelativeDetonationLocation_BodyXDistance = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_RelativeDetonationLocation_BodyYDistance = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_RelativeDetonationLocation_BodyZDistance = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_TargetObjectIdentifier_ScenarioObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_TargetObjectIdentifier_SimulationObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
}

}
