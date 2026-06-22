#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-04-16 13:53:13

namespace nframework::intellival
{
namespace CFCS_Status
{
using v_MessageHeader_MessageID = nframework::nom::NUShort;
using v_MessageHeader_MessageLength = nframework::nom::NUShort;
using v_MessageHeader_SystemTime1 = nframework::nom::NUInteger;
using v_MessageHeader_SystemTime2 = nframework::nom::NUInteger;
using v_CFCSOperationalCondition = nframework::nom::NEnum;
using v_Padding_PaddingA = nframework::nom::NByte;
using v_Padding_PaddingB = nframework::nom::NByte;
using v_Padding_PaddingC = nframework::nom::NByte;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_MessageHeader_SystemTime1 = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_SystemTime2 = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_CFCSOperationalCondition = [](nframework::nom::NValueType* val)->tstring { return val->toString(); };
auto t_Padding_PaddingA = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Padding_PaddingB = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
auto t_Padding_PaddingC = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
}

namespace CFCS_Connect
{
using v_MessageHeader_MessageID = nframework::nom::NUShort;
using v_MessageHeader_MessageLength = nframework::nom::NUShort;
using v_MessageHeader_SystemTime1 = nframework::nom::NUInteger;
using v_MessageHeader_SystemTime2 = nframework::nom::NUInteger;
auto t_MessageHeader_MessageID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_MessageHeader_MessageLength = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_MessageHeader_SystemTime1 = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_MessageHeader_SystemTime2 = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

}
