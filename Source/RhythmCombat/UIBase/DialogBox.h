// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "DialogBox.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API UDialogBox : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FText DialogText;
	UPROPERTY(BlueprintReadOnly)
	bool bisAChoice;

	UPROPERTY(BlueprintReadWrite)
	UButton* Button1;
	UPROPERTY(BlueprintReadWrite)
	UButton* Button2;
	
	//UFUNCTION(BlueprintCallable)
	//void InitValues(FText Text, bool choice, const FDialogBoxDelegate Yes, const FDialogBoxDelegate No);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ConstructWidget();
	
};
