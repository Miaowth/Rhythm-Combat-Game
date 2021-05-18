// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackProjectile.h"

// Sets default values
AAttackProjectile::AAttackProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//This is how to give an actor a root component.
	MyRootComponent->SetupAttachment(RootComponent);

	ProjectileBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh Component"));
	ProjectileBody->SetupAttachment(MyRootComponent);
}

// Called when the game starts or when spawned
void AAttackProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttackProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAttackProjectile::CalculateSpeed_Implementation(){}

