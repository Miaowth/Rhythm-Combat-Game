// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCharacter.h"
#include "CombatManager.generated.h"

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
		ABaseCharacter* PlayerCharacter;
	//enemy party reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ABaseCharacter*> EnemyParty;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	bool CombatLoop();

	UFUNCTION(BlueprintCallable)
	void BasicAttack(ABaseCharacter* AttackingActor, ABaseCharacter* DefendingActor);

	UFUNCTION(BlueprintCallable)
		bool Escape(ABaseCharacter* EscapingCharacter, TArray<AActor*> Party);
	
	UFUNCTION(BlueprintCallable)
		bool GetChance(int32 min, int32 max, int32 boundary);
	//UFUNCTION(BlueprintCallable)
	//	void UseItem(AActor)
};
