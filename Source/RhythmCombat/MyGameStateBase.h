// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EncounterManager.h"
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
	AEncounterManager* CurrentEncounterManager;

	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable)
	void ChangeEncounterManager(AEncounterManager* NewManager);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AEncounterManager* GetCurrentEncounterManager() const{return CurrentEncounterManager;};
	
};