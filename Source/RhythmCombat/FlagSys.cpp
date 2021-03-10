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
}

void UFlagSys::IncrementFlagAsInt(FString FlagName, int32 Change)
{
	SetFlagAsInt(FlagName,Change + GetFlagAsInt(FlagName));
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
}

void UFlagSys::IncrementFlagAsFloat(FString FlagName, float Change)
{
	SetFlagAsFloat(FlagName,Change + GetFlagAsFloat(FlagName));
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
}
