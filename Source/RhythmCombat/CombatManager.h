// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCharacter.h"
//#include "PlayerCharacter.h"
#include "CombatManager.generated.h"

class APlayerCharacter;

UCLASS()
class RHYTHMCOMBAT_API ACombatManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACombatManager();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* MyRootComponent;
	//player party reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerCharacter* PlayerCharacter;
	//enemy party reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ABaseCharacter*> EnemyParty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ABaseCharacter*> BattleOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool InCombat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool InRhythm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABaseCharacter* SelectedTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<ETargetType> TargetCategory;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ChangeETargetType(ETargetType NewType, ABaseCharacter* Targetter);

	UFUNCTION(BlueprintCallable)
	void GenerateEnemyActions();

	UFUNCTION(BlueprintCallable)
	void InitialiseCombat();

	UFUNCTION(BlueprintCallable)
	void CreateTurnOrder();

	UFUNCTION(BlueprintCallable)
	void BasicAttack(ABaseCharacter* AttackingActor, ABaseCharacter* DefendingActor);

	UFUNCTION(BlueprintCallable)
	bool Escape(ABaseCharacter* EscapingCharacter, TArray<AActor*> Party);
	
	UFUNCTION(BlueprintCallable)
	bool GetChance(int32 min, int32 max, int32 boundary);
	//UFUNCTION(BlueprintCallable)
	//	void UseItem(AActor)
	UFUNCTION(BlueprintCallable)
		void MergeSortTurnOrder(TArray<ABaseCharacter*> arr, int32 l, int32 r);
	UFUNCTION()
		void Merge(TArray<ABaseCharacter*> arr, int32 l, int32 m, int32 r);
};
