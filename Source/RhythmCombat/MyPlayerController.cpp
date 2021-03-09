// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"


void AMyPlayerController::Tick(float DeltaSeconds)
{
	if(ResettingCamera)
	{
		FRotator DesiredRotator = FMath::RInterpTo(GetControlRotation(),CharacterRotation,DeltaSeconds,10.0f);
		SetControlRotation(DesiredRotator);
		if(DesiredRotator.Equals(CharacterRotation,1))
		{
			ResettingCamera = false;
		}
	}
}

void AMyPlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	APlayerCharacter* pc = Cast<APlayerCharacter>(InPawn);
	if (pc)
	{
		PlayerCharacter = pc;
		PlayerCharacter->GetCharacterMovement()->SetActive(true, true);
		SetViewTargetWithBlend(PlayerCharacter, 0.0f, VTBlend_Linear);

		
	}
}

void AMyPlayerController::SetupInputComponent()
{
	// Set up gameplay key bindings
	Super::SetupInputComponent();
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::DoJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyPlayerController::StopJump);

	//inputs for combat
	
	InputComponent->BindAction("BattleAction1", IE_Pressed, this, &AMyPlayerController::BattleAction1);
	InputComponent->BindAction("BattleAction2", IE_Pressed, this, &AMyPlayerController::BattleAction2);
	InputComponent->BindAction("BattleAction3", IE_Pressed, this, &AMyPlayerController::BattleAction3);
	InputComponent->BindAction("BattleAction4", IE_Pressed, this, &AMyPlayerController::BattleAction4);

	InputComponent->BindAction("Interact", IE_Pressed, this, &AMyPlayerController::DoInteract);
	InputComponent->BindAction("ResetCamera", IE_Pressed, this, &AMyPlayerController::ResetCamera);

	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APlayerController::AddYawInput);
	InputComponent->BindAxis("TurnRate", this, &AMyPlayerController::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APlayerController::AddPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AMyPlayerController::LookUpAtRate);

}

void AMyPlayerController::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (PlayerCharacter) {
		AddYawInput((FMath::Pow(Rate, 2) * FMath::Sign(Rate)) * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMyPlayerController::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (PlayerCharacter) {
		AddPitchInput((FMath::Pow(Rate, 2) * FMath::Sign(Rate)) * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMyPlayerController::MoveForward(float Value)
{
	if(PlayerCharacter)
	{
		if (Value != 0.0f)
		{
			// find out which way is forward
			const FRotator Rotation = GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			PlayerCharacter->AddMovementInput(Direction, Value);
		}
	}
	
}

void AMyPlayerController::MoveRight(float Value)
{
	if (PlayerCharacter)
	{
		if (Value != 0.0f)
		{
			// find out which way is right
			const FRotator Rotation = GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
	
			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			PlayerCharacter->AddMovementInput(Direction, Value);
		}
	}
	
}

void AMyPlayerController::DoJump()
{
	if(PlayerCharacter)
	{
		PlayerCharacter->Jump();
	}
}

void AMyPlayerController::StopJump()
{
	if(PlayerCharacter)
	{
		PlayerCharacter->StopJumping();
	}
}

void AMyPlayerController::DoInteract()
{
	if(PlayerCharacter)
	{
		UE_LOG(LogTemp,Warning,TEXT("Interact?"))
		AActor* Interact = PlayerCharacter->FindInteractActors();
		if(Interact)
		{
			PlayerCharacter->InteractWith(Interact);
		} 	
	}
}

void AMyPlayerController::ResetCamera()
{
	if(!ResettingCamera)
	{
		ResettingCamera = true;
		CharacterRotation = GetCharacter()->GetActorRotation();
	}
}

void AMyPlayerController::BattleAction1()
{
	if(PlayerCharacter->CombatManagerRef)
	{
		if(PlayerCharacter->CombatManagerRef->InCombat)
		{
			PlayerCharacter->BattleAction1();
		}
		
	}
	
}

void AMyPlayerController::BattleAction2()
{
	if(PlayerCharacter->CombatManagerRef)
	{
		if(PlayerCharacter->CombatManagerRef->InCombat)
		{
			PlayerCharacter->BattleAction2();
		}
		
	}
}

void AMyPlayerController::BattleAction3()
{
	if(PlayerCharacter->CombatManagerRef)
	{
		if(PlayerCharacter->CombatManagerRef->InCombat)
		{
			PlayerCharacter->BattleAction3();
		}
		
	}
}

void AMyPlayerController::BattleAction4()
{
	if(PlayerCharacter->CombatManagerRef)
	{
		if(PlayerCharacter->CombatManagerRef->InCombat)
		{
			PlayerCharacter->BattleAction4();
		}
		
	}
}

void AMyPlayerController::NavigateUp()
{
}

void AMyPlayerController::NavigateDown()
{
}
