// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"

// Sets default values
ACombatManager::ACombatManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//This is how to give an actor a root component.
	MyRootComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACombatManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
bool ACombatManager::CombatLoop()
{
	//while (true) {
	//	if () {

	//	}
	//	else if () {

	//	}
	//	else {

	//	}
	//}
	return true;
}
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
