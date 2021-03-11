// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"
#include "PlayerCharacter.h"

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
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	if(player)
	{
		PlayerCharacter = player;
	}else
	{
		UE_LOG(LogTemp,Fatal,TEXT("Player Character not assignable, crashes imminent."))
	}
	
}

// Called every frame
void ACombatManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ACombatManager::InitialiseCombat()
{
	//combine the enemy and player arrays into a turn order array using a mergesort function
	CreateTurnOrder();
	InCombat = true;
	SelectedTarget = EnemyParty[0];
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
}
void ACombatManager::CreateTurnOrder() {
	if (PlayerCharacter->OtherPartyMembers.Num() > 0) {
		BattleOrder.Append(PlayerCharacter->OtherPartyMembers);
	}
	BattleOrder.Append(EnemyParty);
	BattleOrder.Add(PlayerCharacter);
	BattleOrder.Sort([](ABaseCharacter& a, ABaseCharacter& b) {return a.CharacterStats.Speed < b.CharacterStats.Speed; });
}
void ACombatManager::GenerateEnemyActions() {
	//TODO - make enemy smort
	for (int i = 0; i < EnemyParty.Num(); i++) {
		//pick a random active action that the enemy has available
		EnemyParty[i]->ChosenAction = EnemyParty[i]->ActiveActions[FMath ::RandRange(0, 3)];
	}
}

void ACombatManager::EnterRhythmPhase() {
	//
	for (int i = 0; i < BattleOrder.Num() - 1; i++) {
		switch (BattleOrder[i]->ChosenAction.Type)
		{
		case 0:
			//basicattack
			//this pattern is the same for all characters
			Button1Array.Add({
				{0,0,0,Crotchet},
				false,
				BattleOrder[i]
			});
			Button1Array.Add({
				{0,1,0,Crotchet},
				true,
				BattleOrder[i]
			});
			break;
		case 1:
			//basicdefend
			//this pattern is the same for all characters
			Button1Array.Add({
				{0,0,0,Breve},
				true,
				BattleOrder[i]
			});
			break;
		case 2:
			//Item
			//TODO - implement once items are fully functional
			break;
		case 3:
			//Ability
			for (int j = 0; j < BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern.Num() - 1; j++) {
				switch (BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j].ButtonIndex) 
				{
				case 0:
					//square or x
					if (j == BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern.Num() - 1) {
						Button1Array.Add({
							BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j],
							true,
							BattleOrder[i]
							});
					}
					else {
						Button1Array.Add({
							BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j],
							false,
							BattleOrder[i]
							});
					}
					break;
				case 1:
					//triangle or y
					if (j == BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern.Num() - 1) {
						Button2Array.Add({
							BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j],
							true,
							BattleOrder[i]
							});
					}
					else {
						Button2Array.Add({
							BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j],
							false,
							BattleOrder[i]
							});
					}
					break;
				case 2:
					//circle or a
					if (j == BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern.Num() - 1) {
						Button3Array.Add({
							BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j],
							true,
							BattleOrder[i]
							});
					}
					else {
						Button3Array.Add({
							BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j],
							false,
							BattleOrder[i]
							});
					}
					break;
				case 3:
					//cross or b
					if (j == BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern.Num() - 1) {
						Button4Array.Add({
							BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j],
							true,
							BattleOrder[i]
							});
					}
					else {
						Button4Array.Add({
							BattleOrder[i]->Abilities[BattleOrder[i]->ChosenAction.index].NotePattern[j],
							false,
							BattleOrder[i]
							});
					}
					break;
				default:
					//this should never happen
					break;
				}
			};
			break;
		default:
			break;
		};
		//put in a bars rest between patterns
		
		//Start from next bar

	}
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
