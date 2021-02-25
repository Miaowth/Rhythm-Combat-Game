// Fill out your copyright notice in the Description page of Project Settings.


#include "Encounter.h"

#include "../../../UE_4.25/Engine/Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

// Sets default values
AEncounter::AEncounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//This is how to give an actor a root component.
	MyRootComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEncounter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->SetActive(true,true);
}

// Called every frame
void AEncounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

