// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "RhythmCombatCharacter.h"


#include "AIHelpers.h"
#include "InteractableInterface.h"
#include "Kismet/GameplayStatics.h"

void APlayerCharacter::BattleAction1() {
	//if in action select phase in combat
	if (CombatManagerRef->InCombat && !(CombatManagerRef->InRhythm) && LastPressedButton == Left) {
		//Square or X
		if (CharacterIndex == -1) {
			//PlayerCharacter
			ChosenAction = ActiveActions[0];
			TargetList.Add(CombatManagerRef->SelectedTarget);
			CharacterIndex++;
		}
		else if (CharacterIndex < OtherPartyMembers.Num() - 1) {
			//Member of Party
			OtherPartyMembers[CharacterIndex]->ChosenAction = ActiveActions[0];
			OtherPartyMembers[CharacterIndex]->TargetList.Add(CombatManagerRef->SelectedTarget);
			CharacterIndex++;
		}
		if(CharacterIndex >= OtherPartyMembers.Num()) {
			//All player party actions have been chosen
			UE_LOG(LogTemp, Warning, TEXT("All Actions Now Chosen"));

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
	else if (CombatManagerRef->InRhythm && CombatManagerRef->Button1Array.Num() > 0) {
		if ((CombatManagerRef->Button1Array[0].OwningChar == this || OtherPartyMembers.Contains(CombatManagerRef->Button1Array[0].OwningChar)) && CombatManagerRef->Button1Array.Num() > 0) {
			//this is a valid note for the player to hit
			//if(CombatManagerRef->Button1Array.Num() > 0){
			CurrentPos = UAkGameplayStatics::GetSourcePlayPosition(CombatManagerRef->ConductorRef->CombatPlayingID);
			UE_LOG(LogTemp, Warning, TEXT("current %d target %f"), CurrentPos, CombatManagerRef->Button1Array[0].PosInMs);
			HitButtonCheck(CombatManagerRef->Button1Array, true);
		}
		CombatManagerRef->RhythmSectionCompleteCheck();
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
			TargetList.Add(CombatManagerRef->SelectedTarget);
			CharacterIndex++;
		}
		else if (CharacterIndex < OtherPartyMembers.Num() - 1) {
			//Member of Party
			OtherPartyMembers[CharacterIndex]->ChosenAction = ActiveActions[1];
			OtherPartyMembers[CharacterIndex]->TargetList.Add(CombatManagerRef->SelectedTarget);
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
	else if (CombatManagerRef->InRhythm && CombatManagerRef->Button2Array.Num() > 0) {
		if ((CombatManagerRef->Button2Array[0].OwningChar == this || OtherPartyMembers.Contains(CombatManagerRef->Button2Array[0].OwningChar)) && CombatManagerRef->Button2Array.Num() > 0) {
			//this is a valid note for the player to hit
			CurrentPos = UAkGameplayStatics::GetSourcePlayPosition(CombatManagerRef->ConductorRef->CombatPlayingID);
			UE_LOG(LogTemp, Warning, TEXT("current %d target %f"), CurrentPos, CombatManagerRef->Button2Array[0].PosInMs);
			HitButtonCheck(CombatManagerRef->Button2Array, true);
		}
		CombatManagerRef->RhythmSectionCompleteCheck();
	}
}
void APlayerCharacter::BattleAction3() {
	//if in action select phase in combat

	if (CombatManagerRef->InCombat && !(CombatManagerRef->InRhythm) && LastPressedButton == Right) {
		//Circle or B
		if (CharacterIndex == -1) {
			//PlayerCharacter
			ChosenAction = ActiveActions[2];
			TargetList.Add(CombatManagerRef->SelectedTarget);
			CharacterIndex++;
		}
		else if (CharacterIndex < OtherPartyMembers.Num() - 1) {
			//Member of Party
			OtherPartyMembers[CharacterIndex]->ChosenAction = ActiveActions[2];
			OtherPartyMembers[CharacterIndex]->TargetList.Add(CombatManagerRef->SelectedTarget);
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
	else if (CombatManagerRef->InRhythm && CombatManagerRef->Button3Array.Num() > 0) {
		if ((CombatManagerRef->Button3Array[0].OwningChar == this || OtherPartyMembers.Contains(CombatManagerRef->Button3Array[0].OwningChar)) && CombatManagerRef->Button3Array.Num() > 0) {
			//this is a valid note for the player to hit
			CurrentPos = UAkGameplayStatics::GetSourcePlayPosition(CombatManagerRef->ConductorRef->CombatPlayingID);
			UE_LOG(LogTemp, Warning, TEXT("current %d target %f"), CurrentPos, CombatManagerRef->Button3Array[0].PosInMs);
			HitButtonCheck(CombatManagerRef->Button3Array, false);
		}
		CombatManagerRef->RhythmSectionCompleteCheck();
	}
}
void APlayerCharacter::BattleAction4() {
	//if in action select phase in combat

	if (CombatManagerRef->InCombat && !(CombatManagerRef->InRhythm) && LastPressedButton == Bottom) {
		//Cross/X or A
		if (CharacterIndex == -1) {
			//PlayerCharacter
			ChosenAction = ActiveActions[3];
			TargetList.Add(CombatManagerRef->SelectedTarget);
			CharacterIndex++;
		}
		else if (CharacterIndex < OtherPartyMembers.Num() - 1) {
			//Member of Party
			OtherPartyMembers[CharacterIndex]->ChosenAction = ActiveActions[3];
			OtherPartyMembers[CharacterIndex]->TargetList.Add(CombatManagerRef->SelectedTarget);
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
	else if (CombatManagerRef->InRhythm  && CombatManagerRef->Button4Array.Num() > 0) {
		if ((CombatManagerRef->Button4Array[0].OwningChar == this || OtherPartyMembers.Contains(CombatManagerRef->Button4Array[0].OwningChar)) && CombatManagerRef->Button4Array.Num() > 0) {
			//this is a valid note for the player to hit
			CurrentPos = UAkGameplayStatics::GetSourcePlayPosition(CombatManagerRef->ConductorRef->CombatPlayingID);
			UE_LOG(LogTemp, Warning, TEXT("current %d target %f"), CurrentPos, CombatManagerRef->Button4Array[0].PosInMs);
			HitButtonCheck(CombatManagerRef->Button4Array, false);
		}
		CombatManagerRef->RhythmSectionCompleteCheck();
	}
}

void APlayerCharacter::HitButtonCheck(TArray<FPatternNote> &TargetArray, bool TopTrack)
{
	if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Miss] - 500))
	{
		//invalid hit
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Miss])) {
		//miss
		UE_LOG(LogTemp, Warning, TEXT("MISS %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Miss]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Miss]));
		LastHitQuality = Miss;
		PerfectComboCounter = 0;
		UpdateNote(TargetArray, 0.0f, TopTrack);
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Poor])) {
		//poor hit
		UE_LOG(LogTemp, Warning, TEXT("POOR %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Poor]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Poor]));
		LastHitQuality = Poor;
		PerfectComboCounter = 0;
		UpdateNote(TargetArray, 20.0f, TopTrack);
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Okay])) {
		//okay hit
		UE_LOG(LogTemp, Warning, TEXT("OKAY %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Okay]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Okay]));
		LastHitQuality = Okay;
		PerfectComboCounter = 0;
		UpdateNote(TargetArray, 40.0f, TopTrack);
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Good])) {
		//good hit
		UE_LOG(LogTemp, Warning, TEXT("GOOD %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Good]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Good]));
		LastHitQuality = Good;
		PerfectComboCounter = 0;
		UpdateNote(TargetArray, 60.0f, TopTrack);
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Great])) {
		//great hit
		UE_LOG(LogTemp, Warning, TEXT("GREAT %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Great]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Great]));
		LastHitQuality = Great;
		PerfectComboCounter = 0;
		UpdateNote(TargetArray, 80.0f, TopTrack);
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Perfect])) {
		//perfect hit
		UE_LOG(LogTemp, Warning, TEXT("PERFECT %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Perfect]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Perfect]));
		LastHitQuality = Perfect;
		PerfectComboCounter += 1;
		UpdateNote(TargetArray, 100.0f, TopTrack);
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Perfect])) {
		//perfect hit
		UE_LOG(LogTemp, Warning, TEXT("PERFECT %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Perfect]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Perfect]));
		LastHitQuality = Perfect;
		PerfectComboCounter += 1;
		UpdateNote(TargetArray, 100.0f, TopTrack);
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Great])) {
		//great hit
		UE_LOG(LogTemp, Warning, TEXT("GREAT %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Great]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Great]));
		LastHitQuality = Great;
		PerfectComboCounter = 0;
		UpdateNote(TargetArray, 80.0f, TopTrack);
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Good])) {
		//good hit
		UE_LOG(LogTemp, Warning, TEXT("GOOD %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Good]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Good]));
		LastHitQuality = Good;
		PerfectComboCounter = 0;
		UpdateNote(TargetArray, 60.0f, TopTrack);
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Okay])) {
		//okay hit
		UE_LOG(LogTemp, Warning, TEXT("OKAY %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Okay]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Okay]));
		LastHitQuality = Okay;
		PerfectComboCounter = 0;
		UpdateNote(TargetArray, 40.0f, TopTrack);
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Poor])) {
		//poor hit
		UE_LOG(LogTemp, Warning, TEXT("POOR %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Poor]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Poor]));
		LastHitQuality = Poor;
		PerfectComboCounter = 0;
		UpdateNote(TargetArray, 20.0f, TopTrack);
	}
	else if (CombatManagerRef->IsBelowBoundary(CurrentPos, TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Miss])) {
		//miss
		UE_LOG(LogTemp, Warning, TEXT("MISS %f lower %f upper"), (TargetArray[0].PosInMs - CombatManagerRef->HitBoundaries[Miss]), (TargetArray[0].PosInMs + CombatManagerRef->HitBoundaries[Miss]));
		LastHitQuality = Miss;
		PerfectComboCounter = 0;
		UpdateNote(TargetArray, 0.0f, TopTrack);
	}

}
void APlayerCharacter::UpdateNote(TArray<FPatternNote> &TargetArray, float Accuracy, bool TopTrack) {
	AbilityAccuracyValues.Add(Accuracy);
	if (TargetArray[0].IsFinal) {
		//calculate the accuracy average across all notes in the pattern
		float accuracyaverage = 0;
		for (int i = 0; i < TargetArray[0].OwningChar->AbilityAccuracyValues.Num(); i++) {
			accuracyaverage += TargetArray[0].OwningChar->AbilityAccuracyValues[i];
		}
		accuracyaverage = accuracyaverage / TargetArray[0].OwningChar->AbilityAccuracyValues.Num();
		//implement the effect of the completed action
		switch (TargetArray[0].OwningChar->ChosenAction.Type)
		{
		case BasicAttack:
			
			for (int i = 0; i < TargetArray[0].OwningChar->TargetList.Num(); i++) {
				UE_LOG(LogTemp, Warning, TEXT("Damage: %d"), TargetArray[0].OwningChar->Level * 2 * accuracyaverage * TargetArray[0].OwningChar->TargetList[i]->DefenseModifier);
				TargetArray[0].OwningChar->TargetList[i]->CharacterStats.HealthPoints -= 
					TargetArray[0].OwningChar->Level * 2 * accuracyaverage * TargetArray[0].OwningChar->TargetList[i]->DefenseModifier;
				//Kill our enemies
			};
			for (int i = 0; i < CombatManagerRef->EnemyParty.Num(); i++) {
				if (CombatManagerRef->EnemyParty[i]->CharacterStats.HealthPoints <= 0) {
					//enemy is dead
					for (int j = 0; j < OtherPartyMembers.Num(); j++) {
						OtherPartyMembers[j]->TargetList.Remove(CombatManagerRef->EnemyParty[i]);
					};
					TargetList.Remove(CombatManagerRef->EnemyParty[i]);
					CombatManagerRef->BattleOrder.RemoveSingleSwap(CombatManagerRef->EnemyParty[i], false);
					CombatManagerRef->EnemyParty[i]->Destroy();
					CombatManagerRef->EnemyParty.RemoveAt(i, 1, false);
					
				};
				CombatManagerRef->BattleOrder.Shrink();
			}
			CombatManagerRef->RemoveInvalidNotes(CombatManagerRef->Button1Array);
			CombatManagerRef->RemoveInvalidNotes(CombatManagerRef->Button2Array);
			CombatManagerRef->RemoveInvalidNotes(CombatManagerRef->Button3Array);
			CombatManagerRef->RemoveInvalidNotes(CombatManagerRef->Button4Array);
			CombatManagerRef->EnemyParty.Shrink();
			
			break;
		case BasicDefend:
			TargetArray[0].OwningChar->IsDefending = true;
			TargetArray[0].OwningChar->DefenseModifier = 100 - accuracyaverage;
			break;
		case UseItem:
			//TODO
			break;

		case UseAbility:
			//TODO
			break;
		default:
			break;
		}
	}
	TargetArray[0].UIElement->Destroy();
	TargetArray.RemoveAt(0);
	CombatManagerRef->ConductorRef->RemoveUI(TopTrack);
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	BestInteractable = FindInteractActors();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> CombatManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACombatManager::StaticClass(), CombatManagers);

	CombatManagerRef = Cast<ACombatManager>(CombatManagers[0]);
}

APlayerCharacter::APlayerCharacter()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"), true);
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->InitSphereRadius(300.0f);
	PrimaryActorTick.bCanEverTick = true;
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
		break;
	case BasicDefend:
		//target self and prevent movement of target
		//for a defend I still want a confirm press right?
		CombatManagerRef->ChangeETargetType(Self, Targetter);
		break;
	case UseItem:
		//check targetable type of Item
		//TODO: Change this to fit the new Item system
		//CombatManagerRef->ChangeETargetType(Inventory[ActiveActions[moveindex].index].TargetGroup, Targetter);
		break;
	case UseAbility:
		//check targetable type of Ability
		CombatManagerRef->ChangeETargetType(Abilities[ActiveActions[moveindex].index].TargetGroup, Targetter);
		break;
	}
}


void APlayerCharacter::NavigateUp() {
	UE_LOG(LogTemp, Warning, TEXT("Some warning message"));

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
	CombatManagerRef->TargetLamp->MovePosition(CombatManagerRef->SelectedTarget->GetTransform());
};
void APlayerCharacter::NavigateDown() {
	UE_LOG(LogTemp, Warning, TEXT("Some warning message"));

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
	CombatManagerRef->TargetLamp->MovePosition(CombatManagerRef->SelectedTarget->GetTransform());
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


