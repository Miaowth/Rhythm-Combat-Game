// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Structs.h"
#include "Encounter.generated.h"

class AEncounterManager;

UCLASS()
class RHYTHMCOMBAT_API AEncounter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEncounter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* MyRootComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AEncounterManager* EncounterManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* EncounterMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CanMove = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FEnemyGenerationStats> EnemyStats;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
