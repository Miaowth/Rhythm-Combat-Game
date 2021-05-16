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

	OverWorldHUDWidget->AddToViewport();
}

bool AMyHUD::ToggleGameMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Game"))
	if(!GameMenuWidget)
	{
		if(PauseMenuWidget->IsInViewport())
		{
			return false;
		}	
	}
	if(GameMenuWidget->IsInViewport())
	{
		GameMenuWidget->RemoveFromViewport();
		OverWorldHUDWidget->AddToViewport();
		GetOwningPlayerController()->bShowMouseCursor = false;
		GetWorldSettings()->SetTimeDilation(1.0f);
		bisInMenu = false;
		return false;
	}else
	{
		OverWorldHUDWidget->RemoveFromViewport();
		GameMenuWidget->AddToViewport();
		GetOwningPlayerController()->bShowMouseCursor = true;
		GetWorldSettings()->SetTimeDilation(0.0f);
		bisInMenu = true;
		return true;
	}
}

bool AMyHUD::TogglePauseMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Pause"))
	if(GameMenuWidget->IsInViewport()||!PauseMenuWidget)
	{
		return false;
	}
	if(PauseMenuWidget->IsInViewport())
	{
		PauseMenuWidget->RemoveFromViewport();
		OverWorldHUDWidget->AddToViewport();
		GetOwningPlayerController()->bShowMouseCursor = false;
		GetWorldSettings()->SetTimeDilation(1.0f);
		bisInMenu = false;
		return false;
	}else
	{
		OverWorldHUDWidget->RemoveFromViewport();
		PauseMenuWidget->AddToViewport();
		GetOwningPlayerController()->bShowMouseCursor = true;
		GetWorldSettings()->SetTimeDilation(0.0f);
		bisInMenu = true;
		return true;
	}
	
}

bool AMyHUD::ExitMenu()
{
	if(CustomMenuWidget)
	{
		if(CustomMenuWidget->IsInViewport())
		{
			if(CanCloseCustomMenu)
			{
				CustomMenuWidget->RemoveFromViewport();
				GetOwningPlayerController()->bShowMouseCursor = false;
				GetWorldSettings()->SetTimeDilation(1.0f);
				bisInMenu = false;
				return true;
			}else
			{
				return false;
			}
		}
	}
	
	if(GameMenuWidget)
	{
		if(GameMenuWidget->IsInViewport())
		{
			GameMenuWidget->RemoveFromViewport();
			GetOwningPlayerController()->bShowMouseCursor = false;
			GetWorldSettings()->SetTimeDilation(1.0f);
			bisInMenu = true;
			return true;
		}
	}

	if(PauseMenuWidget)
	{
		if(PauseMenuWidget->IsInViewport())
		{
			PauseMenuWidget->RemoveFromViewport();
			GetOwningPlayerController()->bShowMouseCursor = false;
			GetWorldSettings()->SetTimeDilation(1.0f);
			bisInMenu = true;
			return true;
		}
	}
	return false;
	
}

bool AMyHUD::OpenCustomMenu(class UUserWidget* Widget, bool ClosableByButton)
{
	if(Widget)
	{
		if(!CustomMenuWidget)
		{
			CustomMenuWidget = Widget;
		}
		
		if(!CustomMenuWidget->IsInViewport())
		{
			CustomMenuWidget = Widget;
			CustomMenuWidget->AddToViewport();
			GetOwningPlayerController()->bShowMouseCursor = true;
			GetWorldSettings()->SetTimeDilation(0.0f);
			CanCloseCustomMenu = ClosableByButton;
			bisInMenu = true;
			return true;
		}
	}
	return false;
}

bool AMyHUD::CloseCustomMenu()
{
	if(CustomMenuWidget)
	{
		if(CustomMenuWidget->IsInViewport())
		{
			CustomMenuWidget->RemoveFromViewport();
			GetOwningPlayerController()->bShowMouseCursor = false;
			GetWorldSettings()->SetTimeDilation(1.0f);
			bisInMenu = false;
			return true;
		}
	}
	return false;
}

/*void AMyHUD::DisplayDialogBox(FText Text, bool choice, const FDialogBoxDelegate YesChoice, const FDialogBoxDelegate NoChoice)
{
	if(DialogBoxWidget)
	{
		//DialogBoxWidget->InitValues(Text,choice,YesChoice,NoChoice);
		//DialogBoxWidget->AddToViewport();
	}
}*/
