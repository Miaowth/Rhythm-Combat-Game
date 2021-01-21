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

//for storing information about an ability
USTRUCT(BlueprintType)
struct FAbilityStats {
	GENERATED_BODY()
		int32 Power;
	int32 MagicPointsCost;
	FString AbilityName;
	FString Description;
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

