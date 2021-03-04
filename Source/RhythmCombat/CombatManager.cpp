// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "CombatManager.h"

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
	MergeSortTurnOrder(BattleOrder, 0, BattleOrder.Num() - 1);
}

void ACombatManager::MergeSortTurnOrder(TArray<ABaseCharacter*> arr, int32 l, int32 r) {
	//if (l >= r) {
	//	return;//returns recursively
	//}
	
	if (l < r) {
		int m = l + (r - 1) / 2;
		MergeSortTurnOrder(arr, l, m);
		MergeSortTurnOrder(arr, m + 1, r);
		Merge(arr, l, m, r);
	}
};
void ACombatManager::Merge(TArray<ABaseCharacter*> arr, int32 l, int32 m, int32 r) {
	int32 n1 = m - l + 1;
	int32 n2 = r - m;
	// Create temp arrays
	TArray<ABaseCharacter*> L, R;

	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++) { L.Add(arr[l + i]); }
	for (int j = 0; j < n2; j++) { R.Add(arr[m + 1 + j]); }
		

	// Merge the temp arrays back into arr[l..r]
	// Initial index of each array
	int i = 0;
	int j = 0;
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i]->CharacterStats.Speed >= R[j]->CharacterStats.Speed) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	// Copy the remaining elements of L[], if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	// Copy the remaining elements of R[], if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}


}

void ACombatManager::GenerateEnemyActions() {
	//TODO - make enemy smort
	for (int i = 0; i < EnemyParty.Num(); i++) {
		//pick a random active action that the enemy has available
		EnemyParty[i]->ChosenAction = EnemyParty[i]->ActiveActions[FMath ::RandRange(0, 3)];
	}
}



//pretty sure these are defunct but oh well
void ACombatManager::BasicAttack(ABaseCharacter* AttackingActor, ABaseCharacter* DefendingActor)
{
	//TODO - fix
	DefendingActor->CharacterStats.HealthPoints -= AttackingActor->CharacterStats.AttackPower;
	if (DefendingActor->CharacterStats.HealthPoints <= 0) {
		//DefendingActor Dies
		DefendingActor->CharacterStats.HealthPoints = 0;
	}
}
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
