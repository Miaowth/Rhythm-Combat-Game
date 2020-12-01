// Copyright Epic Games, Inc. All Rights Reserved.

#include "RhythmCombatGameMode.h"
#include "RhythmCombatCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARhythmCombatGameMode::ARhythmCombatGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
