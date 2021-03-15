// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs.h"
#include "Conductor.generated.h"

UCLASS()
class RHYTHMCOMBAT_API AConductor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConductor();

	//May not need

	float bpm = 60;
	float crotchet;
	float songposition;
	float deltasongpos;
	float lasthit; 

	float offset = 0.2f; //this may only be needed when using mp3 not wav
	float addoffset;
	float offsetstatic;
	bool hasoffsetadjusted = false;
	int32 barnumber = 0;
	//End May not need

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

	UFUNCTION(BlueprintCallable)
		float ConvertBeatMapToMS(FMyNote Note, float CurrentBarStart);

	UFUNCTION(BlueprintNativeEvent)
		void BeginCombat();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
