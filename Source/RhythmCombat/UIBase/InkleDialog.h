// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Story.h"
#include "Blueprint/UserWidget.h"
#include "InkleDialog.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API UInkleDialog : public UUserWidget
{
	GENERATED_BODY()
public:
	//UPROPERTY(BlueprintReadOnly)
	//UStory* CurrentStory;
	UPROPERTY(BlueprintReadOnly)
	FString TextToDisplay;
	UPROPERTY(BlueprintReadOnly)
	FString Speaker;
	UPROPERTY(BlueprintReadWrite)
	float BaseTickTime;
	UPROPERTY(BlueprintReadWrite)
	float CurTickTime;
	UPROPERTY(BlueprintReadWrite)
	bool IsTextTicking;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void OnTextTick();

	void OnTextTickTerminated();

	void OnCmdReached();

	void OnAdvance();

	void OnStartStory();

	void OnChoiceReached();

	void OnChoiceChosen();
private:
	UPROPERTY()
	int32 charNo = -1;
	//TCHAR& CurChar;
	//TCHAR& PrevChar;
	//TCHAR& NextChar;
	float TickTimer;
};
