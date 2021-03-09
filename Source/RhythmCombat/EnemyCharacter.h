// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



#include "BaseCharacter.h"
#include "Structs.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		TArray<FItemAmt> Items;
	//UPROPERTY(EditAnywhere,BlueprintReadOnly)
		//TMap<FItemAmt,float> PossibleDrops;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		int32 XPPerLevel;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		int32 MoneyPerLevel;
};