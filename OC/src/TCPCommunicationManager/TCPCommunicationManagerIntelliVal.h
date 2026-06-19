#include <nFramework/nom/NOMMain.h>

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-04-16 13:53:12

namespace nframework::intellival
{
namespace LTE_SEND_MESSAGE
{
using v_Header_MessageID = nframework::nom::NUShort;
using v_Header_MessageLength = nframework::nom::NUShort;
using v_Header_SystemTime1 = nframework::nom::NUInteger;
using v_Header_SystemTime2 = nframework::nom::NUInteger;
using v_Body = nframework::nom::NUInteger;
auto t_Header_MessageID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_MessageLength = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SystemTime1 = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_Header_SystemTime2 = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_Body = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
}

namespace RTI_SEND_MESSAGE
{
using v_Header_MessageID = nframework::nom::NUShort;
using v_Header_MessageLength = nframework::nom::NUShort;
using v_Header_SystemTime1 = nframework::nom::NUInteger;
using v_Header_SystemTime2 = nframework::nom::NUInteger;
using v_Data = nframework::nom::NBool;
auto t_Header_MessageID = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_MessageLength = [](nframework::nom::NValueType* val)->uint16_t { return val->toUShort(); };
auto t_Header_SystemTime1 = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_Header_SystemTime2 = [](nframework::nom::NValueType* val)->uint32_t { return val->toUInt(); };
auto t_Data = [](nframework::nom::NValueType* val)->uint8_t { return val->toByte(); };
}

}
