// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RhythmCombatCharacter.h"
#include "BaseItemClass.h"
#include "CombatManager.h"
#include "BaseCharacter.h"
#include "Components/SphereComponent.h"


#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API APlayerCharacter : public ARhythmCombatCharacter
{
	GENERATED_BODY()
	APlayerCharacter();
private:

	USphereComponent* SphereComponent;

	AActor* BestInteractable;
	
public:
	//stores party inventory
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<UBaseItemClass*> Inventory;

	AActor* FindInteractActors();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ABaseCharacter*> OtherPartyMembers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 XPForNextLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CharacterIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform PosInWorld;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	int32 Activemoveindex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EButtonPressed> LastPressedButton = None;
public:

	UFUNCTION(BlueprintCallable)
		void UpdateTargetType(int32 moveindex, ABaseCharacter* Targetter);
	
	UFUNCTION(BlueprintCallable)
		void UpdateActiveActions(FAction NewAction, EButtonPressed ButtonToAssign, ABaseCharacter* CharacterToUpdate);

	
	
	virtual void NavigateUp() override;
	virtual void NavigateDown() override;
	virtual void BattleAction1() override;
	virtual void BattleAction2() override;
	virtual void BattleAction3() override;
	virtual void BattleAction4() override;

	
protected:
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
};
