// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats {
	GENERATED_BODY()
	public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HealthPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagicPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagAttackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefensePower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagDefensePower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Evasiveness;
};

UENUM(BlueprintType)
enum ENoteType {
	Breve,
	SemiBreve,
	Minim,
	Crotchet,
	Quaver,
	SemiQuaver
};


USTRUCT(BlueprintType)
struct FMyNote {
	GENERATED_BODY()
	int32 ButtonIndex;
	int32 NotePosInBar;
	ENoteType TypeOfNote;
};

UENUM(BlueprintType)
enum ETargetType {
	Ally,
	Enemy,
	Self
};

UENUM(BlueprintType)
enum EButtonPressed {
	None,
	Left,
	Top,
	Right,
	Bottom
};

//for storing information about an ability
USTRUCT(BlueprintType)
struct FAbilityStats {
	GENERATED_BODY()
	int32 Power;
	int32 MagicPointsCost;
	FString AbilityName;
	FString Description;
	TArray<FMyNote> NotePattern;
	int32 Range;
	ETargetType TargetGroup;
};

USTRUCT(BlueprintType)
struct FItem {
	//TODO - finish
	GENERATED_BODY()
	int32 QuantityHeld;
	FString ItemName;
	FString Description;
	int32 Range;
	ETargetType TargetGroup;
};

UENUM(BlueprintType)
enum EActionType {
	BasicAttack,
	BasicDefend,
	UseItem,
	UseAbility
};

USTRUCT(BlueprintType, Blueprintable)
struct FAction {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EActionType> Type;
	UPROPERTY(BlueprintReadWrite)
	int32 index;
};

//stores basic information about an enemy for generation
USTRUCT(BlueprintType)
struct FEnemyGenerationStats {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemyLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> EnemyClass;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FCharacterStats CharacterStats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMesh* CharacterMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAbilityStats> Abilities;
};

