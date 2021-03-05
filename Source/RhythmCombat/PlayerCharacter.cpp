// Fill out your copyright notice in the Description page of Project Settings.

#include "RhythmCombatCharacter.h"
#include "PlayerCharacter.h"

#include "AIHelpers.h"
#include "InteractableInterface.h"

//get 1 working then repeat for the rest
void APlayerCharacter::BattleAction1() {
	//if in action select phase in combat
	if (CombatManagerRef->InCombat && !(CombatManagerRef->InRhythm) && LastPressedButton == Left) {
		//Square or X
		if (CharacterIndex == -1) {
			//PlayerCharacter
			ChosenAction = ActiveActions[0];
			CharacterIndex++;
		}
		else if (CharacterIndex < OtherPartyMembers.Num()) {
			//Member of Party
			OtherPartyMembers[CharacterIndex]->ChosenAction = ActiveActions[0];
			OtherPartyMembers[CharacterIndex]->TargetList.Add(CombatManagerRef->SelectedTarget);
			CharacterIndex++;
		}
		if(CharacterIndex >= OtherPartyMembers.Num()) {
			//All player party actions have been chosen
			CombatManagerRef->GenerateEnemyActions();
		};
	}
	else if (CombatManagerRef->InCombat && !(CombatManagerRef->InRhythm) && LastPressedButton != Left) {
		LastPressedButton = Left;
		if (CharacterIndex == -1) {
			UpdateTargetType(0, this);
		}
		else {
			//not player character, get member of party instead
			UpdateTargetType(0, OtherPartyMembers[CharacterIndex]);
		}
	}
	else if (CombatManagerRef->InRhythm) {

	}
}
//TODO - add targetable types to other actions
void APlayerCharacter::BattleAction2() {
	//if in action select phase in combat

	if (CombatManagerRef->InCombat && !(CombatManagerRef->InRhythm) && LastPressedButton == Top) {
		//Triangle or Y
		if (CharacterIndex == -1) {
			//PlayerCharacter
			ChosenAction = ActiveActions[1];
			CharacterIndex++;
		}
		else if (CharacterIndex < OtherPartyMembers.Num()) {
			//Member of Party
			OtherPartyMembers[CharacterIndex]->ChosenAction = ActiveActions[1];
			CharacterIndex++;
		}
		if (CharacterIndex >= OtherPartyMembers.Num()) {
			//All player party actions have been chosen
			CombatManagerRef->GenerateEnemyActions();
		};
	}
	else if (CombatManagerRef->InCombat && !(CombatManagerRef->InRhythm) && LastPressedButton != Top) {
		LastPressedButton = Top;
		if (CharacterIndex == -1) {
			UpdateTargetType(1, this);
		}
		else {
			UpdateTargetType(1, OtherPartyMembers[CharacterIndex]);
		}
	}
	else if (CombatManagerRef->InRhythm) {

	}
}
void APlayerCharacter::BattleAction3() {
	//if in action select phase in combat

	if (CombatManagerRef->InCombat && !(CombatManagerRef->InRhythm) && LastPressedButton == Right) {
		//Circle or B
		if (CharacterIndex == -1) {
			//PlayerCharacter
			ChosenAction = ActiveActions[2];
			CharacterIndex++;
		}
		else if (CharacterIndex < OtherPartyMembers.Num()) {
			//Member of Party
			OtherPartyMembers[CharacterIndex]->ChosenAction = ActiveActions[2];
			CharacterIndex++;
		}
		if (CharacterIndex >= OtherPartyMembers.Num()) {
			//All player party actions have been chosen
			CombatManagerRef->GenerateEnemyActions();
		};
	}
	else if (CombatManagerRef->InCombat && !(CombatManagerRef->InRhythm) && LastPressedButton != Right) {
		LastPressedButton = Right;
		if (CharacterIndex == -1) {
			UpdateTargetType(2, this);
		}
		else {
			UpdateTargetType(2, OtherPartyMembers[CharacterIndex]);
		}
	}
	else if (CombatManagerRef->InRhythm) {

	}
}
void APlayerCharacter::BattleAction4() {
	//if in action select phase in combat

	if (CombatManagerRef->InCombat && !(CombatManagerRef->InRhythm) && LastPressedButton == Bottom) {
		//Cross/X or A
		if (CharacterIndex == -1) {
			//PlayerCharacter
			ChosenAction = ActiveActions[3];
			CharacterIndex++;
		}
		else if (CharacterIndex < OtherPartyMembers.Num()) {
			//Member of Party
			OtherPartyMembers[CharacterIndex]->ChosenAction = ActiveActions[3];
			CharacterIndex++;
		}
		if (CharacterIndex >= OtherPartyMembers.Num()) {
			//All player party actions have been chosen
			CombatManagerRef->GenerateEnemyActions();
		};
	}
	else if (CombatManagerRef->InCombat && !(CombatManagerRef->InRhythm) && LastPressedButton != Bottom) {
		LastPressedButton = Bottom;
		if (CharacterIndex == -1) {
			UpdateTargetType(3, this);
		}
		else {
			UpdateTargetType(3, OtherPartyMembers[CharacterIndex]);
		}
	}
	else if (CombatManagerRef->InRhythm) {

	}
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	BestInteractable = FindInteractActors();
}

APlayerCharacter::APlayerCharacter()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"), true);
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->InitSphereRadius(300.0f);

	SphereComponent->SetCollisionProfileName("Interactable",true);
}

AActor* APlayerCharacter::FindInteractActors()
{
	//Get all Actors nearby
	TArray<AActor*> Actors;
	SphereComponent->GetOverlappingActors(Actors);

	//Get rid of any actors that aren't interactable
	/*
	for(int x=0; x < Actors.Num(); x++)
	{
		if (!Cast<IInteractableInterface>(Actors[x]) || !Actors[x]->Implements<UInteractableInterface>())
		{
			UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), *Actors[x]->GetName());
			Actors.RemoveAt(x);
			x--;
		}
	}
	*/
	int32 ClosestDistIndex = 0;
	if(Actors.Num() >= 1)
	{
		//Loop through them all and find the closest Actor
		FVector CurLoc = GetActorLocation();
		float ClosestDistSquared = 0.0f;
		for(int i=0; i < Actors.Num(); i++)
		{
			FVector Difference = CurLoc - Actors[i]->GetActorLocation();
			float DistSquared = Difference.SizeSquared();
			if(i==0)
			{
				ClosestDistSquared = DistSquared;
				ClosestDistIndex = i;
			}else
			{
				if(DistSquared < ClosestDistSquared)
				{
					ClosestDistSquared = DistSquared;
					ClosestDistIndex = i;
				}
			}
		}
	}else
	{
		return nullptr;
	}
	return Actors[ClosestDistIndex];
}

void APlayerCharacter::UpdateTargetType(int32 moveindex, ABaseCharacter* Targetter) {
	//updates the current targetable type based on the move that has been selected
	switch (ActiveActions[moveindex].Type)
	{
	case BasicAttack:
		//target 1 enemy
		CombatManagerRef->ChangeETargetType(Enemy, Targetter);
	case BasicDefend:
		//target self and prevent movement of target
		//for a defend I still want a confirm press right?
		CombatManagerRef->ChangeETargetType(Self, Targetter);
	case UseItem:
		//check targetable type of Item
		//TODO: Change this to fit the new Item system
		//CombatManagerRef->ChangeETargetType(Inventory[ActiveActions[moveindex].index].TargetGroup, Targetter);
	case UseAbility:
		//check targetable type of Ability
		CombatManagerRef->ChangeETargetType(Abilities[ActiveActions[moveindex].index].TargetGroup, Targetter);
	}
}

void APlayerCharacter::NavigateUp() {
	if (CombatManagerRef->TargetCategory == Ally) {
		//check if targetted character is the player
		if (CombatManagerRef->SelectedTarget == this) {
			//wrap to last member of the party
			CombatManagerRef->SelectedTarget = OtherPartyMembers[OtherPartyMembers.Num() - 1];

		}
		//if first member of the party that's not the player, then target the player
		else if (OtherPartyMembers[0] == CombatManagerRef->SelectedTarget) {
			CombatManagerRef->SelectedTarget = this;
		}
		else {
			//target the previous entry in the party
			for (int i = 1; i < OtherPartyMembers.Num(); i++) {
				if (OtherPartyMembers[i] == CombatManagerRef->SelectedTarget) {
					CombatManagerRef->SelectedTarget = OtherPartyMembers[i - 1];
					break;
				}
			}
		}
	}
	else if(CombatManagerRef->TargetCategory == Self){
		//do nothing
	}
	else {
		//if first enemy then wrap around
		if (CombatManagerRef->SelectedTarget == CombatManagerRef->EnemyParty[0]) {
			CombatManagerRef->SelectedTarget = CombatManagerRef->EnemyParty[CombatManagerRef->EnemyParty.Num() - 1];

		}
		else {
			//target previous enemy in list
			for (int i = 1; i < CombatManagerRef->EnemyParty.Num(); i++) {
				if (CombatManagerRef->EnemyParty[i] == CombatManagerRef->SelectedTarget) {
					CombatManagerRef->SelectedTarget = CombatManagerRef->EnemyParty[i - 1];
					break;
				}
			}
		}
	}

};
void APlayerCharacter::NavigateDown() {
	if (CombatManagerRef->TargetCategory == Ally) {
		//wrap to the player if end of party
		if (CombatManagerRef->SelectedTarget == OtherPartyMembers[OtherPartyMembers.Num() - 1]) {
			CombatManagerRef->SelectedTarget = this;
		}
		//if player, then target first in the party
		else if (CombatManagerRef->SelectedTarget == this) {
			CombatManagerRef->SelectedTarget = OtherPartyMembers[0];
		}
		else {
			//target the next entry in the party
			for (int i = 0; i < OtherPartyMembers.Num() - 1; i++) {
				if (OtherPartyMembers[i] == CombatManagerRef->SelectedTarget) {
					CombatManagerRef->SelectedTarget = OtherPartyMembers[i + 1];
					break;
				}
			}
		}
	}
	else if (CombatManagerRef->TargetCategory == Self) {
		//do nothing
	}
	else {
		//if last enemy then wrap around
		if (CombatManagerRef->SelectedTarget == CombatManagerRef->EnemyParty[CombatManagerRef->EnemyParty.Num() - 1]) {
			CombatManagerRef->SelectedTarget = CombatManagerRef->EnemyParty[0];

		}
		else {
			//target next enemy in list
			for (int i = 0; i < CombatManagerRef->EnemyParty.Num() - 1; i++) {
				if (CombatManagerRef->EnemyParty[i] == CombatManagerRef->SelectedTarget) {
					CombatManagerRef->SelectedTarget = CombatManagerRef->EnemyParty[i + 1];
					break;
				}
			}
		}
	};
};

void APlayerCharacter::UpdateActiveActions(FAction NewAction, EButtonPressed ButtonToAssign, ABaseCharacter* CharacterToUpdate) {
	//if () {

	//}
	switch (ButtonToAssign)
	{
	case Left:
		CharacterToUpdate->ActiveActions[0] = NewAction;
		break;
	case Top:
		CharacterToUpdate->ActiveActions[1] = NewAction;
		break;
	case Right:
		CharacterToUpdate->ActiveActions[2] = NewAction;
		break;
	case Bottom:
		CharacterToUpdate->ActiveActions[3] = NewAction;
		break;
	}
};


