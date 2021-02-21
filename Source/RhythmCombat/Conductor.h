// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Conductor.generated.h"

UCLASS()
class RHYTHMCOMBAT_API AConductor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConductor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 crotchetsperbar = 4;
	float bpm = 60;
	float crotchet;
	float songposition;
	float deltasongpos;
	float lasthit; 

	float offset = 0.2f; //this may only be needed when using mp3 not wav
	float addoffset;
	float offsetstatic;
	bool hasoffsetadjusted = false;
	int32 beatnumber = 0;
	int32 barnumber = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
