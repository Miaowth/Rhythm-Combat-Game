// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleCamera.h"

// Sets default values
ABattleCamera::ABattleCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABattleCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

