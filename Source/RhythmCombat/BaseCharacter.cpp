// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "InteractableInterface.h"

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

	ActiveActions.Add({ BasicAttack, 0 });
	ActiveActions.Add({ BasicAttack, 0 });
	ActiveActions.Add({ BasicDefend, 0 });
	ActiveActions.Add({ BasicDefend, 0 });

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseCharacter::InteractWith(AActor* Actor)
{
	IInteractableInterface* Interact = Cast<IInteractableInterface>(Actor);
	if(Interact)
	{
		return Interact->DoInteract_Implementation(this);
	}
	if(Actor->Implements<UInteractableInterface>())
	{
		return IInteractableInterface::Execute_DoInteract(Actor,this);
	}
	return false;
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

