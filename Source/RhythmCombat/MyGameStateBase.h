// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EncounterManager.h"
#include "FlagSys.h"
#include "MyGameInstance.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UMyGameInstance* GameInstance;
	UPROPERTY()
	AEncounterManager* CurrentEncounterManager;

	virtual void BeginPlay() override;
public:
	UPROPERTY(BlueprintReadOnly)
		UInventory* PlayerInventory;

	UPROPERTY(BlueprintReadOnly)
		UFlagSys* FlagSystem;
	
	UFUNCTION(BlueprintCallable)
		void ChangeEncounterManager(AEncounterManager* NewManager);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE AEncounterManager* GetCurrentEncounterManager() const{return CurrentEncounterManager;};
	
};
