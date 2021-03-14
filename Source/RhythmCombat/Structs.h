// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Structs.generated.h"

class ABaseCharacter;
class UBaseItemClass;
USTRUCT(BlueprintType)
struct FCharacterStats {
	GENERATED_BODY()
	public:
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
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ButtonIndex;
	//Note Position should start count at 1 to avoid musical confusion
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NotePosInBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BarNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ENoteType> TypeOfNote;
};

//USTRUCT(BlueprintType)
//struct FPatternNote {
//	GENERATED_BODY()
//	FMyNote BaseNoteInfo;
//	bool IsFinal;
//	ABaseCharacter* OwningChar;
//};

USTRUCT(BlueprintType)
struct FPatternNote {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFinal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABaseCharacter* OwningChar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PosInMs;
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
USTRUCT(BlueprintType, Blueprintable)
struct FAbilityStats : public FTableRowBase {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Power;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagicPointsCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AbilityName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMyNote> NotePattern;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETargetType> TargetGroup;
};

USTRUCT(BlueprintType)
struct FItemAmt {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UBaseItemClass> Item;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Quantity;
};

UENUM(BlueprintType)
enum EActionType {
	BasicAttack,
	BasicDefend,
	UseItem,
	UseAbility
};

USTRUCT(BlueprintType, Blueprintable)
struct FAction : public FTableRowBase {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EActionType> Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMesh* CharacterMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAbilityStats> Abilities;
};

