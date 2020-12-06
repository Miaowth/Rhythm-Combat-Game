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

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), SpawnPoints);

	if (EncounterArray.Num() < EncounterMinQuantity) {

		TArray<FEnemyArrayWrapper> AllEncounters;
		

		for (int32 i = EncounterArray.Num(); i < EncounterMinQuantity; i++) {

			TArray<FEnemyGenerationStats> SingleEncounter;

			for (int32 j = 0; j < FMath::RandRange(1, EncounterMaxEnemies - 1); j++) {

				FCharacterStats TempEnemyStats = {1,2,3,4,5,6,7,8};
				int32 TempLevel = FMath::RandRange(LevelMin, LevelMax);
				TSubclassOf<class AActor> TempClass = PossibleEnemyClasses[FMath::RandRange(0, PossibleEnemyClasses.Num() - 1)];

				FEnemyGenerationStats temp = {
					TempLevel,
					TempClass,
					TempEnemyStats
				};
				SingleEncounter.Add(temp);
			}

			ATargetPoint* EncounterTempVector = GetRandomSpawnpoint();

			FEnemyArrayWrapper EnemyGenTemp = { SingleEncounter, EncounterTempVector };
			AllEncounters.Add(EnemyGenTemp);

		};
		
		EncounterArray.Append(AllEncounters);
	}
}

// Called every frame
void AEncounterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


