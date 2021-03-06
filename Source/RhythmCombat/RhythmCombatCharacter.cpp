// Copyright Epic Games, Inc. All Rights Reserved.

#include "RhythmCombatCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Structs.h"


//////////////////////////////////////////////////////////////////////////
// ARhythmCombatCharacter

ARhythmCombatCharacter::ARhythmCombatCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARhythmCombatCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//inputs for combat
	PlayerInputComponent->BindAction("BattleAction1", IE_Pressed, this, &ARhythmCombatCharacter::BattleAction1);
	PlayerInputComponent->BindAction("BattleAction2", IE_Pressed, this, &ARhythmCombatCharacter::BattleAction2);
	PlayerInputComponent->BindAction("BattleAction3", IE_Pressed, this, &ARhythmCombatCharacter::BattleAction3);
	PlayerInputComponent->BindAction("BattleAction4", IE_Pressed, this, &ARhythmCombatCharacter::BattleAction4);


	PlayerInputComponent->BindAxis("MoveForward", this, &ARhythmCombatCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARhythmCombatCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ARhythmCombatCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ARhythmCombatCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ARhythmCombatCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ARhythmCombatCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ARhythmCombatCharacter::OnResetVR);
}


void ARhythmCombatCharacter::BattleAction1() {

}
void ARhythmCombatCharacter::BattleAction2() {

}
void ARhythmCombatCharacter::BattleAction3() {

}
void ARhythmCombatCharacter::BattleAction4() {

}

void ARhythmCombatCharacter::NavigateUp() {};
void ARhythmCombatCharacter::NavigateDown() {};

void ARhythmCombatCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ARhythmCombatCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (!CombatManagerRef->InCombat) {
		Jump();
	}
}

void ARhythmCombatCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (!CombatManagerRef->InCombat) {
		StopJumping();
	}
}

void ARhythmCombatCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (!CombatManagerRef->InCombat) {
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void ARhythmCombatCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (!CombatManagerRef->InCombat) {
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void ARhythmCombatCharacter::MoveForward(float Value)
{
	if (((Controller != NULL) && (Value != 0.0f))&& !CombatManagerRef->InCombat)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ARhythmCombatCharacter::MoveRight(float Value)
{
	if ( ((Controller != NULL) && (Value != 0.0f)) && !CombatManagerRef->InCombat)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


