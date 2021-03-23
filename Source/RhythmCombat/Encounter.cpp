// Fill out your copyright notice in the Description page of Project Settings.


#include "Encounter.h"

#include "GameFramework/CharacterMovementComponent.h"


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

void AEncounter::CopySkelemeshandAnimBP(ABaseCharacter* Character)
{
	GetMesh()->SetSkeletalMesh(Character->GetMesh()->SkeletalMesh,false);
	GetMesh()->SetAnimClass(Character->GetMesh()->AnimClass);
	for (int32 i = 0; i < Character->GetMesh()->GetMaterials().Num(); i++)
	{
		UMaterialInterface* mat = Character->GetMesh()->GetMaterials()[i];
		GetMesh()->SetMaterial(i,mat);
	}
}



