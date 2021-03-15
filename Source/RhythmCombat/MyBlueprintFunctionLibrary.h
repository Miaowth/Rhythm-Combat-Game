// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FlagSys.h"
#include "ItemsAndInventory/Inventory.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure,Category="Flags")
	static UFlagSys* GetGlobalFlagSystem(UWorld* ThisWorld);

	UFUNCTION(BlueprintPure,Category="Inventory")
	static UInventory* GetPlayerInventory(UWorld* ThisWorld);

	UFUNCTION(BlueprintPure, Category="StringFormat")
	static FString ZeroBuffer(float Number, int Numbers, int DecimalPlaces);

	UFUNCTION(BlueprintPure, Category="StringFormat")
	static FString FormatTimeAsMMSS(float Number, int DecimalPlaces);
};
