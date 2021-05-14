// Fill out your copyright notice in the Description page of Project Settings.




#include "Conductor.h"
#include "RhythmUI_Manager.h"
// Sets default values
AConductor::AConductor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//This is how to give an actor a root component.
	MyRootComponent->SetupAttachment(RootComponent);

	CombatMusicAk = CreateDefaultSubobject<UAkComponent>(TEXT("CppCreatedAKComponent"));
	CombatMusicAk->SetupAttachment(MyRootComponent);

}

// Called when the game starts or when spawned
void AConductor::BeginPlay()
{
	Super::BeginPlay();
	
}

float AConductor::ConvertBeatMapToMS(FMyNote Note, float CurrentBarStart) {
	//converts note position values into ms for combat
	if (Note.NotePosInBar == 1) {
		return (CurrentBarStart);
	}
	else {
		switch (Note.TypeOfNote) {
		case Breve:
			//if (BeatLength * 8 * Note.NotePosInBar > BarDuration) {
			//	//note mapping has gone wrong
			//}
			return (CurrentBarStart + (BeatLength * 8 * Note.NotePosInBar));
		case SemiBreve:
			return (CurrentBarStart + (BeatLength * 4 * Note.NotePosInBar));
		case Minim:
			return (CurrentBarStart + (BeatLength * 2 * Note.NotePosInBar));
		case Crotchet:
			return (CurrentBarStart + (BeatLength * Note.NotePosInBar));
		case Quaver:
			return (CurrentBarStart + (BeatLength * 0.5 * Note.NotePosInBar));
		case SemiQuaver:
			return (CurrentBarStart + (BeatLength * 0.25 * Note.NotePosInBar));
		}
	}
	//for errors
	return 0.0f;
}

void AConductor::UpdateRhythmUI(float DeltaTime) {

};

void AConductor::EndCombat_Implementation()
{
	// Logic needed when blueprints don't implement the event. Can be empty.
}

void AConductor::BeginCombat_Implementation()
{
	// Logic needed when blueprints don't implement the event. Can be empty.
}
void AConductor::UpdatePhaseUI_Implementation() {

}
void AConductor::RemoveUI(bool IsTopTrack) {
	if (IsTopTrack) {
		RhythmUIManagerRef->TopTrackNoteArray[0]->Destroy();
		RhythmUIManagerRef->TopTrackNoteArray.RemoveAt(0);
	}
	else {
		RhythmUIManagerRef->BottomTrackNoteArray[0]->Destroy();
		RhythmUIManagerRef->BottomTrackNoteArray.RemoveAt(0);
	};
	
}

// Called every frame
void AConductor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

