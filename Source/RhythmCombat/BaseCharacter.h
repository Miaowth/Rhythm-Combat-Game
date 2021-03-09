// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Structs.h"
#include "ItemsAndInventory/Inventory.h"

#include "BaseCharacter.generated.h"

UCLASS()
class RHYTHMCOMBAT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	UNavigationSystemV1* navSys;

	//void FoundNavPath(uint32 id,ENavigationQueryResult::Type Result, FNavPathSharedPtr Path);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UInventory* Inventory;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool InteractWith(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void LookAtActor(AActor* Actor);

	
};
