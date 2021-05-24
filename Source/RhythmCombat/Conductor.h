// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "AKComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
//#include "AKGameplayStatics.h"

#include "Structs.h"
#include "Conductor.generated.h"

class ARhythmUI_Manager;

UCLASS()
class RHYTHMCOMBAT_API AConductor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConductor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float bpm = 60.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LastBarStartPos = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BarDuration = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NextBarStartPos = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BeatLength = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PatternBarStart = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BeatNum = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BeatsPerBar = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* MyRootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAkComponent* CombatMusicAk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CombatPlayingID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ARhythmUI_Manager* RhythmUIManagerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool WaitingForNextBar = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BarsShownInAdvance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<BattlePhase> CurrentPhase;

	UFUNCTION(BlueprintCallable)
	void UpdateRhythmUI(float DeltaTime);

	UFUNCTION(BlueprintCallable)
		float ConvertBeatMapToMS(FMyNote Note, float CurrentBarStart);

	UFUNCTION(BlueprintNativeEvent)
		void BeginCombat();

	UFUNCTION(BlueprintNativeEvent)
		void EndCombat();

	UFUNCTION(BlueprintNativeEvent)
		void UpdatePhaseUI();

	UFUNCTION(BlueprintCallable)
		void RemoveUI(bool IsTopTrack);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
