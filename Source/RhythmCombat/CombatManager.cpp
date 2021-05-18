// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"
#include "PlayerCharacter.h"
#include "EncounterManager.h"
#include "MyPlayerController.h"
#include "RhythmUI_Manager.h"
#include "RhythmUI_Note.h"
#include "AttackProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACombatManager::ACombatManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//This is how to give an actor a root component.
	MyRootComponent->SetupAttachment(RootComponent);

	InCombat = InRhythm = false;
}

// Called when the game starts or when spawned
void ACombatManager::BeginPlay()
{
	Super::BeginPlay();
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (player)
	{
		PlayerCharacter = player;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Player Character not assignable, crashes imminent."))
	}

}

// Called every frame
void ACombatManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (InRhythm) {
		ConductorRef->UpdateRhythmUI(DeltaTime);
	}
}
void ACombatManager::InitialiseCombat()
{
	//combine the enemy and player arrays into a turn order array using a mergesort function
	CreateTurnOrder();
	InCombat = true;
	SelectedTarget = EnemyParty[0];
	PlayerCharacter->CharacterIndex = -1;
	FBeginCombatDelegateDeclaration.Broadcast();
	Button1Array.Empty();
	Button2Array.Empty();
	Button3Array.Empty();
	Button4Array.Empty();
	ConductorRef->BeginCombat();
}

//helper function to change the current type of target and currently selected target
void ACombatManager::ChangeETargetType(ETargetType NewType, ABaseCharacter* Targetter) {
	TargetCategory = NewType;
	switch (NewType)
	{
	case Ally:
		SelectedTarget = PlayerCharacter;
		break;
	case Enemy:
		SelectedTarget = EnemyParty[0];
		break;
	case Self:
		SelectedTarget = Targetter;
		break;
	}
	TargetLamp->MovePosition(SelectedTarget->GetTransform());
}
void ACombatManager::CreateTurnOrder() {
	if (PlayerCharacter->OtherPartyMembers.Num() > 0) {
		BattleOrder.Append(PlayerCharacter->OtherPartyMembers);
	}
	BattleOrder.Append(EnemyParty);
	BattleOrder.Add(PlayerCharacter);
	BattleOrder.Sort([](ABaseCharacter& a, ABaseCharacter& b) {return a.CharacterStats.Speed < b.CharacterStats.Speed; });
}

void ACombatManager::RemoveInvalidNotes(TArray<FPatternNote> &ArrayToClean, bool IsTopTrack) {
	TArray<FPatternNote> CleanedArray;
	for (int i = 0; i < ArrayToClean.Num(); i++) {
		//(IsValid(ArrayToClean[i].OwningChar) && IsValid(ArrayToClean[i].UIElement)
		if (ArrayToClean[i].OwningChar->IsAlive) {
			//do nothing
			CleanedArray.Add(ArrayToClean[i]);
		}
		else {
			//ArrayToClean[i].UIElement->Destroy();
			if (IsTopTrack && ArrayToClean.Num() > 0) {
				TArray<ARhythmUI_Note*> TempTopArray;
				for (int j = 0; j < ConductorRef->RhythmUIManagerRef->TopTrackNoteArray.Num(); j++) {
					if (ConductorRef->RhythmUIManagerRef->TopTrackNoteArray[j]->OwningChar->IsAlive) {
						TempTopArray.Add(ConductorRef->RhythmUIManagerRef->TopTrackNoteArray[j]);
					}
					else {
						ConductorRef->RhythmUIManagerRef->TopTrackNoteArray[j]->Destroy();
					}
				}
				ConductorRef->RhythmUIManagerRef->TopTrackNoteArray = TempTopArray;
			}
			else {
				TArray<ARhythmUI_Note*> TempBottomArray;
				for (int j = 0; j < ConductorRef->RhythmUIManagerRef->BottomTrackNoteArray.Num(); j++) {
					if (ConductorRef->RhythmUIManagerRef->BottomTrackNoteArray[j]->OwningChar->IsAlive) {
						TempBottomArray.Add(ConductorRef->RhythmUIManagerRef->BottomTrackNoteArray[j]);
					}
					else {
						ConductorRef->RhythmUIManagerRef->BottomTrackNoteArray[j]->Destroy();
					}
				}
				ConductorRef->RhythmUIManagerRef->BottomTrackNoteArray = TempBottomArray;
			}
		};
	}
	ArrayToClean = CleanedArray;
}

void ACombatManager::GenerateEnemyActions() {
	//TODO - make enemy smort
	for (int i = 0; i < EnemyParty.Num(); i++) {
		//pick a random active action that the enemy has available
		EnemyParty[i]->TargetList.Empty();
		EnemyParty[i]->ChosenAction = EnemyParty[i]->ActiveActions[FMath::RandRange(0, 3)];
		int32 tempint = FMath::RandRange(0, PlayerCharacter->OtherPartyMembers.Num());
		switch (EnemyParty[i]->ChosenAction.Type)
		{
		case BasicAttack:
			if (tempint == 0) {
				EnemyParty[i]->TargetList.Add(PlayerCharacter);
			}
			else {
				EnemyParty[i]->TargetList.Add(PlayerCharacter->OtherPartyMembers[tempint - 1]);
			}

			break;
		case BasicDefend:
			EnemyParty[i]->TargetList.Add(EnemyParty[i]);
			break;
		default:
			break;
		}
		//TODO - add target selection
	}
	EnterRhythmPhase();
}

void ACombatManager::EnterRhythmPhase() {
	//
	UE_LOG(LogTemp, Warning, TEXT("Rhythm Phase Function Called"));
	//set the button inputs to start from the next bar
	ConductorRef->PatternBarStart = ConductorRef->NextBarStartPos + ConductorRef->BarsShownInAdvance * ConductorRef->BarDuration;
	//if too close to the start of the next bar, wait an additional bar
	//if (ConductorRef->BeatNum > ConductorRef->BeatsPerBar / 2) {
	//	ConductorRef->PatternBarStart += ConductorRef->BarDuration;
	//}
	ConductorRef->CurrentPhase = Rhythm;
	ConductorRef->UpdatePhaseUI();
	for (int i = 0; i < BattleOrder.Num(); i++) {
		switch (BattleOrder[i]->ChosenAction.Type)
		{
		case 0:
			//basicattack
			//this pattern is the same for all characters
			Button1Array.Add({
				false,
				BattleOrder[i],
				ConductorRef->PatternBarStart //start of the bar
				});
			Button1Array.Add({
				true,
				BattleOrder[i],
				(ConductorRef->PatternBarStart + ConductorRef->BeatLength)
				});
			if (EnemyParty.Contains(BattleOrder[i])) {
				//generates the hit value for the note.
				//TODO - update complexity for enemy difficulty
				BattleOrder[i]->AbilityAccuracyValues.Add(70.0f);
				BattleOrder[i]->AbilityAccuracyValues.Add(70.0f);
			};
			//UE_LOG(LogTemp, Warning, TEXT("%f bar start %f position"), ConductorRef->PatternBarStart, Button1Array[0].PosInMs);
			break;
		case 1:
			//basicdefend
			//this pattern is the same for all characters
			Button1Array.Add({
				true,
				BattleOrder[i],
				ConductorRef->PatternBarStart
				});
			if (EnemyParty.Contains(BattleOrder[i])) {
				//generates the hit value for the note.
				//TODO - update complexity for enemy difficulty
				BattleOrder[i]->AbilityAccuracyValues.Add(50.0f);
			};
			break;
		case 2:
			//Item
			//TODO - implement once items are fully functional
			break;
		case 3:
			//for each button in the mapping for the ability the player has selected, 
			//calculate when it should be pressed and add it to the appropriate array
			//Ability
			for (int j = 0; j < BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern.Num() - 1; j++) {
				switch (BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j].ButtonIndex)
				{
				case 0:
					//square or x
					if (j == BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern.Num() - 1) {
						Button1Array.Add({
							true,
							BattleOrder[i],
							ConductorRef->ConvertBeatMapToMS(BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j], ConductorRef->PatternBarStart)
							});
					}
					else {
						Button1Array.Add({
							false,
							BattleOrder[i],
							ConductorRef->ConvertBeatMapToMS(BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j], ConductorRef->PatternBarStart)
							});
					}
					break;
				case 1:
					//triangle or y
					if (j == BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern.Num() - 1) {
						Button2Array.Add({
							true,
							BattleOrder[i],
							ConductorRef->ConvertBeatMapToMS(BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j], ConductorRef->PatternBarStart)
							});
					}
					else {
						Button2Array.Add({
							false,
							BattleOrder[i],
							ConductorRef->ConvertBeatMapToMS(BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j], ConductorRef->PatternBarStart)
							});
					}
					break;
				case 2:
					//circle or a
					if (j == BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern.Num() - 1) {
						Button3Array.Add({
							true,
							BattleOrder[i],
							ConductorRef->ConvertBeatMapToMS(BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j], ConductorRef->PatternBarStart)
							});
					}
					else {
						Button3Array.Add({
							false,
							BattleOrder[i],
							ConductorRef->ConvertBeatMapToMS(BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j], ConductorRef->PatternBarStart)
							});
					}
					break;
				case 3:
					//cross or b
					if (j == BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern.Num() - 1) {
						Button4Array.Add({
							true,
							BattleOrder[i],
							ConductorRef->ConvertBeatMapToMS(BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j], ConductorRef->PatternBarStart)
							});
					}
					else {
						Button4Array.Add({
							false,
							BattleOrder[i],
							ConductorRef->ConvertBeatMapToMS(BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j], ConductorRef->PatternBarStart)
							});
					}
					break;
				default:
					//this should never happen
					break;
				}
				if (EnemyParty.Contains(BattleOrder[i])) {
					//generates the hit value for the note.
					//TODO - update complexity for enemy difficulty
					BattleOrder[i]->AbilityAccuracyValues.Add(70.0f);
				};
			};
			break;
		default:
			break;
		};
		//put in a bars rest between patterns

		//Start from next bar after a 1 bar break if late in bar
		if (ConductorRef->BeatNum > ConductorRef->BeatsPerBar / 2) {
			ConductorRef->PatternBarStart += ConductorRef->BarDuration * 2;
		}
		else {
			ConductorRef->PatternBarStart += ConductorRef->BarDuration;
		};

	}

	InRhythm = true;
	ConductorRef->WaitingForNextBar = true;
}
void ACombatManager::RhythmSectionCompleteCheck()
{
	//this is for checking if all arrays are empty
	if (Button1Array.Num() == 0 && Button2Array.Num() == 0 && Button3Array.Num() == 0 && Button4Array.Num() == 0) {
		//end of round clean up
		InRhythm = false;
		UE_LOG(LogTemp, Warning, TEXT("Swapped To Select"));
		PlayerCharacter->LastPressedButton = None;
		PlayerCharacter->CharacterIndex = -1;
		for (int i = 0; i < PlayerCharacter->OtherPartyMembers.Num(); i++) {
			PlayerCharacter->OtherPartyMembers[i]->ChosenAction = {};
			PlayerCharacter->OtherPartyMembers[i]->TargetList.Empty();
			PlayerCharacter->OtherPartyMembers[i]->CurrentPerfectComboCounter = 0;
			PlayerCharacter->OtherPartyMembers[i]->AbilityAccuracyValues = {};
		}
		PlayerCharacter->ChosenAction = {};
		PlayerCharacter->TargetList.Empty();
		PlayerCharacter->CurrentPerfectComboCounter = 0;
		PlayerCharacter->AbilityAccuracyValues = {};
		PlayerCharacter->LastHitQuality = Invalid;
		ConductorRef->CurrentPhase = ActionSelect;
		ConductorRef->UpdatePhaseUI();
	};

	if (EnemyParty.Num() == 0) {
		//return to overworld
		InCombat = false;
		InRhythm = false;
		SelectedTarget = NULL;
		PlayerCharacter->CharacterIndex = -1;
		PlayerCharacter->LastHitQuality = Invalid;
		EncounterManagerRef->EnableEncounters();
		FEndCombatDelegateDeclaration.Broadcast();
		PlayerCharacter->TeleportTo(PlayerCharacter->PosInWorld.GetLocation(), PlayerCharacter->PosInWorld.Rotator());
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAttackProjectile::StaticClass(), FoundActors);
		for (int i = 0; i < FoundActors.Num(); i++) {
			FoundActors[i]->Destroy();
		}
		Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->Possess(PlayerCharacter);
		ConductorRef->EndCombat();
		ConductorRef->CurrentPhase = Complete;
		ConductorRef->UpdatePhaseUI();
	};
}

float ACombatManager::PatternAccuracyScore(ABaseCharacter* ActiveCharacter) {
	//calculates the overall accuracy score and ability effectiveness
	//currently uses the mean
	float TotalScore = 0;
	for (int32 i = 0; i < ActiveCharacter->AbilityAccuracyValues.Num(); i++) {
		TotalScore += ActiveCharacter->AbilityAccuracyValues[i];
	}

	return TotalScore / ActiveCharacter->AbilityAccuracyValues.Num();
};

bool ACombatManager::IsBelowBoundary(int32 CurrentPos, int32 Boundary) {
	return(CurrentPos < Boundary);
}
bool ACombatManager::IsAboveBoundary(int32 CurrentPos, int32 Boundary) {
	return(CurrentPos > Boundary);
}
//pretty sure these are defunct but oh well
bool ACombatManager::Escape(ABaseCharacter* EscapingCharacter, TArray<AActor*> Party)
{
	if (EscapingCharacter == PlayerCharacter) {
		//then player running away
		if (GetChance(0, 100, 50)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (GetChance(0, 100, 50)) {
			//successfully ran
			if (Party.Num() == 1) {
				//last enemy is running away
				return true;
			}
			else {
				//TODO - runaway anim
				int32 characterindex = -1;
				for (int32 i = 0; i < Party.Num(); i++) {
					if (Party[i] == EscapingCharacter) {
						//character found
						characterindex = i;
					}
				}
				if (characterindex != -1) {
					//character found 
					Party.RemoveAt(characterindex);
					EscapingCharacter->Destroy();
					return true;
				}
				else {
					//error!
					UE_LOG(LogTemp, Warning, TEXT("Character tried to escape but doesn't exist in party"));
					return false;
				};
			};
		}
		return false;
	};
}
bool ACombatManager::GetChance(int32 min, int32 max, int32 boundary)
{
	int32 tempgenerated = FMath::RandRange(min, max);
	if (tempgenerated <= boundary) {
		//is successful
		return true;
	}
	else {
		return false;
	}
}
