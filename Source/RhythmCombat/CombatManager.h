// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCharacter.h"
#include "Conductor.h"
#include "TargetIndicator.h"

//#include "PlayerCharacter.h"
#include "CombatManager.generated.h"
class AEncounterManager;
class APlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginCombatDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndCombatDelegate);


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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AConductor* ConductorRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AEncounterManager* EncounterManagerRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ATargetIndicator* TargetLamp;

	//arrays for rhythm section
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPatternNote> Button1Array;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPatternNote> Button2Array;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPatternNote> Button3Array;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPatternNote> Button4Array;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<TEnumAsByte<EHitQuality>, float> HitBoundaries;

	UPROPERTY(BlueprintAssignable)
		FBeginCombatDelegate FBeginCombatDelegateDeclaration;

	UPROPERTY(BlueprintAssignable)
		FEndCombatDelegate FEndCombatDelegateDeclaration;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void RemoveInvalidNotes(UPARAM(ref) TArray<FPatternNote> &ArrayToClean, bool IsTopTrack);

	UFUNCTION(BlueprintCallable)
	void ChangeETargetType(ETargetType NewType, ABaseCharacter* Targetter);

	UFUNCTION(BlueprintCallable)
	void GenerateEnemyActions();

	UFUNCTION(BlueprintCallable)
	void InitialiseCombat();

	UFUNCTION(BlueprintCallable)
	void CreateTurnOrder();

	UFUNCTION(BlueprintCallable)
	void RhythmSectionCompleteCheck();

	UFUNCTION(BlueprintCallable)
	bool Escape(ABaseCharacter* EscapingCharacter, TArray<AActor*> Party);
	
	UFUNCTION(BlueprintCallable)
	float PatternAccuracyScore(ABaseCharacter* ActiveCharacter);
	
	UFUNCTION(BlueprintCallable)
	void EnterRhythmPhase();

	UFUNCTION(BlueprintCallable)
		bool IsBelowBoundary(int32 CurrentPos, int32 Boundary);

	UFUNCTION(BlueprintCallable)
		bool IsAboveBoundary(int32 CurrentPos, int32 Boundary);

	UFUNCTION(BlueprintCallable)
	bool GetChance(int32 min, int32 max, int32 boundary);
	//UFUNCTION(BlueprintCallable)
	//	void UseItem(AActor)
};
