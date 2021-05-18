// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackProjectile.generated.h"

UCLASS()
class RHYTHMCOMBAT_API AAttackProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttackProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* MyRootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ProjectileBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform StartingPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform DestinationPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BeatDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
		void CalculateSpeed();

};
