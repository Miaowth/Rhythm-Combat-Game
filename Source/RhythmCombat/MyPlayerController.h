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

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, Category=Camera)
	float BaseTurnRate = 45.f;

	/** Turn rate for left stick navigation. */
	UPROPERTY(VisibleAnywhere, Category=Camera)
	float AutoTurnRate = 22.5f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, Category=Camera)
	float BaseLookUpRate = 45.f;

	virtual void Tick(float DeltaSeconds) override;
	
	//Setting up the camera possession
	UFUNCTION(BlueprintCallable)
	virtual void OnPossess(APawn* InPawn) override;

//INPUT STUFF

	virtual void SetupInputComponent() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	* Called via input to turn at a given rate. 
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate. 
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	/**
	 *Does Jump
	 *
	 */
	void DoJump();

	/**
	 *Stops Jump
	 *
	 */
	void StopJump();

	
	void DoInteract();

	void ResetCamera();

	virtual void BattleAction1();
	virtual void BattleAction2();
	virtual void BattleAction3();
	virtual void BattleAction4();
	virtual void NavigateUp();
	virtual void NavigateDown();

private:
	bool ResettingCamera = false;
	FRotator CharacterRotation;

	FVector2D MoveDir;
	
};


