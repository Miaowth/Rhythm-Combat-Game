// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterManager.h"
#include "EnemyCharacter.h"
#include "../../../UE_4.25/Engine/Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AEncounterManager::AEncounterManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//This is how to give an actor a root component.
	MyRootComponent->SetupAttachment(RootComponent);
}
ATargetPoint* AEncounterManager::GetRandomSpawnpoint() {

	auto index = FMath::RandRange(0, (SpawnPoints.Num() - 1));

	return Cast<ATargetPoint>(SpawnPoints[index]);
}
// Called when the game starts or when spawned
void AEncounterManager::BeginPlay()
{
	Super::BeginPlay();
	//gets all target points with Encounter tag(places an encounter can be spawned)
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), SpawnPoints);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Encounter")), SpawnPoints);
	//set path to find mesh object
	//TODO - make this neater

	if (EncounterArray.Num() < EncounterMinQuantity) {
	
		//make x number of encounters where x is the difference between the minimum number and how many currently exist
		for (int32 i = EncounterArray.Num(); i < EncounterMinQuantity; i++) {

			TArray<FEnemyGenerationStats> EncounterEnemies;
			//create a random number of enemies for the encounter between 1 and area max
			for (int32 j = 0; j < FMath::RandRange(1, EncounterMaxEnemies - 1); j++) {

				//FCharacterStats TempEnemyStats = {1,2,3,4,5,6,7,8,9};
				int32 TempLevel = FMath::RandRange(LevelMin, LevelMax);
				TSubclassOf<class AActor> TempClass = PossibleEnemyClasses[FMath::RandRange(0, PossibleEnemyClasses.Num() - 1)];

				FEnemyGenerationStats SingleEnemy = {
					TempLevel,
					TempClass,
					//TempEnemyStats,
					//TempMesh.Object
				};
				EncounterEnemies.Add(SingleEnemy);
			}
			//wrap up encounter in FEnemyArrayWrapper and add to encounter array
			ATargetPoint* EncounterTempPos = GetRandomSpawnpoint();
			FVector EncounterTempVector = EncounterTempPos->GetActorLocation();

			//Spawn a new encounter bp in world
			FActorSpawnParameters TempSpawnParam;
			TempSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			AEncounter* TempStorage = GetWorld()->SpawnActor<AEncounter>(BP_Encounter, EncounterTempVector, FRotator(0.0f), TempSpawnParam);
			
			TempStorage->CanMove = true;
			TempStorage->EnemyStats = EncounterEnemies;
			TempStorage->EncounterManager = this;
			//assign a mesh from one of the enemies in the encounter
			int32 total_enemies = TempStorage->EnemyStats.Num();
			int32 random_mesh_num = FMath::RandRange(0, total_enemies - 1);
			//checks if mesh is valid before attempting assignment
			if (TempStorage->EnemyStats[random_mesh_num].CharacterMesh) {
				TempStorage->EncounterMesh->SetStaticMesh(TempStorage->EnemyStats[random_mesh_num].CharacterMesh);
				TempStorage->EncounterMesh->SetupAttachment(MyRootComponent);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("I don't have a mesh and now I'm sad :("));
			}
			//add reference to new encounter to the encounter manager
			EncounterArray.Add(TempStorage);

		};
	}
}

// Called every frame
void AEncounterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEncounterManager::DisableEncounters(AActor* StartedEncounter)
{
	//this is where we need to pause all other encounters movement, hide their meshes
	int32 StartedEncounterIndex;

	for (int32 i = 0; i < EncounterArray.Num(); i++) {
		if (EncounterArray[i]->GetActorLocation() == StartedEncounter->GetActorLocation()) {
			//do stuff
			StartedEncounterIndex = i;
		}
		else {
			
			UE_LOG(LogTemp, Warning, TEXT("Index"));
			EncounterArray[i]->CanMove = false;
			////set encounter mesh to invisible and turn off collision
			//EncounterArray[i]->EncounterMesh->SetVisibility(false);
			EncounterArray[i]->SetActorEnableCollision(false);
			//EncounterArray[i]->CanMove = false;
		}
	}
	EncounterArray.RemoveAt(StartedEncounterIndex);
	//AEnemyCharacter* TempStorage = GetWorld()->SpawnActor<AEnemyCharacter>(BP_Encounter, EncounterTempVector, FRotator(0.0f), TempSpawnParam);
	//CombatManagerRef->EnemyParty = EncounterArray[StartedEncounterIndex];
}
void AEncounterManager::EnableEncounters()
{
	for (int32 i = 0; i < EncounterArray.Num(); i++) {
		EncounterArray[i]->EncounterMesh->SetVisibility(true);
		EncounterArray[i]->SetActorEnableCollision(true);
		EncounterArray[i]->CanMove = false;
	}
}


