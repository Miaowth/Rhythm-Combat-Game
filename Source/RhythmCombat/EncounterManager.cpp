// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AEncounterManager::AEncounterManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
ATargetPoint* AEncounterManager::GetRandomSpawnpoint() {

	auto index = FMath::RandRange(0, (SpawnPoints.Num() - 1));

	return Cast<ATargetPoint>(SpawnPoints[index]);
}
// Called when the game starts or when spawned
void AEncounterManager::BeginPlay()
{
	Super::BeginPlay();
	//gets all target points (places an encounter can be spawned)
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), SpawnPoints);

	if (EncounterArray.Num() < EncounterMinQuantity) {
		//temporary variable
		TArray<FEnemyArrayWrapper> AllEncounters;
		
		//make x number of encounters where x is the difference between the minimum number and how many currently exist
		for (int32 i = EncounterArray.Num(); i < EncounterMinQuantity; i++) {

			TArray<FEnemyGenerationStats> SingleEncounter;
			//create a random number of enemies for the encounter between 1 and area max
			for (int32 j = 0; j < FMath::RandRange(1, EncounterMaxEnemies - 1); j++) {

				//TODO - make generated based on class
				FCharacterStats TempEnemyStats = {1,2,3,4,5,6,7,8,9};
				int32 TempLevel = FMath::RandRange(LevelMin, LevelMax);
				TSubclassOf<class AActor> TempClass = PossibleEnemyClasses[FMath::RandRange(0, PossibleEnemyClasses.Num() - 1)];

				FEnemyGenerationStats temp = {
					TempLevel,
					TempClass,
					TempEnemyStats
				};
				SingleEncounter.Add(temp);
			}
			//wrap up encounter in FEnemyArrayWrapper and add to encounter array
			ATargetPoint* EncounterTempPos = GetRandomSpawnpoint();
			FVector EncounterTempVector = EncounterTempPos->GetActorLocation();
			FEnemyArrayWrapper EnemyGenTemp = { SingleEncounter, EncounterTempPos, EncounterTempVector, true };
			AllEncounters.Add(EnemyGenTemp);

		};
		//add all generated encounters to EncounterArray
		EncounterArray.Append(AllEncounters);
		for (int32 i = 0; i < EncounterArray.Num(); i++) {
			FActorSpawnParameters TempSpawnParam;
			//TSubclassOf<AEncounter> TempSubClass = AEncounter->GetClass();
			AEncounter* TempStorage = GetWorld()->SpawnActor<AEncounter>(AEncounter::StaticClass(), EncounterArray[i].CurrentPos, FRotator(0.0f), TempSpawnParam);
		};
	}
}

// Called every frame
void AEncounterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEncounterManager::BeginCombat(AActor* StartedEncounter)
{
	//this is where we need to pause all other encounters movement, hide their meshes
	//update camera, spawn in all enemies and player party members
	int32 StartedEncounterIndex;

	for (int32 i = 0; i < EncounterArray.Num(); i++) {
		if (EncounterArray[i].CurrentPos == StartedEncounter->GetActorLocation()) {
			//do stuff
			StartedEncounterIndex = i;
		}
		else {
			EncounterArray[i].CanMove = false;
			//set encounter mesh to invisible
		}
	}

}


