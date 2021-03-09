// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ItemsAndInventory/Inventory.h"

#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UInventory* PlayerInventory;
	
	virtual void Init() override;
};
