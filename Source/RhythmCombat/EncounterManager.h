// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Encounter.h"
#include "CombatManager.h"
#include "EncounterManager.generated.h"



UCLASS()
class RHYTHMCOMBAT_API AEncounterManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEncounterManager();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 LevelMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 LevelMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EncounterMaxQuantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EncounterMinQuantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EncounterMaxEnemies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AEncounter*> EncounterArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<class AActor>> PossibleEnemyClasses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> SpawnPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ACombatManager* CombatManagerRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* MyRootComponent;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEncounter> BP_Encounter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* RoamAreaBoxComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DisableEncounters(AActor* StartedEncounter);

	UFUNCTION(BlueprintCallable)
	void EnableEncounters();

	UFUNCTION(BlueprintCallable)
	bool IsInRoamableRange(FVector Point);

	UFUNCTION()
	void RemoveAllEncounters();

	UFUNCTION()
	void Enable();

	UFUNCTION()
	void Disable();

	UFUNCTION()
        void SpawnNewEncounters(int32 MaxQuantity);
	
private:
	UFUNCTION()
		ATargetPoint* GetNextSpawnpoint();
	
};
