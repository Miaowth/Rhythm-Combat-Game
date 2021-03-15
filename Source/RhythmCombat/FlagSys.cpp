// Fill out your copyright notice in the Description page of Project Settings.


#include "FlagSys.h"

/*
 *
 *BOOL FLAGS
 *
 */

bool UFlagSys::GetFlagAsBool(FString FlagName) const
{
	return BoolFlags.FindRef(FlagName);
}

void UFlagSys::SetFlagAsBool(FString FlagName, bool NewValue)
{
	BoolFlags.FindOrAdd(FlagName,NewValue);
	OnAnyFlagChanged.Broadcast(FlagName, FlagType_Bool);
	OnBoolFlagChanged.Broadcast(FlagName, NewValue);
}

/*
 *
 *INT FLAGS
 *
 */

int32 UFlagSys::GetFlagAsInt(FString FlagName) const
{
	return IntFlags.FindRef(FlagName);
}

void UFlagSys::SetFlagAsInt(FString FlagName, int32 NewValue)
{
	IntFlags.FindOrAdd(FlagName,NewValue);
	OnAnyFlagChanged.Broadcast(FlagName, FlagType_Int);
	OnIntFlagChanged.Broadcast(FlagName, NewValue);
}

void UFlagSys::IncrementFlagAsInt(FString FlagName, int32 Change)
{
	int32 NewValue = Change + GetFlagAsInt(FlagName);
	SetFlagAsInt(FlagName, NewValue);
}

/*
 *
 *FLOAT FLAGS
 *
 */

float UFlagSys::GetFlagAsFloat(FString FlagName) const
{
	return FloatFlags.FindRef(FlagName);
}

void UFlagSys::SetFlagAsFloat(FString FlagName, float NewValue)
{
	FloatFlags.FindOrAdd(FlagName,NewValue);
	OnAnyFlagChanged.Broadcast(FlagName, FlagType_Float);
	OnFloatFlagChanged.Broadcast(FlagName, NewValue);
}

void UFlagSys::IncrementFlagAsFloat(FString FlagName, float Change)
{
	float NewValue = Change + GetFlagAsFloat(FlagName);
	SetFlagAsFloat(FlagName, NewValue);
}


/*
 *
 *STRING FLAGS
 *
 */

FString UFlagSys::GetFlagAsString(FString FlagName) const
{
	return StringFlags.FindRef(FlagName);
}

void UFlagSys::SetFlagAsString(FString FlagName, FString NewValue)
{
	StringFlags.FindOrAdd(FlagName,NewValue);
	OnAnyFlagChanged.Broadcast(FlagName, FlagType_String);
	OnStringFlagChanged.Broadcast(FlagName, NewValue);
}
