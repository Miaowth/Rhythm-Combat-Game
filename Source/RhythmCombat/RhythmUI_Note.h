// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"

#include "RhythmUI_Note.generated.h"

UCLASS()
class RHYTHMCOMBAT_API ARhythmUI_Note : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARhythmUI_Note();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* MyRootComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperSpriteComponent* NoteSprite;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float bpm;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
