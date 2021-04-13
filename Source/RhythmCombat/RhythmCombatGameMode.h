// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UIBase/DialogBox.h"

#include "RhythmCombatGameMode.generated.h"

UCLASS(minimalapi)
class ARhythmCombatGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARhythmCombatGameMode();

	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UUserWidget> OverWorldHUDWidget;
	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UUserWidget> GameMenuWidget;
	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UUserWidget> PauseMenuWidget;
	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UUserWidget> DialogBoxWidget;
	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UUserWidget> InkleDialogWidget;
};



