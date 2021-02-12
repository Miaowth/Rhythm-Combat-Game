// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PlayerCharacter.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		APlayerCharacter* PlayerCharacter;

private:
	//Setting up the camera possession
	UFUNCTION(BlueprintCallable)
	virtual void OnPossess(APawn* InPawn) override;
};
