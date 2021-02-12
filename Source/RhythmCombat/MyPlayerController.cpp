// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/CharacterMovementComponent.h"
#include "MyPlayerController.h"

void AMyPlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	PlayerCharacter = Cast<APlayerCharacter>(InPawn);
	if (PlayerCharacter)
	{
		PlayerCharacter->GetCharacterMovement()->SetActive(true, true);
		SetViewTargetWithBlend(PlayerCharacter, 0.0f, VTBlend_Linear);
	}
}