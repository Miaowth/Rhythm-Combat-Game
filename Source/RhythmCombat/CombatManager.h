// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatManager.generated.h"

UCLASS()
class RHYTHMCOMBAT_API ACombatManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombatManager();

	//player party reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* PlayerParty;
	//enemy party reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* EnemyParty;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
