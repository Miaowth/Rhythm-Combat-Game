// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmUI_Track.h"

// Sets default values
ARhythmUI_Track::ARhythmUI_Track()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//This is how to give an actor a root component.
	MyRootComponent->SetupAttachment(RootComponent);

	TrackSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Track Sprite"));
	TrackSprite->SetupAttachment(MyRootComponent);
}

// Called when the game starts or when spawned
void ARhythmUI_Track::BeginPlay()
{
	Super::BeginPlay();
	//FBeginCombatDelegateDeclaration.Bind();
	//FEndCombatDelegateDeclaration.Bind();
}

// Called every frame
void ARhythmUI_Track::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

