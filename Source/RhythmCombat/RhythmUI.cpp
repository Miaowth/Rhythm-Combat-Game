// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmUI.h"

// Sets default values
ARhythmUI::ARhythmUI()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//This is how to give an actor a root component.
	MyRootComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARhythmUI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARhythmUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

