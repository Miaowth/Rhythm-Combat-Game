// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "Blueprint/UserWidget.h"

AMyHUD::AMyHUD()
{
}

void AMyHUD::BeginPlay()
{
	GameMode = Cast<ARhythmCombatGameMode>(GetWorld()->GetAuthGameMode());

	OverWorldHUDWidget = CreateWidget(GetOwningPlayerController(),GameMode->OverWorldHUDWidget);
	GameMenuWidget = CreateWidget(GetOwningPlayerController(),GameMode->GameMenuWidget);
	PauseMenuWidget = CreateWidget(GetOwningPlayerController(),GameMode->PauseMenuWidget);
	DialogBoxWidget = CreateWidget(GetOwningPlayerController(),GameMode->DialogBoxWidget);

	OverWorldHUDWidget->AddToViewport();
}

bool AMyHUD::ToggleGameMenu()
{
	if(PauseMenuWidget->IsInViewport()||!GameMenuWidget)
	{
		return false;
	}
	if(GameMenuWidget->IsInViewport())
	{
		GameMenuWidget->RemoveFromViewport();
		OverWorldHUDWidget->AddToViewport();
		return false;
	}else
	{
		OverWorldHUDWidget->RemoveFromViewport();
		GameMenuWidget->AddToViewport();
		return true;
	}
}

bool AMyHUD::TogglePauseMenu()
{
	if(GameMenuWidget->IsInViewport()||!PauseMenuWidget)
	{
		return false;
	}
	if(PauseMenuWidget->IsInViewport())
	{
		PauseMenuWidget->RemoveFromViewport();
		OverWorldHUDWidget->AddToViewport();
		return false;
	}else
	{
		OverWorldHUDWidget->RemoveFromViewport();
		PauseMenuWidget->AddToViewport();
		return true;
	}
	
}

void AMyHUD::DisplayDialogBox(FText Text, bool choice, const FDialogBoxDelegate YesChoice, const FDialogBoxDelegate NoChoice)
{
	if(DialogBoxWidget)
	{
		//DialogBoxWidget->InitValues(Text,choice,YesChoice,NoChoice);
		//DialogBoxWidget->AddToViewport();
	}
}
