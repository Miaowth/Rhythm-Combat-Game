// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

#include "Kismet/GameplayStatics.h"

void AMyGameStateBase::BeginPlay()
{
	//Find the nearest Encounter Manager and make it the current one
	//TODO: Make this less scuffed
	TArray<AActor*> EncounterManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEncounterManager::StaticClass(), EncounterManagers);
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);

	float lowestDist;
	int32 lowestDistIndex = 0;
	for(int i = 0; i<EncounterManagers.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Iterate!!!"));
		AActor* CurEnc = EncounterManagers[i];
		FVector Dist = CurEnc->GetActorLocation() - Character->GetActorLocation();
	
		float size = Dist.Size();
		if (i == 0)
		{
			lowestDist = size;
			lowestDistIndex = i;
		}else
		{
			if(size < lowestDist)
			{
				lowestDist = size;
				lowestDistIndex = i;
			}
		}
	}

	ChangeEncounterManager(Cast<AEncounterManager>(EncounterManagers[lowestDistIndex]));
	
}

void AMyGameStateBase::ChangeEncounterManager(AEncounterManager* NewManager)
{
	if(CurrentEncounterManager)
	{
		if(CurrentEncounterManager != NewManager)
		{
			NewManager->Enable();
			CurrentEncounterManager->Disable();
			CurrentEncounterManager = NewManager;
		}
	}else
	{
		if(NewManager)
		{
			NewManager->Enable();
			CurrentEncounterManager = NewManager;
		}
	}
}
