// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RhythmCombatGameMode.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"




/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API AMyHUD : public AHUD
{
	GENERATED_BODY()
private:
	AMyHUD();
	virtual void BeginPlay() override;
public:
	
	UFUNCTION(BlueprintCallable)
	bool ToggleGameMenu();

	UFUNCTION(BlueprintCallable)
    bool TogglePauseMenu();

	//UFUNCTION(BlueprintCallable)
	//void DisplayDialogBox(FText Text, bool choice, const FDialogBoxDelegate YesChoice, const FDialogBoxDelegate NoChoice);

private:
	UPROPERTY()
	ARhythmCombatGameMode* GameMode;
	//HUD Widgets
	UPROPERTY()
	class UUserWidget* OverWorldHUDWidget;
	UPROPERTY()
	class UUserWidget* GameMenuWidget;
	UPROPERTY()
	class UUserWidget* PauseMenuWidget;
	UPROPERTY()
	class UUserWidget* DialogBoxWidget;
	UPROPERTY()
	class UUserWidget* InkleDialogWidget;
};
