// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "AttackProjectile.h"
#include "InteractableInterface.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	FAction tempAttack;
	tempAttack.Type = BasicAttack;
	tempAttack.index = 0;
	ActiveActions.Add(tempAttack);
	ActiveActions.Add(tempAttack);
	tempAttack.Type = BasicDefend;
	ActiveActions.Add(tempAttack);
	ActiveActions.Add(tempAttack);

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABaseCharacter::SpawnProjectile(FTransform TargetDestination, float BeatDuration) {
	FActorSpawnParameters SpawnInfo;
	AAttackProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AAttackProjectile>(BP_AttackProjectile, GetActorLocation(), GetActorRotation(), SpawnInfo);
	SpawnedProjectile->StartingPoint = GetActorTransform();
	SpawnedProjectile->DestinationPoint = TargetDestination;
	SpawnedProjectile->BeatDuration = BeatDuration;
	SpawnedProjectile->CalculateSpeed();

}

bool ABaseCharacter::InteractWith(AActor* Actor)
{
	IInteractableInterface* Interact = Cast<IInteractableInterface>(Actor);
	if (Interact)
	{
		if (Interact->DoInteract_Implementation(this))
		{
			LookAtActor(Actor);
		}
		else
		{
			//Go to the right place and try again
		}
	}
	if (Actor->Implements<UInteractableInterface>())
	{
		if (IInteractableInterface::Execute_DoInteract(Actor, this))
		{
			LookAtActor(Actor);
		}
		else
		{
			//Go to the right place and try again
		}
	}
	return false;
}

void ABaseCharacter::LookAtActor(AActor* Actor)
{
	FVector Diff = Actor->GetActorLocation() - GetActorLocation();
	Diff.Normalize();
	Diff.Z = 0.f;

	SetActorRotation(Diff.Rotation());
}



