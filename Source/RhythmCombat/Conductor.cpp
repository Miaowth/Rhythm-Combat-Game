// Fill out your copyright notice in the Description page of Project Settings.


#include "Conductor.h"

// Sets default values
AConductor::AConductor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConductor::BeginPlay()
{
	Super::BeginPlay();
	
}
void AConductor::BeginCombat_Implementation()
{
	// Logic needed when blueprints don't implement the event. Can be empty.
}

// Called every frame
void AConductor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

