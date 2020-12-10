// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RhythmCombatCharacter.h"
#include "BaseItemClass.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API APlayerCharacter : public ARhythmCombatCharacter
{
	GENERATED_BODY()
public:
	//stores party inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UBaseItemClass*> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ARhythmCombatCharacter*> OtherPartyMembers;
};
