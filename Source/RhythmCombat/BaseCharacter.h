// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Structs.h"
#include "BaseCharacter.generated.h"

UCLASS()
class RHYTHMCOMBAT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FCharacterStats CharacterStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAbilityStats> Abilities;

	//this should never have more than 4 elements
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAction> ActiveActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAction ChosenAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ABaseCharacter*> TargetList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FItem> Inventory;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
