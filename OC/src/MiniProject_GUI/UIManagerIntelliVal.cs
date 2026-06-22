using System;
using nframework.nom;

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-04-16 13:53:13

namespace nframework.intellival
{
namespace BaseEntity_PhysicalEntity_Platform_Aircraft
{
public class v_AccelerationVector_XAcceleration : NFloat{
public v_AccelerationVector_XAcceleration(float x):base(x){}
public v_AccelerationVector_XAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_YAcceleration : NFloat{
public v_AccelerationVector_YAcceleration(float x):base(x){}
public v_AccelerationVector_YAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_ZAcceleration : NFloat{
public v_AccelerationVector_ZAcceleration(float x):base(x){}
public v_AccelerationVector_ZAcceleration(NFloat t):base(t.value){}}
public class v_EntityType_EntityKind : NByte{
public v_EntityType_EntityKind(byte x):base(x){}
public v_EntityType_EntityKind(NByte t):base(t.value){}}
public class v_EntityType_Domain : NByte{
public v_EntityType_Domain(byte x):base(x){}
public v_EntityType_Domain(NByte t):base(t.value){}}
public class v_EntityType_CountryCode : NUShort{
public v_EntityType_CountryCode(ushort x):base(x){}
public v_EntityType_CountryCode(NUShort t):base(t.value){}}
public class v_EntityType_Category : NByte{
public v_EntityType_Category(byte x):base(x){}
public v_EntityType_Category(NByte t):base(t.value){}}
public class v_EntityType_Subcategory : NByte{
public v_EntityType_Subcategory(byte x):base(x){}
public v_EntityType_Subcategory(NByte t):base(t.value){}}
public class v_EntityType_Specific : NByte{
public v_EntityType_Specific(byte x):base(x){}
public v_EntityType_Specific(NByte t):base(t.value){}}
public class v_EntityType_Extra : NByte{
public v_EntityType_Extra(byte x):base(x){}
public v_EntityType_Extra(NByte t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_SiteID : NUShort{
public v_EntityIdentifier_FederateIdentifier_SiteID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_ApplicationID : NUShort{
public v_EntityIdentifier_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_EntityNumber : NUShort{
public v_EntityIdentifier_EntityNumber(ushort x):base(x){}
public v_EntityIdentifier_EntityNumber(NUShort t):base(t.value){}}
public class v_IsFrozen : NBool{
public v_IsFrozen(bool x):base(x){}
public v_IsFrozen(NBool t):base(t.value){}}
public class v_Orientation_Psi : NFloat{
public v_Orientation_Psi(float x):base(x){}
public v_Orientation_Psi(NFloat t):base(t.value){}}
public class v_Orientation_Theta : NFloat{
public v_Orientation_Theta(float x):base(x){}
public v_Orientation_Theta(NFloat t):base(t.value){}}
public class v_Orientation_Phi : NFloat{
public v_Orientation_Phi(float x):base(x){}
public v_Orientation_Phi(NFloat t):base(t.value){}}
public class v_WorldLocation_X : NDouble{
public v_WorldLocation_X(double x):base(x){}
public v_WorldLocation_X(NDouble t):base(t.value){}}
public class v_WorldLocation_Y : NDouble{
public v_WorldLocation_Y(double x):base(x){}
public v_WorldLocation_Y(NDouble t):base(t.value){}}
public class v_WorldLocation_Z : NDouble{
public v_WorldLocation_Z(double x):base(x){}
public v_WorldLocation_Z(NDouble t):base(t.value){}}
public class v_VelocityVector_XVelocity : NFloat{
public v_VelocityVector_XVelocity(float x):base(x){}
public v_VelocityVector_XVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_YVelocity : NFloat{
public v_VelocityVector_YVelocity(float x):base(x){}
public v_VelocityVector_YVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_ZVelocity : NFloat{
public v_VelocityVector_ZVelocity(float x):base(x){}
public v_VelocityVector_ZVelocity(NFloat t):base(t.value){}}
public class v_ForceIdentifier : NEnum{
public v_ForceIdentifier(string x):base(x){}
public v_ForceIdentifier(int v):base(v){}
public v_ForceIdentifier(string x, int v):base(x, v){}
public v_ForceIdentifier(NEnum t):base(t.enumerator, t.enumValue){}}
public class T{
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_XAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_YAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_ZAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,byte> t_EntityType_EntityKind = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Domain = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityType_CountryCode = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Category = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Subcategory = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Specific = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Extra = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_IsFrozen = val => val.toByte();
public static Func<nframework.nom.NValueType,float> t_Orientation_Psi = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Theta = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Phi = val => val.toFloat();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_XVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_YVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_ZVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,string> t_ForceIdentifier = val => val.toString();
}

}

namespace BaseEntity_PhysicalEntity_Munition
{
public class v_AccelerationVector_XAcceleration : NFloat{
public v_AccelerationVector_XAcceleration(float x):base(x){}
public v_AccelerationVector_XAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_YAcceleration : NFloat{
public v_AccelerationVector_YAcceleration(float x):base(x){}
public v_AccelerationVector_YAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_ZAcceleration : NFloat{
public v_AccelerationVector_ZAcceleration(float x):base(x){}
public v_AccelerationVector_ZAcceleration(NFloat t):base(t.value){}}
public class v_EntityType_EntityKind : NByte{
public v_EntityType_EntityKind(byte x):base(x){}
public v_EntityType_EntityKind(NByte t):base(t.value){}}
public class v_EntityType_Domain : NByte{
public v_EntityType_Domain(byte x):base(x){}
public v_EntityType_Domain(NByte t):base(t.value){}}
public class v_EntityType_CountryCode : NUShort{
public v_EntityType_CountryCode(ushort x):base(x){}
public v_EntityType_CountryCode(NUShort t):base(t.value){}}
public class v_EntityType_Category : NByte{
public v_EntityType_Category(byte x):base(x){}
public v_EntityType_Category(NByte t):base(t.value){}}
public class v_EntityType_Subcategory : NByte{
public v_EntityType_Subcategory(byte x):base(x){}
public v_EntityType_Subcategory(NByte t):base(t.value){}}
public class v_EntityType_Specific : NByte{
public v_EntityType_Specific(byte x):base(x){}
public v_EntityType_Specific(NByte t):base(t.value){}}
public class v_EntityType_Extra : NByte{
public v_EntityType_Extra(byte x):base(x){}
public v_EntityType_Extra(NByte t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_SiteID : NUShort{
public v_EntityIdentifier_FederateIdentifier_SiteID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_ApplicationID : NUShort{
public v_EntityIdentifier_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_EntityNumber : NUShort{
public v_EntityIdentifier_EntityNumber(ushort x):base(x){}
public v_EntityIdentifier_EntityNumber(NUShort t):base(t.value){}}
public class v_IsFrozen : NBool{
public v_IsFrozen(bool x):base(x){}
public v_IsFrozen(NBool t):base(t.value){}}
public class v_Orientation_Psi : NFloat{
public v_Orientation_Psi(float x):base(x){}
public v_Orientation_Psi(NFloat t):base(t.value){}}
public class v_Orientation_Theta : NFloat{
public v_Orientation_Theta(float x):base(x){}
public v_Orientation_Theta(NFloat t):base(t.value){}}
public class v_Orientation_Phi : NFloat{
public v_Orientation_Phi(float x):base(x){}
public v_Orientation_Phi(NFloat t):base(t.value){}}
public class v_WorldLocation_X : NDouble{
public v_WorldLocation_X(double x):base(x){}
public v_WorldLocation_X(NDouble t):base(t.value){}}
public class v_WorldLocation_Y : NDouble{
public v_WorldLocation_Y(double x):base(x){}
public v_WorldLocation_Y(NDouble t):base(t.value){}}
public class v_WorldLocation_Z : NDouble{
public v_WorldLocation_Z(double x):base(x){}
public v_WorldLocation_Z(NDouble t):base(t.value){}}
public class v_VelocityVector_XVelocity : NFloat{
public v_VelocityVector_XVelocity(float x):base(x){}
public v_VelocityVector_XVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_YVelocity : NFloat{
public v_VelocityVector_YVelocity(float x):base(x){}
public v_VelocityVector_YVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_ZVelocity : NFloat{
public v_VelocityVector_ZVelocity(float x):base(x){}
public v_VelocityVector_ZVelocity(NFloat t):base(t.value){}}
public class v_ForceIdentifier : NEnum{
public v_ForceIdentifier(string x):base(x){}
public v_ForceIdentifier(int v):base(v){}
public v_ForceIdentifier(string x, int v):base(x, v){}
public v_ForceIdentifier(NEnum t):base(t.enumerator, t.enumValue){}}
public class T{
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_XAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_YAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_ZAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,byte> t_EntityType_EntityKind = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Domain = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityType_CountryCode = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Category = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Subcategory = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Specific = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Extra = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_IsFrozen = val => val.toByte();
public static Func<nframework.nom.NValueType,float> t_Orientation_Psi = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Theta = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Phi = val => val.toFloat();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_XVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_YVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_ZVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,string> t_ForceIdentifier = val => val.toString();
}

}

namespace BaseEntity_PhysicalEntity_Sensor
{
public class v_AccelerationVector_XAcceleration : NFloat{
public v_AccelerationVector_XAcceleration(float x):base(x){}
public v_AccelerationVector_XAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_YAcceleration : NFloat{
public v_AccelerationVector_YAcceleration(float x):base(x){}
public v_AccelerationVector_YAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_ZAcceleration : NFloat{
public v_AccelerationVector_ZAcceleration(float x):base(x){}
public v_AccelerationVector_ZAcceleration(NFloat t):base(t.value){}}
public class v_EntityType_EntityKind : NByte{
public v_EntityType_EntityKind(byte x):base(x){}
public v_EntityType_EntityKind(NByte t):base(t.value){}}
public class v_EntityType_Domain : NByte{
public v_EntityType_Domain(byte x):base(x){}
public v_EntityType_Domain(NByte t):base(t.value){}}
public class v_EntityType_CountryCode : NUShort{
public v_EntityType_CountryCode(ushort x):base(x){}
public v_EntityType_CountryCode(NUShort t):base(t.value){}}
public class v_EntityType_Category : NByte{
public v_EntityType_Category(byte x):base(x){}
public v_EntityType_Category(NByte t):base(t.value){}}
public class v_EntityType_Subcategory : NByte{
public v_EntityType_Subcategory(byte x):base(x){}
public v_EntityType_Subcategory(NByte t):base(t.value){}}
public class v_EntityType_Specific : NByte{
public v_EntityType_Specific(byte x):base(x){}
public v_EntityType_Specific(NByte t):base(t.value){}}
public class v_EntityType_Extra : NByte{
public v_EntityType_Extra(byte x):base(x){}
public v_EntityType_Extra(NByte t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_SiteID : NUShort{
public v_EntityIdentifier_FederateIdentifier_SiteID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_ApplicationID : NUShort{
public v_EntityIdentifier_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_EntityNumber : NUShort{
public v_EntityIdentifier_EntityNumber(ushort x):base(x){}
public v_EntityIdentifier_EntityNumber(NUShort t):base(t.value){}}
public class v_IsFrozen : NBool{
public v_IsFrozen(bool x):base(x){}
public v_IsFrozen(NBool t):base(t.value){}}
public class v_Orientation_Psi : NFloat{
public v_Orientation_Psi(float x):base(x){}
public v_Orientation_Psi(NFloat t):base(t.value){}}
public class v_Orientation_Theta : NFloat{
public v_Orientation_Theta(float x):base(x){}
public v_Orientation_Theta(NFloat t):base(t.value){}}
public class v_Orientation_Phi : NFloat{
public v_Orientation_Phi(float x):base(x){}
public v_Orientation_Phi(NFloat t):base(t.value){}}
public class v_WorldLocation_X : NDouble{
public v_WorldLocation_X(double x):base(x){}
public v_WorldLocation_X(NDouble t):base(t.value){}}
public class v_WorldLocation_Y : NDouble{
public v_WorldLocation_Y(double x):base(x){}
public v_WorldLocation_Y(NDouble t):base(t.value){}}
public class v_WorldLocation_Z : NDouble{
public v_WorldLocation_Z(double x):base(x){}
public v_WorldLocation_Z(NDouble t):base(t.value){}}
public class v_VelocityVector_XVelocity : NFloat{
public v_VelocityVector_XVelocity(float x):base(x){}
public v_VelocityVector_XVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_YVelocity : NFloat{
public v_VelocityVector_YVelocity(float x):base(x){}
public v_VelocityVector_YVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_ZVelocity : NFloat{
public v_VelocityVector_ZVelocity(float x):base(x){}
public v_VelocityVector_ZVelocity(NFloat t):base(t.value){}}
public class v_ForceIdentifier : NEnum{
public v_ForceIdentifier(string x):base(x){}
public v_ForceIdentifier(int v):base(v){}
public v_ForceIdentifier(string x, int v):base(x, v){}
public v_ForceIdentifier(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_AntennaRaised : NBool{
public v_AntennaRaised(bool x):base(x){}
public v_AntennaRaised(NBool t):base(t.value){}}
public class v_BlackoutLightsOn : NBool{
public v_BlackoutLightsOn(bool x):base(x){}
public v_BlackoutLightsOn(NBool t):base(t.value){}}
public class v_LightsOn : NBool{
public v_LightsOn(bool x):base(x){}
public v_LightsOn(NBool t):base(t.value){}}
public class v_InteriorLightsOn : NBool{
public v_InteriorLightsOn(bool x):base(x){}
public v_InteriorLightsOn(NBool t):base(t.value){}}
public class v_MissionKill : NBool{
public v_MissionKill(bool x):base(x){}
public v_MissionKill(NBool t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_XAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_YAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_ZAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,byte> t_EntityType_EntityKind = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Domain = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityType_CountryCode = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Category = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Subcategory = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Specific = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Extra = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_IsFrozen = val => val.toByte();
public static Func<nframework.nom.NValueType,float> t_Orientation_Psi = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Theta = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Phi = val => val.toFloat();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_XVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_YVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_ZVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,string> t_ForceIdentifier = val => val.toString();
public static Func<nframework.nom.NValueType,byte> t_AntennaRaised = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_BlackoutLightsOn = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_LightsOn = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_InteriorLightsOn = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_MissionKill = val => val.toByte();
}

}

namespace BaseEntity_PhysicalEntity_Platform_GroundVehicle
{
public class v_AccelerationVector_XAcceleration : NFloat{
public v_AccelerationVector_XAcceleration(float x):base(x){}
public v_AccelerationVector_XAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_YAcceleration : NFloat{
public v_AccelerationVector_YAcceleration(float x):base(x){}
public v_AccelerationVector_YAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_ZAcceleration : NFloat{
public v_AccelerationVector_ZAcceleration(float x):base(x){}
public v_AccelerationVector_ZAcceleration(NFloat t):base(t.value){}}
public class v_EntityType_EntityKind : NByte{
public v_EntityType_EntityKind(byte x):base(x){}
public v_EntityType_EntityKind(NByte t):base(t.value){}}
public class v_EntityType_Domain : NByte{
public v_EntityType_Domain(byte x):base(x){}
public v_EntityType_Domain(NByte t):base(t.value){}}
public class v_EntityType_CountryCode : NUShort{
public v_EntityType_CountryCode(ushort x):base(x){}
public v_EntityType_CountryCode(NUShort t):base(t.value){}}
public class v_EntityType_Category : NByte{
public v_EntityType_Category(byte x):base(x){}
public v_EntityType_Category(NByte t):base(t.value){}}
public class v_EntityType_Subcategory : NByte{
public v_EntityType_Subcategory(byte x):base(x){}
public v_EntityType_Subcategory(NByte t):base(t.value){}}
public class v_EntityType_Specific : NByte{
public v_EntityType_Specific(byte x):base(x){}
public v_EntityType_Specific(NByte t):base(t.value){}}
public class v_EntityType_Extra : NByte{
public v_EntityType_Extra(byte x):base(x){}
public v_EntityType_Extra(NByte t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_SiteID : NUShort{
public v_EntityIdentifier_FederateIdentifier_SiteID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_ApplicationID : NUShort{
public v_EntityIdentifier_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_EntityNumber : NUShort{
public v_EntityIdentifier_EntityNumber(ushort x):base(x){}
public v_EntityIdentifier_EntityNumber(NUShort t):base(t.value){}}
public class v_IsFrozen : NBool{
public v_IsFrozen(bool x):base(x){}
public v_IsFrozen(NBool t):base(t.value){}}
public class v_Orientation_Psi : NFloat{
public v_Orientation_Psi(float x):base(x){}
public v_Orientation_Psi(NFloat t):base(t.value){}}
public class v_Orientation_Theta : NFloat{
public v_Orientation_Theta(float x):base(x){}
public v_Orientation_Theta(NFloat t):base(t.value){}}
public class v_Orientation_Phi : NFloat{
public v_Orientation_Phi(float x):base(x){}
public v_Orientation_Phi(NFloat t):base(t.value){}}
public class v_WorldLocation_X : NDouble{
public v_WorldLocation_X(double x):base(x){}
public v_WorldLocation_X(NDouble t):base(t.value){}}
public class v_WorldLocation_Y : NDouble{
public v_WorldLocation_Y(double x):base(x){}
public v_WorldLocation_Y(NDouble t):base(t.value){}}
public class v_WorldLocation_Z : NDouble{
public v_WorldLocation_Z(double x):base(x){}
public v_WorldLocation_Z(NDouble t):base(t.value){}}
public class v_VelocityVector_XVelocity : NFloat{
public v_VelocityVector_XVelocity(float x):base(x){}
public v_VelocityVector_XVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_YVelocity : NFloat{
public v_VelocityVector_YVelocity(float x):base(x){}
public v_VelocityVector_YVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_ZVelocity : NFloat{
public v_VelocityVector_ZVelocity(float x):base(x){}
public v_VelocityVector_ZVelocity(NFloat t):base(t.value){}}
public class v_ForceIdentifier : NEnum{
public v_ForceIdentifier(string x):base(x){}
public v_ForceIdentifier(int v):base(v){}
public v_ForceIdentifier(string x, int v):base(x, v){}
public v_ForceIdentifier(NEnum t):base(t.enumerator, t.enumValue){}}
public class T{
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_XAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_YAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_ZAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,byte> t_EntityType_EntityKind = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Domain = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityType_CountryCode = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Category = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Subcategory = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Specific = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Extra = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_IsFrozen = val => val.toByte();
public static Func<nframework.nom.NValueType,float> t_Orientation_Psi = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Theta = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Phi = val => val.toFloat();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_XVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_YVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_ZVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,string> t_ForceIdentifier = val => val.toString();
}

}

namespace BaseEntity_PhysicalEntity_Platform_SurfaceVessel
{
public class v_AccelerationVector_XAcceleration : NFloat{
public v_AccelerationVector_XAcceleration(float x):base(x){}
public v_AccelerationVector_XAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_YAcceleration : NFloat{
public v_AccelerationVector_YAcceleration(float x):base(x){}
public v_AccelerationVector_YAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_ZAcceleration : NFloat{
public v_AccelerationVector_ZAcceleration(float x):base(x){}
public v_AccelerationVector_ZAcceleration(NFloat t):base(t.value){}}
public class v_EntityType_EntityKind : NByte{
public v_EntityType_EntityKind(byte x):base(x){}
public v_EntityType_EntityKind(NByte t):base(t.value){}}
public class v_EntityType_Domain : NByte{
public v_EntityType_Domain(byte x):base(x){}
public v_EntityType_Domain(NByte t):base(t.value){}}
public class v_EntityType_CountryCode : NUShort{
public v_EntityType_CountryCode(ushort x):base(x){}
public v_EntityType_CountryCode(NUShort t):base(t.value){}}
public class v_EntityType_Category : NByte{
public v_EntityType_Category(byte x):base(x){}
public v_EntityType_Category(NByte t):base(t.value){}}
public class v_EntityType_Subcategory : NByte{
public v_EntityType_Subcategory(byte x):base(x){}
public v_EntityType_Subcategory(NByte t):base(t.value){}}
public class v_EntityType_Specific : NByte{
public v_EntityType_Specific(byte x):base(x){}
public v_EntityType_Specific(NByte t):base(t.value){}}
public class v_EntityType_Extra : NByte{
public v_EntityType_Extra(byte x):base(x){}
public v_EntityType_Extra(NByte t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_SiteID : NUShort{
public v_EntityIdentifier_FederateIdentifier_SiteID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_ApplicationID : NUShort{
public v_EntityIdentifier_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_EntityNumber : NUShort{
public v_EntityIdentifier_EntityNumber(ushort x):base(x){}
public v_EntityIdentifier_EntityNumber(NUShort t):base(t.value){}}
public class v_IsFrozen : NBool{
public v_IsFrozen(bool x):base(x){}
public v_IsFrozen(NBool t):base(t.value){}}
public class v_Orientation_Psi : NFloat{
public v_Orientation_Psi(float x):base(x){}
public v_Orientation_Psi(NFloat t):base(t.value){}}
public class v_Orientation_Theta : NFloat{
public v_Orientation_Theta(float x):base(x){}
public v_Orientation_Theta(NFloat t):base(t.value){}}
public class v_Orientation_Phi : NFloat{
public v_Orientation_Phi(float x):base(x){}
public v_Orientation_Phi(NFloat t):base(t.value){}}
public class v_WorldLocation_X : NDouble{
public v_WorldLocation_X(double x):base(x){}
public v_WorldLocation_X(NDouble t):base(t.value){}}
public class v_WorldLocation_Y : NDouble{
public v_WorldLocation_Y(double x):base(x){}
public v_WorldLocation_Y(NDouble t):base(t.value){}}
public class v_WorldLocation_Z : NDouble{
public v_WorldLocation_Z(double x):base(x){}
public v_WorldLocation_Z(NDouble t):base(t.value){}}
public class v_VelocityVector_XVelocity : NFloat{
public v_VelocityVector_XVelocity(float x):base(x){}
public v_VelocityVector_XVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_YVelocity : NFloat{
public v_VelocityVector_YVelocity(float x):base(x){}
public v_VelocityVector_YVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_ZVelocity : NFloat{
public v_VelocityVector_ZVelocity(float x):base(x){}
public v_VelocityVector_ZVelocity(NFloat t):base(t.value){}}
public class v_ForceIdentifier : NEnum{
public v_ForceIdentifier(string x):base(x){}
public v_ForceIdentifier(int v):base(v){}
public v_ForceIdentifier(string x, int v):base(x, v){}
public v_ForceIdentifier(NEnum t):base(t.enumerator, t.enumValue){}}
public class T{
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_XAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_YAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_ZAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,byte> t_EntityType_EntityKind = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Domain = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityType_CountryCode = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Category = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Subcategory = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Specific = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Extra = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_IsFrozen = val => val.toByte();
public static Func<nframework.nom.NValueType,float> t_Orientation_Psi = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Theta = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Phi = val => val.toFloat();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_XVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_YVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_ZVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,string> t_ForceIdentifier = val => val.toString();
}

}

namespace BaseEntity_PhysicalEntity_Platform_Aircraft_GUI
{
public class v_LogicalTime : NUInteger{
public v_LogicalTime(uint x):base(x){}
public v_LogicalTime(NUInteger t):base(t.value){}}
public class v_AccelerationVector_XAcceleration : NFloat{
public v_AccelerationVector_XAcceleration(float x):base(x){}
public v_AccelerationVector_XAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_YAcceleration : NFloat{
public v_AccelerationVector_YAcceleration(float x):base(x){}
public v_AccelerationVector_YAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_ZAcceleration : NFloat{
public v_AccelerationVector_ZAcceleration(float x):base(x){}
public v_AccelerationVector_ZAcceleration(NFloat t):base(t.value){}}
public class v_EntityType_EntityKind : NByte{
public v_EntityType_EntityKind(byte x):base(x){}
public v_EntityType_EntityKind(NByte t):base(t.value){}}
public class v_EntityType_Domain : NByte{
public v_EntityType_Domain(byte x):base(x){}
public v_EntityType_Domain(NByte t):base(t.value){}}
public class v_EntityType_CountryCode : NUShort{
public v_EntityType_CountryCode(ushort x):base(x){}
public v_EntityType_CountryCode(NUShort t):base(t.value){}}
public class v_EntityType_Category : NByte{
public v_EntityType_Category(byte x):base(x){}
public v_EntityType_Category(NByte t):base(t.value){}}
public class v_EntityType_Subcategory : NByte{
public v_EntityType_Subcategory(byte x):base(x){}
public v_EntityType_Subcategory(NByte t):base(t.value){}}
public class v_EntityType_Specific : NByte{
public v_EntityType_Specific(byte x):base(x){}
public v_EntityType_Specific(NByte t):base(t.value){}}
public class v_EntityType_Extra : NByte{
public v_EntityType_Extra(byte x):base(x){}
public v_EntityType_Extra(NByte t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_SiteID : NUShort{
public v_EntityIdentifier_FederateIdentifier_SiteID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_ApplicationID : NUShort{
public v_EntityIdentifier_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_EntityNumber : NUShort{
public v_EntityIdentifier_EntityNumber(ushort x):base(x){}
public v_EntityIdentifier_EntityNumber(NUShort t):base(t.value){}}
public class v_IsFrozen : NBool{
public v_IsFrozen(bool x):base(x){}
public v_IsFrozen(NBool t):base(t.value){}}
public class v_Orientation_Psi : NFloat{
public v_Orientation_Psi(float x):base(x){}
public v_Orientation_Psi(NFloat t):base(t.value){}}
public class v_Orientation_Theta : NFloat{
public v_Orientation_Theta(float x):base(x){}
public v_Orientation_Theta(NFloat t):base(t.value){}}
public class v_Orientation_Phi : NFloat{
public v_Orientation_Phi(float x):base(x){}
public v_Orientation_Phi(NFloat t):base(t.value){}}
public class v_WorldLocation_X : NDouble{
public v_WorldLocation_X(double x):base(x){}
public v_WorldLocation_X(NDouble t):base(t.value){}}
public class v_WorldLocation_Y : NDouble{
public v_WorldLocation_Y(double x):base(x){}
public v_WorldLocation_Y(NDouble t):base(t.value){}}
public class v_WorldLocation_Z : NDouble{
public v_WorldLocation_Z(double x):base(x){}
public v_WorldLocation_Z(NDouble t):base(t.value){}}
public class v_VelocityVector_XVelocity : NFloat{
public v_VelocityVector_XVelocity(float x):base(x){}
public v_VelocityVector_XVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_YVelocity : NFloat{
public v_VelocityVector_YVelocity(float x):base(x){}
public v_VelocityVector_YVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_ZVelocity : NFloat{
public v_VelocityVector_ZVelocity(float x):base(x){}
public v_VelocityVector_ZVelocity(NFloat t):base(t.value){}}
public class v_ForceIdentifier : NEnum{
public v_ForceIdentifier(string x):base(x){}
public v_ForceIdentifier(int v):base(v){}
public v_ForceIdentifier(string x, int v):base(x, v){}
public v_ForceIdentifier(NEnum t):base(t.enumerator, t.enumValue){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_LogicalTime = val => val.toUInt();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_XAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_YAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_ZAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,byte> t_EntityType_EntityKind = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Domain = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityType_CountryCode = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Category = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Subcategory = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Specific = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Extra = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_IsFrozen = val => val.toByte();
public static Func<nframework.nom.NValueType,float> t_Orientation_Psi = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Theta = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Phi = val => val.toFloat();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_XVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_YVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_ZVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,string> t_ForceIdentifier = val => val.toString();
}

}

namespace BaseEntity_PhysicalEntity_Munition_GUI
{
public class v_LogicalTime : NUInteger{
public v_LogicalTime(uint x):base(x){}
public v_LogicalTime(NUInteger t):base(t.value){}}
public class v_AccelerationVector_XAcceleration : NFloat{
public v_AccelerationVector_XAcceleration(float x):base(x){}
public v_AccelerationVector_XAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_YAcceleration : NFloat{
public v_AccelerationVector_YAcceleration(float x):base(x){}
public v_AccelerationVector_YAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_ZAcceleration : NFloat{
public v_AccelerationVector_ZAcceleration(float x):base(x){}
public v_AccelerationVector_ZAcceleration(NFloat t):base(t.value){}}
public class v_EntityType_EntityKind : NByte{
public v_EntityType_EntityKind(byte x):base(x){}
public v_EntityType_EntityKind(NByte t):base(t.value){}}
public class v_EntityType_Domain : NByte{
public v_EntityType_Domain(byte x):base(x){}
public v_EntityType_Domain(NByte t):base(t.value){}}
public class v_EntityType_CountryCode : NUShort{
public v_EntityType_CountryCode(ushort x):base(x){}
public v_EntityType_CountryCode(NUShort t):base(t.value){}}
public class v_EntityType_Category : NByte{
public v_EntityType_Category(byte x):base(x){}
public v_EntityType_Category(NByte t):base(t.value){}}
public class v_EntityType_Subcategory : NByte{
public v_EntityType_Subcategory(byte x):base(x){}
public v_EntityType_Subcategory(NByte t):base(t.value){}}
public class v_EntityType_Specific : NByte{
public v_EntityType_Specific(byte x):base(x){}
public v_EntityType_Specific(NByte t):base(t.value){}}
public class v_EntityType_Extra : NByte{
public v_EntityType_Extra(byte x):base(x){}
public v_EntityType_Extra(NByte t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_SiteID : NUShort{
public v_EntityIdentifier_FederateIdentifier_SiteID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_ApplicationID : NUShort{
public v_EntityIdentifier_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_EntityNumber : NUShort{
public v_EntityIdentifier_EntityNumber(ushort x):base(x){}
public v_EntityIdentifier_EntityNumber(NUShort t):base(t.value){}}
public class v_IsFrozen : NBool{
public v_IsFrozen(bool x):base(x){}
public v_IsFrozen(NBool t):base(t.value){}}
public class v_Orientation_Psi : NFloat{
public v_Orientation_Psi(float x):base(x){}
public v_Orientation_Psi(NFloat t):base(t.value){}}
public class v_Orientation_Theta : NFloat{
public v_Orientation_Theta(float x):base(x){}
public v_Orientation_Theta(NFloat t):base(t.value){}}
public class v_Orientation_Phi : NFloat{
public v_Orientation_Phi(float x):base(x){}
public v_Orientation_Phi(NFloat t):base(t.value){}}
public class v_WorldLocation_X : NDouble{
public v_WorldLocation_X(double x):base(x){}
public v_WorldLocation_X(NDouble t):base(t.value){}}
public class v_WorldLocation_Y : NDouble{
public v_WorldLocation_Y(double x):base(x){}
public v_WorldLocation_Y(NDouble t):base(t.value){}}
public class v_WorldLocation_Z : NDouble{
public v_WorldLocation_Z(double x):base(x){}
public v_WorldLocation_Z(NDouble t):base(t.value){}}
public class v_VelocityVector_XVelocity : NFloat{
public v_VelocityVector_XVelocity(float x):base(x){}
public v_VelocityVector_XVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_YVelocity : NFloat{
public v_VelocityVector_YVelocity(float x):base(x){}
public v_VelocityVector_YVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_ZVelocity : NFloat{
public v_VelocityVector_ZVelocity(float x):base(x){}
public v_VelocityVector_ZVelocity(NFloat t):base(t.value){}}
public class v_ForceIdentifier : NEnum{
public v_ForceIdentifier(string x):base(x){}
public v_ForceIdentifier(int v):base(v){}
public v_ForceIdentifier(string x, int v):base(x, v){}
public v_ForceIdentifier(NEnum t):base(t.enumerator, t.enumValue){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_LogicalTime = val => val.toUInt();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_XAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_YAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_ZAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,byte> t_EntityType_EntityKind = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Domain = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityType_CountryCode = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Category = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Subcategory = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Specific = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Extra = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_IsFrozen = val => val.toByte();
public static Func<nframework.nom.NValueType,float> t_Orientation_Psi = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Theta = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Phi = val => val.toFloat();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_XVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_YVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_ZVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,string> t_ForceIdentifier = val => val.toString();
}

}

namespace BaseEntity_PhysicalEntity_Sensor_GUI
{
public class v_LogicalTime : NUInteger{
public v_LogicalTime(uint x):base(x){}
public v_LogicalTime(NUInteger t):base(t.value){}}
public class v_AccelerationVector_XAcceleration : NFloat{
public v_AccelerationVector_XAcceleration(float x):base(x){}
public v_AccelerationVector_XAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_YAcceleration : NFloat{
public v_AccelerationVector_YAcceleration(float x):base(x){}
public v_AccelerationVector_YAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_ZAcceleration : NFloat{
public v_AccelerationVector_ZAcceleration(float x):base(x){}
public v_AccelerationVector_ZAcceleration(NFloat t):base(t.value){}}
public class v_EntityType_EntityKind : NByte{
public v_EntityType_EntityKind(byte x):base(x){}
public v_EntityType_EntityKind(NByte t):base(t.value){}}
public class v_EntityType_Domain : NByte{
public v_EntityType_Domain(byte x):base(x){}
public v_EntityType_Domain(NByte t):base(t.value){}}
public class v_EntityType_CountryCode : NUShort{
public v_EntityType_CountryCode(ushort x):base(x){}
public v_EntityType_CountryCode(NUShort t):base(t.value){}}
public class v_EntityType_Category : NByte{
public v_EntityType_Category(byte x):base(x){}
public v_EntityType_Category(NByte t):base(t.value){}}
public class v_EntityType_Subcategory : NByte{
public v_EntityType_Subcategory(byte x):base(x){}
public v_EntityType_Subcategory(NByte t):base(t.value){}}
public class v_EntityType_Specific : NByte{
public v_EntityType_Specific(byte x):base(x){}
public v_EntityType_Specific(NByte t):base(t.value){}}
public class v_EntityType_Extra : NByte{
public v_EntityType_Extra(byte x):base(x){}
public v_EntityType_Extra(NByte t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_SiteID : NUShort{
public v_EntityIdentifier_FederateIdentifier_SiteID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_ApplicationID : NUShort{
public v_EntityIdentifier_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_EntityNumber : NUShort{
public v_EntityIdentifier_EntityNumber(ushort x):base(x){}
public v_EntityIdentifier_EntityNumber(NUShort t):base(t.value){}}
public class v_IsFrozen : NBool{
public v_IsFrozen(bool x):base(x){}
public v_IsFrozen(NBool t):base(t.value){}}
public class v_Orientation_Psi : NFloat{
public v_Orientation_Psi(float x):base(x){}
public v_Orientation_Psi(NFloat t):base(t.value){}}
public class v_Orientation_Theta : NFloat{
public v_Orientation_Theta(float x):base(x){}
public v_Orientation_Theta(NFloat t):base(t.value){}}
public class v_Orientation_Phi : NFloat{
public v_Orientation_Phi(float x):base(x){}
public v_Orientation_Phi(NFloat t):base(t.value){}}
public class v_WorldLocation_X : NDouble{
public v_WorldLocation_X(double x):base(x){}
public v_WorldLocation_X(NDouble t):base(t.value){}}
public class v_WorldLocation_Y : NDouble{
public v_WorldLocation_Y(double x):base(x){}
public v_WorldLocation_Y(NDouble t):base(t.value){}}
public class v_WorldLocation_Z : NDouble{
public v_WorldLocation_Z(double x):base(x){}
public v_WorldLocation_Z(NDouble t):base(t.value){}}
public class v_VelocityVector_XVelocity : NFloat{
public v_VelocityVector_XVelocity(float x):base(x){}
public v_VelocityVector_XVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_YVelocity : NFloat{
public v_VelocityVector_YVelocity(float x):base(x){}
public v_VelocityVector_YVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_ZVelocity : NFloat{
public v_VelocityVector_ZVelocity(float x):base(x){}
public v_VelocityVector_ZVelocity(NFloat t):base(t.value){}}
public class v_ForceIdentifier : NEnum{
public v_ForceIdentifier(string x):base(x){}
public v_ForceIdentifier(int v):base(v){}
public v_ForceIdentifier(string x, int v):base(x, v){}
public v_ForceIdentifier(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_AntennaRaised : NBool{
public v_AntennaRaised(bool x):base(x){}
public v_AntennaRaised(NBool t):base(t.value){}}
public class v_BlackoutLightsOn : NBool{
public v_BlackoutLightsOn(bool x):base(x){}
public v_BlackoutLightsOn(NBool t):base(t.value){}}
public class v_LightsOn : NBool{
public v_LightsOn(bool x):base(x){}
public v_LightsOn(NBool t):base(t.value){}}
public class v_InteriorLightsOn : NBool{
public v_InteriorLightsOn(bool x):base(x){}
public v_InteriorLightsOn(NBool t):base(t.value){}}
public class v_MissionKill : NBool{
public v_MissionKill(bool x):base(x){}
public v_MissionKill(NBool t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_LogicalTime = val => val.toUInt();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_XAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_YAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_ZAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,byte> t_EntityType_EntityKind = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Domain = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityType_CountryCode = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Category = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Subcategory = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Specific = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Extra = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_IsFrozen = val => val.toByte();
public static Func<nframework.nom.NValueType,float> t_Orientation_Psi = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Theta = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Phi = val => val.toFloat();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_XVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_YVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_ZVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,string> t_ForceIdentifier = val => val.toString();
public static Func<nframework.nom.NValueType,byte> t_AntennaRaised = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_BlackoutLightsOn = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_LightsOn = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_InteriorLightsOn = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_MissionKill = val => val.toByte();
}

}

namespace BaseEntity_PhysicalEntity_Platform_GroundVehicle_GUI
{
public class v_LogicalTime : NUInteger{
public v_LogicalTime(uint x):base(x){}
public v_LogicalTime(NUInteger t):base(t.value){}}
public class v_AccelerationVector_XAcceleration : NFloat{
public v_AccelerationVector_XAcceleration(float x):base(x){}
public v_AccelerationVector_XAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_YAcceleration : NFloat{
public v_AccelerationVector_YAcceleration(float x):base(x){}
public v_AccelerationVector_YAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_ZAcceleration : NFloat{
public v_AccelerationVector_ZAcceleration(float x):base(x){}
public v_AccelerationVector_ZAcceleration(NFloat t):base(t.value){}}
public class v_EntityType_EntityKind : NByte{
public v_EntityType_EntityKind(byte x):base(x){}
public v_EntityType_EntityKind(NByte t):base(t.value){}}
public class v_EntityType_Domain : NByte{
public v_EntityType_Domain(byte x):base(x){}
public v_EntityType_Domain(NByte t):base(t.value){}}
public class v_EntityType_CountryCode : NUShort{
public v_EntityType_CountryCode(ushort x):base(x){}
public v_EntityType_CountryCode(NUShort t):base(t.value){}}
public class v_EntityType_Category : NByte{
public v_EntityType_Category(byte x):base(x){}
public v_EntityType_Category(NByte t):base(t.value){}}
public class v_EntityType_Subcategory : NByte{
public v_EntityType_Subcategory(byte x):base(x){}
public v_EntityType_Subcategory(NByte t):base(t.value){}}
public class v_EntityType_Specific : NByte{
public v_EntityType_Specific(byte x):base(x){}
public v_EntityType_Specific(NByte t):base(t.value){}}
public class v_EntityType_Extra : NByte{
public v_EntityType_Extra(byte x):base(x){}
public v_EntityType_Extra(NByte t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_SiteID : NUShort{
public v_EntityIdentifier_FederateIdentifier_SiteID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_ApplicationID : NUShort{
public v_EntityIdentifier_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_EntityNumber : NUShort{
public v_EntityIdentifier_EntityNumber(ushort x):base(x){}
public v_EntityIdentifier_EntityNumber(NUShort t):base(t.value){}}
public class v_IsFrozen : NBool{
public v_IsFrozen(bool x):base(x){}
public v_IsFrozen(NBool t):base(t.value){}}
public class v_Orientation_Psi : NFloat{
public v_Orientation_Psi(float x):base(x){}
public v_Orientation_Psi(NFloat t):base(t.value){}}
public class v_Orientation_Theta : NFloat{
public v_Orientation_Theta(float x):base(x){}
public v_Orientation_Theta(NFloat t):base(t.value){}}
public class v_Orientation_Phi : NFloat{
public v_Orientation_Phi(float x):base(x){}
public v_Orientation_Phi(NFloat t):base(t.value){}}
public class v_WorldLocation_X : NDouble{
public v_WorldLocation_X(double x):base(x){}
public v_WorldLocation_X(NDouble t):base(t.value){}}
public class v_WorldLocation_Y : NDouble{
public v_WorldLocation_Y(double x):base(x){}
public v_WorldLocation_Y(NDouble t):base(t.value){}}
public class v_WorldLocation_Z : NDouble{
public v_WorldLocation_Z(double x):base(x){}
public v_WorldLocation_Z(NDouble t):base(t.value){}}
public class v_VelocityVector_XVelocity : NFloat{
public v_VelocityVector_XVelocity(float x):base(x){}
public v_VelocityVector_XVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_YVelocity : NFloat{
public v_VelocityVector_YVelocity(float x):base(x){}
public v_VelocityVector_YVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_ZVelocity : NFloat{
public v_VelocityVector_ZVelocity(float x):base(x){}
public v_VelocityVector_ZVelocity(NFloat t):base(t.value){}}
public class v_ForceIdentifier : NEnum{
public v_ForceIdentifier(string x):base(x){}
public v_ForceIdentifier(int v):base(v){}
public v_ForceIdentifier(string x, int v):base(x, v){}
public v_ForceIdentifier(NEnum t):base(t.enumerator, t.enumValue){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_LogicalTime = val => val.toUInt();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_XAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_YAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_ZAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,byte> t_EntityType_EntityKind = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Domain = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityType_CountryCode = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Category = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Subcategory = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Specific = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Extra = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_IsFrozen = val => val.toByte();
public static Func<nframework.nom.NValueType,float> t_Orientation_Psi = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Theta = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Phi = val => val.toFloat();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_XVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_YVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_ZVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,string> t_ForceIdentifier = val => val.toString();
}

}

namespace BaseEntity_PhysicalEntity_Platform_SurfaceVessel_GUI
{
public class v_LogicalTime : NUInteger{
public v_LogicalTime(uint x):base(x){}
public v_LogicalTime(NUInteger t):base(t.value){}}
public class v_AccelerationVector_XAcceleration : NFloat{
public v_AccelerationVector_XAcceleration(float x):base(x){}
public v_AccelerationVector_XAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_YAcceleration : NFloat{
public v_AccelerationVector_YAcceleration(float x):base(x){}
public v_AccelerationVector_YAcceleration(NFloat t):base(t.value){}}
public class v_AccelerationVector_ZAcceleration : NFloat{
public v_AccelerationVector_ZAcceleration(float x):base(x){}
public v_AccelerationVector_ZAcceleration(NFloat t):base(t.value){}}
public class v_EntityType_EntityKind : NByte{
public v_EntityType_EntityKind(byte x):base(x){}
public v_EntityType_EntityKind(NByte t):base(t.value){}}
public class v_EntityType_Domain : NByte{
public v_EntityType_Domain(byte x):base(x){}
public v_EntityType_Domain(NByte t):base(t.value){}}
public class v_EntityType_CountryCode : NUShort{
public v_EntityType_CountryCode(ushort x):base(x){}
public v_EntityType_CountryCode(NUShort t):base(t.value){}}
public class v_EntityType_Category : NByte{
public v_EntityType_Category(byte x):base(x){}
public v_EntityType_Category(NByte t):base(t.value){}}
public class v_EntityType_Subcategory : NByte{
public v_EntityType_Subcategory(byte x):base(x){}
public v_EntityType_Subcategory(NByte t):base(t.value){}}
public class v_EntityType_Specific : NByte{
public v_EntityType_Specific(byte x):base(x){}
public v_EntityType_Specific(NByte t):base(t.value){}}
public class v_EntityType_Extra : NByte{
public v_EntityType_Extra(byte x):base(x){}
public v_EntityType_Extra(NByte t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_SiteID : NUShort{
public v_EntityIdentifier_FederateIdentifier_SiteID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_FederateIdentifier_ApplicationID : NUShort{
public v_EntityIdentifier_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_EntityIdentifier_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_EntityIdentifier_EntityNumber : NUShort{
public v_EntityIdentifier_EntityNumber(ushort x):base(x){}
public v_EntityIdentifier_EntityNumber(NUShort t):base(t.value){}}
public class v_IsFrozen : NBool{
public v_IsFrozen(bool x):base(x){}
public v_IsFrozen(NBool t):base(t.value){}}
public class v_Orientation_Psi : NFloat{
public v_Orientation_Psi(float x):base(x){}
public v_Orientation_Psi(NFloat t):base(t.value){}}
public class v_Orientation_Theta : NFloat{
public v_Orientation_Theta(float x):base(x){}
public v_Orientation_Theta(NFloat t):base(t.value){}}
public class v_Orientation_Phi : NFloat{
public v_Orientation_Phi(float x):base(x){}
public v_Orientation_Phi(NFloat t):base(t.value){}}
public class v_WorldLocation_X : NDouble{
public v_WorldLocation_X(double x):base(x){}
public v_WorldLocation_X(NDouble t):base(t.value){}}
public class v_WorldLocation_Y : NDouble{
public v_WorldLocation_Y(double x):base(x){}
public v_WorldLocation_Y(NDouble t):base(t.value){}}
public class v_WorldLocation_Z : NDouble{
public v_WorldLocation_Z(double x):base(x){}
public v_WorldLocation_Z(NDouble t):base(t.value){}}
public class v_VelocityVector_XVelocity : NFloat{
public v_VelocityVector_XVelocity(float x):base(x){}
public v_VelocityVector_XVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_YVelocity : NFloat{
public v_VelocityVector_YVelocity(float x):base(x){}
public v_VelocityVector_YVelocity(NFloat t):base(t.value){}}
public class v_VelocityVector_ZVelocity : NFloat{
public v_VelocityVector_ZVelocity(float x):base(x){}
public v_VelocityVector_ZVelocity(NFloat t):base(t.value){}}
public class v_ForceIdentifier : NEnum{
public v_ForceIdentifier(string x):base(x){}
public v_ForceIdentifier(int v):base(v){}
public v_ForceIdentifier(string x, int v):base(x, v){}
public v_ForceIdentifier(NEnum t):base(t.enumerator, t.enumValue){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_LogicalTime = val => val.toUInt();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_XAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_YAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_AccelerationVector_ZAcceleration = val => val.toFloat();
public static Func<nframework.nom.NValueType,byte> t_EntityType_EntityKind = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Domain = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityType_CountryCode = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Category = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Subcategory = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Specific = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_EntityType_Extra = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_EntityIdentifier_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_IsFrozen = val => val.toByte();
public static Func<nframework.nom.NValueType,float> t_Orientation_Psi = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Theta = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Orientation_Phi = val => val.toFloat();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_WorldLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_XVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_YVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_VelocityVector_ZVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,string> t_ForceIdentifier = val => val.toString();
}

}

namespace EventReport
{
public class v_OriginatingEntity_FederateIdentifier_SiteID : NUShort{
public v_OriginatingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_OriginatingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_EntityNumber : NUShort{
public v_OriginatingEntity_EntityNumber(ushort x):base(x){}
public v_OriginatingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_SiteID : NUShort{
public v_ReceivingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_ReceivingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_EntityNumber : NUShort{
public v_ReceivingEntity_EntityNumber(ushort x):base(x){}
public v_ReceivingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_EventType : NEnum{
public v_EventType(string x):base(x){}
public v_EventType(int v):base(v){}
public v_EventType(string x, int v):base(x, v){}
public v_EventType(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_VariableDatumSet_NumberOfVariableDatums : NUInteger{
public v_VariableDatumSet_NumberOfVariableDatums(uint x):base(x){}
public v_VariableDatumSet_NumberOfVariableDatums(NUInteger t):base(t.value){}}
public class v_VariableDatumSet_VariableDatums_DatumID : NEnum{
public v_VariableDatumSet_VariableDatums_DatumID(string x):base(x){}
public v_VariableDatumSet_VariableDatums_DatumID(int v):base(v){}
public v_VariableDatumSet_VariableDatums_DatumID(string x, int v):base(x, v){}
public v_VariableDatumSet_VariableDatums_DatumID(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_VariableDatumSet_VariableDatums_DatumLength : NUInteger{
public v_VariableDatumSet_VariableDatums_DatumLength(uint x):base(x){}
public v_VariableDatumSet_VariableDatums_DatumLength(NUInteger t):base(t.value){}}
public class v_VariableDatumSet_VariableDatums_DatumValue : NVariableDatum{
public v_VariableDatumSet_VariableDatums_DatumValue(byte[] x, uint y):base(x,y){}
public v_VariableDatumSet_VariableDatums_DatumValue(NVariableDatum t):base(t.value, t.bufLenWithoutOffset){}}
public class v_VariableDatumSet_VariableDatums_Padding : NByte{
public v_VariableDatumSet_VariableDatums_Padding(byte x):base(x){}
public v_VariableDatumSet_VariableDatums_Padding(NByte t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,string> t_EventType = val => val.toString();
public static Func<nframework.nom.NValueType,uint> t_VariableDatumSet_NumberOfVariableDatums = val => val.toUInt();
public static Func<nframework.nom.NValueType,string> t_VariableDatumSet_VariableDatums_DatumID = val => val.toString();
public static Func<nframework.nom.NValueType,uint> t_VariableDatumSet_VariableDatums_DatumLength = val => val.toUInt();
public static Func<nframework.nom.NValueType,byte> t_VariableDatumSet_VariableDatums_Padding = val => val.toByte();
}

}

namespace ActionRequest
{
public class v_OriginatingEntity_FederateIdentifier_SiteID : NUShort{
public v_OriginatingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_OriginatingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_EntityNumber : NUShort{
public v_OriginatingEntity_EntityNumber(ushort x):base(x){}
public v_OriginatingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_SiteID : NUShort{
public v_ReceivingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_ReceivingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_EntityNumber : NUShort{
public v_ReceivingEntity_EntityNumber(ushort x):base(x){}
public v_ReceivingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_RequestIdentifier : NUInteger{
public v_RequestIdentifier(uint x):base(x){}
public v_RequestIdentifier(NUInteger t):base(t.value){}}
public class v_ActionRequestCode : NEnum{
public v_ActionRequestCode(string x):base(x){}
public v_ActionRequestCode(int v):base(v){}
public v_ActionRequestCode(string x, int v):base(x, v){}
public v_ActionRequestCode(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_VariableDatumSet_NumberOfVariableDatums : NUInteger{
public v_VariableDatumSet_NumberOfVariableDatums(uint x):base(x){}
public v_VariableDatumSet_NumberOfVariableDatums(NUInteger t):base(t.value){}}
public class v_VariableDatumSet_VariableDatums_DatumID : NEnum{
public v_VariableDatumSet_VariableDatums_DatumID(string x):base(x){}
public v_VariableDatumSet_VariableDatums_DatumID(int v):base(v){}
public v_VariableDatumSet_VariableDatums_DatumID(string x, int v):base(x, v){}
public v_VariableDatumSet_VariableDatums_DatumID(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_VariableDatumSet_VariableDatums_DatumLength : NUInteger{
public v_VariableDatumSet_VariableDatums_DatumLength(uint x):base(x){}
public v_VariableDatumSet_VariableDatums_DatumLength(NUInteger t):base(t.value){}}
public class v_VariableDatumSet_VariableDatums_DatumValue : NVariableDatum{
public v_VariableDatumSet_VariableDatums_DatumValue(byte[] x, uint y):base(x,y){}
public v_VariableDatumSet_VariableDatums_DatumValue(NVariableDatum t):base(t.value, t.bufLenWithoutOffset){}}
public class v_VariableDatumSet_VariableDatums_Padding : NByte{
public v_VariableDatumSet_VariableDatums_Padding(byte x):base(x){}
public v_VariableDatumSet_VariableDatums_Padding(NByte t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,uint> t_RequestIdentifier = val => val.toUInt();
public static Func<nframework.nom.NValueType,string> t_ActionRequestCode = val => val.toString();
public static Func<nframework.nom.NValueType,uint> t_VariableDatumSet_NumberOfVariableDatums = val => val.toUInt();
public static Func<nframework.nom.NValueType,string> t_VariableDatumSet_VariableDatums_DatumID = val => val.toString();
public static Func<nframework.nom.NValueType,uint> t_VariableDatumSet_VariableDatums_DatumLength = val => val.toUInt();
public static Func<nframework.nom.NValueType,byte> t_VariableDatumSet_VariableDatums_Padding = val => val.toByte();
}

}

namespace ActionResponse
{
public class v_OriginatingEntity_FederateIdentifier_SiteID : NUShort{
public v_OriginatingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_OriginatingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_EntityNumber : NUShort{
public v_OriginatingEntity_EntityNumber(ushort x):base(x){}
public v_OriginatingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_SiteID : NUShort{
public v_ReceivingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_ReceivingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_EntityNumber : NUShort{
public v_ReceivingEntity_EntityNumber(ushort x):base(x){}
public v_ReceivingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_RequestIdentifier : NUInteger{
public v_RequestIdentifier(uint x):base(x){}
public v_RequestIdentifier(NUInteger t):base(t.value){}}
public class v_RequestStatus : NEnum{
public v_RequestStatus(string x):base(x){}
public v_RequestStatus(int v):base(v){}
public v_RequestStatus(string x, int v):base(x, v){}
public v_RequestStatus(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_VariableDatumSet_NumberOfVariableDatums : NUInteger{
public v_VariableDatumSet_NumberOfVariableDatums(uint x):base(x){}
public v_VariableDatumSet_NumberOfVariableDatums(NUInteger t):base(t.value){}}
public class v_VariableDatumSet_VariableDatums_DatumID : NEnum{
public v_VariableDatumSet_VariableDatums_DatumID(string x):base(x){}
public v_VariableDatumSet_VariableDatums_DatumID(int v):base(v){}
public v_VariableDatumSet_VariableDatums_DatumID(string x, int v):base(x, v){}
public v_VariableDatumSet_VariableDatums_DatumID(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_VariableDatumSet_VariableDatums_DatumLength : NUInteger{
public v_VariableDatumSet_VariableDatums_DatumLength(uint x):base(x){}
public v_VariableDatumSet_VariableDatums_DatumLength(NUInteger t):base(t.value){}}
public class v_VariableDatumSet_VariableDatums_DatumValue : NVariableDatum{
public v_VariableDatumSet_VariableDatums_DatumValue(byte[] x, uint y):base(x,y){}
public v_VariableDatumSet_VariableDatums_DatumValue(NVariableDatum t):base(t.value, t.bufLenWithoutOffset){}}
public class v_VariableDatumSet_VariableDatums_Padding : NByte{
public v_VariableDatumSet_VariableDatums_Padding(byte x):base(x){}
public v_VariableDatumSet_VariableDatums_Padding(NByte t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,uint> t_RequestIdentifier = val => val.toUInt();
public static Func<nframework.nom.NValueType,string> t_RequestStatus = val => val.toString();
public static Func<nframework.nom.NValueType,uint> t_VariableDatumSet_NumberOfVariableDatums = val => val.toUInt();
public static Func<nframework.nom.NValueType,string> t_VariableDatumSet_VariableDatums_DatumID = val => val.toString();
public static Func<nframework.nom.NValueType,uint> t_VariableDatumSet_VariableDatums_DatumLength = val => val.toUInt();
public static Func<nframework.nom.NValueType,byte> t_VariableDatumSet_VariableDatums_Padding = val => val.toByte();
}

}

namespace SetData
{
public class v_OriginatingEntity_FederateIdentifier_SiteID : NUShort{
public v_OriginatingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_OriginatingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_EntityNumber : NUShort{
public v_OriginatingEntity_EntityNumber(ushort x):base(x){}
public v_OriginatingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_SiteID : NUShort{
public v_ReceivingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_ReceivingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_EntityNumber : NUShort{
public v_ReceivingEntity_EntityNumber(ushort x):base(x){}
public v_ReceivingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_RequestIdentifier : NUInteger{
public v_RequestIdentifier(uint x):base(x){}
public v_RequestIdentifier(NUInteger t):base(t.value){}}
public class v_VariableDatumSet_NumberOfVariableDatums : NUInteger{
public v_VariableDatumSet_NumberOfVariableDatums(uint x):base(x){}
public v_VariableDatumSet_NumberOfVariableDatums(NUInteger t):base(t.value){}}
public class v_VariableDatumSet_VariableDatums_DatumID : NEnum{
public v_VariableDatumSet_VariableDatums_DatumID(string x):base(x){}
public v_VariableDatumSet_VariableDatums_DatumID(int v):base(v){}
public v_VariableDatumSet_VariableDatums_DatumID(string x, int v):base(x, v){}
public v_VariableDatumSet_VariableDatums_DatumID(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_VariableDatumSet_VariableDatums_DatumLength : NUInteger{
public v_VariableDatumSet_VariableDatums_DatumLength(uint x):base(x){}
public v_VariableDatumSet_VariableDatums_DatumLength(NUInteger t):base(t.value){}}
public class v_VariableDatumSet_VariableDatums_DatumValue : NVariableDatum{
public v_VariableDatumSet_VariableDatums_DatumValue(byte[] x, uint y):base(x,y){}
public v_VariableDatumSet_VariableDatums_DatumValue(NVariableDatum t):base(t.value, t.bufLenWithoutOffset){}}
public class v_VariableDatumSet_VariableDatums_Padding : NByte{
public v_VariableDatumSet_VariableDatums_Padding(byte x):base(x){}
public v_VariableDatumSet_VariableDatums_Padding(NByte t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,uint> t_RequestIdentifier = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_VariableDatumSet_NumberOfVariableDatums = val => val.toUInt();
public static Func<nframework.nom.NValueType,string> t_VariableDatumSet_VariableDatums_DatumID = val => val.toString();
public static Func<nframework.nom.NValueType,uint> t_VariableDatumSet_VariableDatums_DatumLength = val => val.toUInt();
public static Func<nframework.nom.NValueType,byte> t_VariableDatumSet_VariableDatums_Padding = val => val.toByte();
}

}

namespace Data
{
public class v_OriginatingEntity_FederateIdentifier_SiteID : NUShort{
public v_OriginatingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_OriginatingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_EntityNumber : NUShort{
public v_OriginatingEntity_EntityNumber(ushort x):base(x){}
public v_OriginatingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_SiteID : NUShort{
public v_ReceivingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_ReceivingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_EntityNumber : NUShort{
public v_ReceivingEntity_EntityNumber(ushort x):base(x){}
public v_ReceivingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_RequestIdentifier : NUInteger{
public v_RequestIdentifier(uint x):base(x){}
public v_RequestIdentifier(NUInteger t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,uint> t_RequestIdentifier = val => val.toUInt();
}

}

namespace StartResume
{
public class v_OriginatingEntity_FederateIdentifier_SiteID : NUShort{
public v_OriginatingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_OriginatingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_EntityNumber : NUShort{
public v_OriginatingEntity_EntityNumber(ushort x):base(x){}
public v_OriginatingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_SiteID : NUShort{
public v_ReceivingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_ReceivingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_EntityNumber : NUShort{
public v_ReceivingEntity_EntityNumber(ushort x):base(x){}
public v_ReceivingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_RequestIdentifier : NUInteger{
public v_RequestIdentifier(uint x):base(x){}
public v_RequestIdentifier(NUInteger t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,uint> t_RequestIdentifier = val => val.toUInt();
}

}

namespace StopFreeze
{
public class v_OriginatingEntity_FederateIdentifier_SiteID : NUShort{
public v_OriginatingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_OriginatingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_EntityNumber : NUShort{
public v_OriginatingEntity_EntityNumber(ushort x):base(x){}
public v_OriginatingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_SiteID : NUShort{
public v_ReceivingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_ReceivingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_EntityNumber : NUShort{
public v_ReceivingEntity_EntityNumber(ushort x):base(x){}
public v_ReceivingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_RequestIdentifier : NUInteger{
public v_RequestIdentifier(uint x):base(x){}
public v_RequestIdentifier(NUInteger t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,uint> t_RequestIdentifier = val => val.toUInt();
}

}

namespace Acknowledge
{
public class v_OriginatingEntity_FederateIdentifier_SiteID : NUShort{
public v_OriginatingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_OriginatingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_OriginatingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_OriginatingEntity_EntityNumber : NUShort{
public v_OriginatingEntity_EntityNumber(ushort x):base(x){}
public v_OriginatingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_SiteID : NUShort{
public v_ReceivingEntity_FederateIdentifier_SiteID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_SiteID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_FederateIdentifier_ApplicationID : NUShort{
public v_ReceivingEntity_FederateIdentifier_ApplicationID(ushort x):base(x){}
public v_ReceivingEntity_FederateIdentifier_ApplicationID(NUShort t):base(t.value){}}
public class v_ReceivingEntity_EntityNumber : NUShort{
public v_ReceivingEntity_EntityNumber(ushort x):base(x){}
public v_ReceivingEntity_EntityNumber(NUShort t):base(t.value){}}
public class v_RequestIdentifier : NUInteger{
public v_RequestIdentifier(uint x):base(x){}
public v_RequestIdentifier(NUInteger t):base(t.value){}}
public class v_AcknowledgeFlag : NEnum{
public v_AcknowledgeFlag(string x):base(x){}
public v_AcknowledgeFlag(int v):base(v){}
public v_AcknowledgeFlag(string x, int v):base(x, v){}
public v_AcknowledgeFlag(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_ResponseFlag : NEnum{
public v_ResponseFlag(string x):base(x){}
public v_ResponseFlag(int v):base(v){}
public v_ResponseFlag(string x, int v):base(x, v){}
public v_ResponseFlag(NEnum t):base(t.enumerator, t.enumValue){}}
public class T{
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_OriginatingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_SiteID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_FederateIdentifier_ApplicationID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_ReceivingEntity_EntityNumber = val => val.toUShort();
public static Func<nframework.nom.NValueType,uint> t_RequestIdentifier = val => val.toUInt();
public static Func<nframework.nom.NValueType,string> t_AcknowledgeFlag = val => val.toString();
public static Func<nframework.nom.NValueType,string> t_ResponseFlag = val => val.toString();
}

}

namespace WeaponFire
{
public class v_FireMissionIndex : NUInteger{
public v_FireMissionIndex(uint x):base(x){}
public v_FireMissionIndex(NUInteger t):base(t.value){}}
public class v_FiringLocation_X : NDouble{
public v_FiringLocation_X(double x):base(x){}
public v_FiringLocation_X(NDouble t):base(t.value){}}
public class v_FiringLocation_Y : NDouble{
public v_FiringLocation_Y(double x):base(x){}
public v_FiringLocation_Y(NDouble t):base(t.value){}}
public class v_FiringLocation_Z : NDouble{
public v_FiringLocation_Z(double x):base(x){}
public v_FiringLocation_Z(NDouble t):base(t.value){}}
public class v_FiringObjectIdentifier_ScenarioObjectID : NUShort{
public v_FiringObjectIdentifier_ScenarioObjectID(ushort x):base(x){}
public v_FiringObjectIdentifier_ScenarioObjectID(NUShort t):base(t.value){}}
public class v_FiringObjectIdentifier_SimulationObjectID : NUShort{
public v_FiringObjectIdentifier_SimulationObjectID(ushort x):base(x){}
public v_FiringObjectIdentifier_SimulationObjectID(NUShort t):base(t.value){}}
public class v_MunitionObjectIdentifier_ScenarioObjectID : NUShort{
public v_MunitionObjectIdentifier_ScenarioObjectID(ushort x):base(x){}
public v_MunitionObjectIdentifier_ScenarioObjectID(NUShort t):base(t.value){}}
public class v_MunitionObjectIdentifier_SimulationObjectID : NUShort{
public v_MunitionObjectIdentifier_SimulationObjectID(ushort x):base(x){}
public v_MunitionObjectIdentifier_SimulationObjectID(NUShort t):base(t.value){}}
public class v_MunitionType_EntityKind : NByte{
public v_MunitionType_EntityKind(byte x):base(x){}
public v_MunitionType_EntityKind(NByte t):base(t.value){}}
public class v_MunitionType_Domain : NByte{
public v_MunitionType_Domain(byte x):base(x){}
public v_MunitionType_Domain(NByte t):base(t.value){}}
public class v_MunitionType_CountryCode : NUShort{
public v_MunitionType_CountryCode(ushort x):base(x){}
public v_MunitionType_CountryCode(NUShort t):base(t.value){}}
public class v_MunitionType_Category : NByte{
public v_MunitionType_Category(byte x):base(x){}
public v_MunitionType_Category(NByte t):base(t.value){}}
public class v_MunitionType_Subcategory : NByte{
public v_MunitionType_Subcategory(byte x):base(x){}
public v_MunitionType_Subcategory(NByte t):base(t.value){}}
public class v_MunitionType_Specific : NByte{
public v_MunitionType_Specific(byte x):base(x){}
public v_MunitionType_Specific(NByte t):base(t.value){}}
public class v_MunitionType_Extra : NByte{
public v_MunitionType_Extra(byte x):base(x){}
public v_MunitionType_Extra(NByte t):base(t.value){}}
public class v_TargetObjectIdentifier_ScenarioObjectID : NUShort{
public v_TargetObjectIdentifier_ScenarioObjectID(ushort x):base(x){}
public v_TargetObjectIdentifier_ScenarioObjectID(NUShort t):base(t.value){}}
public class v_TargetObjectIdentifier_SimulationObjectID : NUShort{
public v_TargetObjectIdentifier_SimulationObjectID(ushort x):base(x){}
public v_TargetObjectIdentifier_SimulationObjectID(NUShort t):base(t.value){}}
public class v_VariableDatumSet_NumberOfVariableDatums : NUInteger{
public v_VariableDatumSet_NumberOfVariableDatums(uint x):base(x){}
public v_VariableDatumSet_NumberOfVariableDatums(NUInteger t):base(t.value){}}
public class v_VariableDatumSet_VariableDatums_DatumID : NEnum{
public v_VariableDatumSet_VariableDatums_DatumID(string x):base(x){}
public v_VariableDatumSet_VariableDatums_DatumID(int v):base(v){}
public v_VariableDatumSet_VariableDatums_DatumID(string x, int v):base(x, v){}
public v_VariableDatumSet_VariableDatums_DatumID(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_VariableDatumSet_VariableDatums_DatumLength : NUInteger{
public v_VariableDatumSet_VariableDatums_DatumLength(uint x):base(x){}
public v_VariableDatumSet_VariableDatums_DatumLength(NUInteger t):base(t.value){}}
public class v_VariableDatumSet_VariableDatums_DatumValue : NVariableDatum{
public v_VariableDatumSet_VariableDatums_DatumValue(byte[] x, uint y):base(x,y){}
public v_VariableDatumSet_VariableDatums_DatumValue(NVariableDatum t):base(t.value, t.bufLenWithoutOffset){}}
public class v_VariableDatumSet_VariableDatums_Padding : NByte{
public v_VariableDatumSet_VariableDatums_Padding(byte x):base(x){}
public v_VariableDatumSet_VariableDatums_Padding(NByte t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_FireMissionIndex = val => val.toUInt();
public static Func<nframework.nom.NValueType,double> t_FiringLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_FiringLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_FiringLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,ushort> t_FiringObjectIdentifier_ScenarioObjectID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_FiringObjectIdentifier_SimulationObjectID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_MunitionObjectIdentifier_ScenarioObjectID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_MunitionObjectIdentifier_SimulationObjectID = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_MunitionType_EntityKind = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_MunitionType_Domain = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_MunitionType_CountryCode = val => val.toUShort();
public static Func<nframework.nom.NValueType,byte> t_MunitionType_Category = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_MunitionType_Subcategory = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_MunitionType_Specific = val => val.toByte();
public static Func<nframework.nom.NValueType,byte> t_MunitionType_Extra = val => val.toByte();
public static Func<nframework.nom.NValueType,ushort> t_TargetObjectIdentifier_ScenarioObjectID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_TargetObjectIdentifier_SimulationObjectID = val => val.toUShort();
public static Func<nframework.nom.NValueType,uint> t_VariableDatumSet_NumberOfVariableDatums = val => val.toUInt();
public static Func<nframework.nom.NValueType,string> t_VariableDatumSet_VariableDatums_DatumID = val => val.toString();
public static Func<nframework.nom.NValueType,uint> t_VariableDatumSet_VariableDatums_DatumLength = val => val.toUInt();
public static Func<nframework.nom.NValueType,byte> t_VariableDatumSet_VariableDatums_Padding = val => val.toByte();
}

}

namespace Collision
{
public class v_CollidingObjectIdentifier_ScenarioObjectID : NUShort{
public v_CollidingObjectIdentifier_ScenarioObjectID(ushort x):base(x){}
public v_CollidingObjectIdentifier_ScenarioObjectID(NUShort t):base(t.value){}}
public class v_CollidingObjectIdentifier_SimulationObjectID : NUShort{
public v_CollidingObjectIdentifier_SimulationObjectID(ushort x):base(x){}
public v_CollidingObjectIdentifier_SimulationObjectID(NUShort t):base(t.value){}}
public class v_CollisionType : NEnum{
public v_CollisionType(string x):base(x){}
public v_CollisionType(int v):base(v){}
public v_CollisionType(string x, int v):base(x, v){}
public v_CollisionType(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_CollisionLocation_BodyXDistance : NFloat{
public v_CollisionLocation_BodyXDistance(float x):base(x){}
public v_CollisionLocation_BodyXDistance(NFloat t):base(t.value){}}
public class v_CollisionLocation_BodyYDistance : NFloat{
public v_CollisionLocation_BodyYDistance(float x):base(x){}
public v_CollisionLocation_BodyYDistance(NFloat t):base(t.value){}}
public class v_CollisionLocation_BodyZDistance : NFloat{
public v_CollisionLocation_BodyZDistance(float x):base(x){}
public v_CollisionLocation_BodyZDistance(NFloat t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,ushort> t_CollidingObjectIdentifier_ScenarioObjectID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_CollidingObjectIdentifier_SimulationObjectID = val => val.toUShort();
public static Func<nframework.nom.NValueType,string> t_CollisionType = val => val.toString();
public static Func<nframework.nom.NValueType,float> t_CollisionLocation_BodyXDistance = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_CollisionLocation_BodyYDistance = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_CollisionLocation_BodyZDistance = val => val.toFloat();
}

}

namespace MunitionDetonation
{
public class v_DetonationLocation_X : NDouble{
public v_DetonationLocation_X(double x):base(x){}
public v_DetonationLocation_X(NDouble t):base(t.value){}}
public class v_DetonationLocation_Y : NDouble{
public v_DetonationLocation_Y(double x):base(x){}
public v_DetonationLocation_Y(NDouble t):base(t.value){}}
public class v_DetonationLocation_Z : NDouble{
public v_DetonationLocation_Z(double x):base(x){}
public v_DetonationLocation_Z(NDouble t):base(t.value){}}
public class v_DetonationResultCode : NEnum{
public v_DetonationResultCode(string x):base(x){}
public v_DetonationResultCode(int v):base(v){}
public v_DetonationResultCode(string x, int v):base(x, v){}
public v_DetonationResultCode(NEnum t):base(t.enumerator, t.enumValue){}}
public class v_FinalVelocityVector_XVelocity : NFloat{
public v_FinalVelocityVector_XVelocity(float x):base(x){}
public v_FinalVelocityVector_XVelocity(NFloat t):base(t.value){}}
public class v_FinalVelocityVector_YVelocity : NFloat{
public v_FinalVelocityVector_YVelocity(float x):base(x){}
public v_FinalVelocityVector_YVelocity(NFloat t):base(t.value){}}
public class v_FinalVelocityVector_ZVelocity : NFloat{
public v_FinalVelocityVector_ZVelocity(float x):base(x){}
public v_FinalVelocityVector_ZVelocity(NFloat t):base(t.value){}}
public class v_MunitionObjectIdentifier_ScenarioObjectID : NUShort{
public v_MunitionObjectIdentifier_ScenarioObjectID(ushort x):base(x){}
public v_MunitionObjectIdentifier_ScenarioObjectID(NUShort t):base(t.value){}}
public class v_MunitionObjectIdentifier_SimulationObjectID : NUShort{
public v_MunitionObjectIdentifier_SimulationObjectID(ushort x):base(x){}
public v_MunitionObjectIdentifier_SimulationObjectID(NUShort t):base(t.value){}}
public class v_RelativeDetonationLocation_BodyXDistance : NFloat{
public v_RelativeDetonationLocation_BodyXDistance(float x):base(x){}
public v_RelativeDetonationLocation_BodyXDistance(NFloat t):base(t.value){}}
public class v_RelativeDetonationLocation_BodyYDistance : NFloat{
public v_RelativeDetonationLocation_BodyYDistance(float x):base(x){}
public v_RelativeDetonationLocation_BodyYDistance(NFloat t):base(t.value){}}
public class v_RelativeDetonationLocation_BodyZDistance : NFloat{
public v_RelativeDetonationLocation_BodyZDistance(float x):base(x){}
public v_RelativeDetonationLocation_BodyZDistance(NFloat t):base(t.value){}}
public class v_TargetObjectIdentifier_ScenarioObjectID : NUShort{
public v_TargetObjectIdentifier_ScenarioObjectID(ushort x):base(x){}
public v_TargetObjectIdentifier_ScenarioObjectID(NUShort t):base(t.value){}}
public class v_TargetObjectIdentifier_SimulationObjectID : NUShort{
public v_TargetObjectIdentifier_SimulationObjectID(ushort x):base(x){}
public v_TargetObjectIdentifier_SimulationObjectID(NUShort t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,double> t_DetonationLocation_X = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_DetonationLocation_Y = val => val.toDouble();
public static Func<nframework.nom.NValueType,double> t_DetonationLocation_Z = val => val.toDouble();
public static Func<nframework.nom.NValueType,string> t_DetonationResultCode = val => val.toString();
public static Func<nframework.nom.NValueType,float> t_FinalVelocityVector_XVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_FinalVelocityVector_YVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_FinalVelocityVector_ZVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,ushort> t_MunitionObjectIdentifier_ScenarioObjectID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_MunitionObjectIdentifier_SimulationObjectID = val => val.toUShort();
public static Func<nframework.nom.NValueType,float> t_RelativeDetonationLocation_BodyXDistance = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_RelativeDetonationLocation_BodyYDistance = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_RelativeDetonationLocation_BodyZDistance = val => val.toFloat();
public static Func<nframework.nom.NValueType,ushort> t_TargetObjectIdentifier_ScenarioObjectID = val => val.toUShort();
public static Func<nframework.nom.NValueType,ushort> t_TargetObjectIdentifier_SimulationObjectID = val => val.toUShort();
}

}

}
