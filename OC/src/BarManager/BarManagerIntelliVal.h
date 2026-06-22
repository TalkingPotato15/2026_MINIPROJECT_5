#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-04-16 13:53:10

namespace nframework::intellival
{
namespace AirThreatInformation
{
using v_Header_TopicLabel = nframework::nom::NUShort;
using v_Header_TopicSize = nframework::nom::NUShort;
using v_Header_SourceID = nframework::nom::NByte;
using v_Header_TopicClass = nframework::nom::NByte;
using v_Header_TopicNumber = nframework::nom::NUShort;
using v_Header_SystemTime = nframework::nom::NUInteger64;
using v_TimeTick = nframework::nom::NUInteger;
using v_SimulationFlag = nframework::nom::NUShort;
using v_ObjectCount = nframework::nom::NUShort;
using v_AirThreatMessage_ObjectID = nframework::nom::NUShort;
using v_AirThreatMessage_ObjectType = nframework::nom::NByte;
using v_AirThreatMessage_DestructionFlag = nframework::nom::NByte;
using v_AirThreatMessage_PositionX = nframework::nom::NUInteger;
using v_AirThreatMessage_PositionY = nframework::nom::NUInteger;
using v_AirThreatMessage_PositionZ = nframework::nom::NUInteger;
using v_AirThreatMessage_VelocityX = nframework::nom::NUShort;
using v_AirThreatMessage_VelocityY = nframework::nom::NUShort;
using v_AirThreatMessage_VelocityZ = nframework::nom::NUShort;
using v_AirThreatMessage_AccelerationX = nframework::nom::NUShort;
using v_AirThreatMessage_AccelerationY = nframework::nom::NUShort;
using v_AirThreatMessage_AccelerationZ = nframework::nom::NUShort;
using v_AirThreatMessage_MeanRCS = nframework::nom::NUShort;
using v_AirThreatMessage_Reserved = nframework::nom::NByte;
using v_AirThreatMessage_JammingType = nframework::nom::NByte;
using v_AirThreatMessage_JammingPower = nframework::nom::NUShort;
using v_AirThreatMessage_JammingPullOff = nframework::nom::NUShort;
auto t_Header_TopicLabel = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_TopicSize = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SourceID = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicClass = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SystemTime = [](nframework::nom::NValueType* val)->uint64_t { return val->toUInt64(); };
auto t_TimeTick = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_SimulationFlag = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ObjectCount = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_AirThreatMessage_ObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_AirThreatMessage_ObjectType = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_AirThreatMessage_DestructionFlag = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_AirThreatMessage_PositionX = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AirThreatMessage_PositionY = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AirThreatMessage_PositionZ = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_AirThreatMessage_VelocityX = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_AirThreatMessage_VelocityY = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_AirThreatMessage_VelocityZ = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_AirThreatMessage_AccelerationX = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_AirThreatMessage_AccelerationY = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_AirThreatMessage_AccelerationZ = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_AirThreatMessage_MeanRCS = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_AirThreatMessage_Reserved = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_AirThreatMessage_JammingType = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_AirThreatMessage_JammingPower = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_AirThreatMessage_JammingPullOff = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
}

namespace InterceptorInformation
{
using v_Header_TopicLabel = nframework::nom::NUShort;
using v_Header_TopicSize = nframework::nom::NUShort;
using v_Header_SourceID = nframework::nom::NByte;
using v_Header_TopicClass = nframework::nom::NByte;
using v_Header_TopicNumber = nframework::nom::NUShort;
using v_Header_SystemTime = nframework::nom::NUInteger64;
using v_TimeTick = nframework::nom::NUInteger;
using v_SimulationFlag = nframework::nom::NUShort;
using v_ObjectCount = nframework::nom::NUShort;
using v_InterceptorMessage_ObjectID = nframework::nom::NUShort;
using v_InterceptorMessage_MissileType = nframework::nom::NByte;
using v_InterceptorMessage_DestructionFlag = nframework::nom::NByte;
using v_InterceptorMessage_PositionX = nframework::nom::NInteger;
using v_InterceptorMessage_PositionY = nframework::nom::NInteger;
using v_InterceptorMessage_PositionZ = nframework::nom::NInteger;
using v_InterceptorMessage_VelocityX = nframework::nom::NShort;
using v_InterceptorMessage_VelocityY = nframework::nom::NShort;
using v_InterceptorMessage_VelocityZ = nframework::nom::NShort;
using v_InterceptorMessage_AccelerationX = nframework::nom::NShort;
using v_InterceptorMessage_AccelerationY = nframework::nom::NShort;
using v_InterceptorMessage_AccelerationZ = nframework::nom::NShort;
using v_InterceptorMessage_MeanRCS = nframework::nom::NUShort;
using v_InterceptorMessage_Reserved = nframework::nom::NUShort;
using v_InterceptorMessage_SignalPower = nframework::nom::NUShort;
using v_InterceptorMessage_SeekerPhase = nframework::nom::NByte;
using v_InterceptorMessage_AddressKey = nframework::nom::NUShort;
auto t_Header_TopicLabel = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_TopicSize = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SourceID = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicClass = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SystemTime = [](nframework::nom::NValueType* val)->uint64_t { return val->toUInt64(); };
auto t_TimeTick = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_SimulationFlag = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_ObjectCount = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_InterceptorMessage_ObjectID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_InterceptorMessage_MissileType = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_InterceptorMessage_DestructionFlag = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_InterceptorMessage_PositionX = [](nframework::nom::NValueType* val)->int32_t { return val->toInt(); };
auto t_InterceptorMessage_PositionY = [](nframework::nom::NValueType* val)->int32_t { return val->toInt(); };
auto t_InterceptorMessage_PositionZ = [](nframework::nom::NValueType* val)->int32_t { return val->toInt(); };
auto t_InterceptorMessage_VelocityX = [](nframework::nom::NValueType* val)->int16_t { return val->toShort(); };
auto t_InterceptorMessage_VelocityY = [](nframework::nom::NValueType* val)->int16_t { return val->toShort(); };
auto t_InterceptorMessage_VelocityZ = [](nframework::nom::NValueType* val)->int16_t { return val->toShort(); };
auto t_InterceptorMessage_AccelerationX = [](nframework::nom::NValueType* val)->int16_t { return val->toShort(); };
auto t_InterceptorMessage_AccelerationY = [](nframework::nom::NValueType* val)->int16_t { return val->toShort(); };
auto t_InterceptorMessage_AccelerationZ = [](nframework::nom::NValueType* val)->int16_t { return val->toShort(); };
auto t_InterceptorMessage_MeanRCS = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_InterceptorMessage_Reserved = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_InterceptorMessage_SignalPower = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_InterceptorMessage_SeekerPhase = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_InterceptorMessage_AddressKey = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
}

namespace UplinkInformation
{
using v_Header_TopicLabel = nframework::nom::NUShort;
using v_Header_TopicSize = nframework::nom::NUShort;
using v_Header_SourceID = nframework::nom::NByte;
using v_Header_TopicClass = nframework::nom::NByte;
using v_Header_TopicNumber = nframework::nom::NUShort;
using v_Header_SystemTime = nframework::nom::NUInteger64;
using v_TimeTick = nframework::nom::NUInteger;
using v_UplinkMessage_AddressKey = nframework::nom::NUShort;
using v_UplinkMessage_MissileType = nframework::nom::NUShort;
using v_UplinkMessage_Data = nframework::nom::NUShort;
auto t_Header_TopicLabel = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_TopicSize = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SourceID = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicClass = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SystemTime = [](nframework::nom::NValueType* val)->uint64_t { return val->toUInt64(); };
auto t_TimeTick = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_UplinkMessage_AddressKey = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_UplinkMessage_MissileType = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_UplinkMessage_Data = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
}

namespace DownlinkInformation
{
using v_Header_TopicLabel = nframework::nom::NUShort;
using v_Header_TopicSize = nframework::nom::NUShort;
using v_Header_SourceID = nframework::nom::NByte;
using v_Header_TopicClass = nframework::nom::NByte;
using v_Header_TopicNumber = nframework::nom::NUShort;
using v_Header_SystemTime = nframework::nom::NUInteger64;
using v_TimeTick = nframework::nom::NUInteger;
using v_ObjectCount = nframework::nom::NUInteger;
using v_DownlinkMessage_AddressKey = nframework::nom::NUShort;
using v_DownlinkMessage_CRC = nframework::nom::NUShort;
using v_DownlinkMessage_Data = nframework::nom::NUShort;
auto t_Header_TopicLabel = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_TopicSize = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SourceID = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicClass = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SystemTime = [](nframework::nom::NValueType* val)->uint64_t { return val->toUInt64(); };
auto t_TimeTick = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_ObjectCount = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_DownlinkMessage_AddressKey = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_DownlinkMessage_CRC = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_DownlinkMessage_Data = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
}

namespace TimeTickInformation
{
using v_Header_TopicLabel = nframework::nom::NUShort;
using v_Header_TopicSize = nframework::nom::NUShort;
using v_Header_SourceID = nframework::nom::NByte;
using v_Header_TopicClass = nframework::nom::NByte;
using v_Header_TopicNumber = nframework::nom::NUShort;
using v_Header_SystemTime = nframework::nom::NUInteger64;
using v_TimeTickMessage_SyncCycle = nframework::nom::NUInteger;
using v_TimeTickMessage_TimeTick = nframework::nom::NUInteger;
auto t_Header_TopicLabel = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_TopicSize = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SourceID = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicClass = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SystemTime = [](nframework::nom::NValueType* val)->uint64_t { return val->toUInt64(); };
auto t_TimeTickMessage_SyncCycle = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_TimeTickMessage_TimeTick = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace MFRAttitudeInformation
{
using v_Header_TopicLabel = nframework::nom::NUShort;
using v_Header_TopicSize = nframework::nom::NUShort;
using v_Header_SourceID = nframework::nom::NByte;
using v_Header_TopicClass = nframework::nom::NByte;
using v_Header_TopicNumber = nframework::nom::NUShort;
using v_Header_SystemTime = nframework::nom::NUInteger64;
using v_MFRAttitudeMessage_MFRAntennaRoll = nframework::nom::NFloat;
using v_MFRAttitudeMessage_MFRAntennaPitch = nframework::nom::NFloat;
using v_MFRAttitudeMessage_MFRAntennaHeading = nframework::nom::NFloat;
auto t_Header_TopicLabel = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_TopicSize = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SourceID = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicClass = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Header_TopicNumber = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SystemTime = [](nframework::nom::NValueType* val)->uint64_t { return val->toUInt64(); };
auto t_MFRAttitudeMessage_MFRAntennaRoll = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_MFRAttitudeMessage_MFRAntennaPitch = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
auto t_MFRAttitudeMessage_MFRAntennaHeading = [](nframework::nom::NValueType* val)->float32_t { return val->toFloat(); };
}

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

namespace DDSJoinStatus
{
using v_JoinStatus = nframework::nom::NBool;
auto t_JoinStatus = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
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
