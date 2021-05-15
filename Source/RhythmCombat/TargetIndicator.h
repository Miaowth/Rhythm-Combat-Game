// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetIndicator.generated.h"

UCLASS()
class RHYTHMCOMBAT_API ATargetIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetIndicator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* MyRootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* LampMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsLit = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void MovePosition(FTransform TargetPosition);

	UFUNCTION(BlueprintCallable)
		void ToggleLight();
};
