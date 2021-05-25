// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD_BattleUI_Phase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RHYTHMCOMBAT_API UHUD_BattleUI_Phase : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent)
		void UpdateUI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();

public:
	// Called every frame
	virtual void Tick(float DeltaTime);

};
