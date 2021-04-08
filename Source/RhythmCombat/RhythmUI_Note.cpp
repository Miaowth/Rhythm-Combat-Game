// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmUI_Note.h"

// Sets default values
ARhythmUI_Note::ARhythmUI_Note()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//This is how to give an actor a root component.
	MyRootComponent->SetupAttachment(RootComponent);

	NoteSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Note Sprite"));
	NoteSprite->SetupAttachment(MyRootComponent);
}

// Called when the game starts or when spawned
void ARhythmUI_Note::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARhythmUI_Note::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset({ bpm * DeltaTime * -1,0.0f,0.0f });
}

