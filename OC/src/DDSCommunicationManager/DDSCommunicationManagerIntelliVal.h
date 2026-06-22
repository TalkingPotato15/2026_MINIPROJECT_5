#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-04-16 13:53:12

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

namespace DDSJoinStatus
{
using v_JoinStatus = nframework::nom::NBool;
auto t_JoinStatus = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
}

}
