// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RhythmUI_Note.h"
#include "CombatManager.h"

#include "RhythmUI_Manager.generated.h"

UCLASS()
class RHYTHMCOMBAT_API ARhythmUI_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARhythmUI_Manager();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* MyRootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ARhythmUI_Note*> TopTrackNoteArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ARhythmUI_Note*> BottomTrackNoteArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SpawnedIndexButton1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SpawnedIndexButton2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SpawnedIndexButton3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SpawnedIndexButton4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ACombatManager* CombatManagerRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
