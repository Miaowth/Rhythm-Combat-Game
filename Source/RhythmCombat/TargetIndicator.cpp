// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetIndicator.h"

// Sets default values
ATargetIndicator::ATargetIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//This is how to give an actor a root component.
	MyRootComponent->SetupAttachment(RootComponent);

	LampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lamp Mesh Component"));
	LampMesh->SetupAttachment(MyRootComponent);
}

// Called when the game starts or when spawned
void ATargetIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ATargetIndicator::MovePosition(FTransform TargetPosition)
{
	FTransform Destination = TargetPosition;
	Destination.AddToTranslation({ 0, 0, 200 });
	SetActorTransform(Destination);
 }
void ATargetIndicator::ToggleLight()
{
	if (IsLit) {
		//Turn off lamp
		IsLit = false;
	}
	else {
		//Turn on lamp
		IsLit = true;
	}
}