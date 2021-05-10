// Fill out your copyright notice in the Description page of Project Settings.


#include "InkleDialog.h"

void UInkleDialog::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	TickTimer += InDeltaTime;
	if(TickTimer/CurTickTime > 1)
	{
		for(int a=0; a < FMath::Floor(TickTimer/CurTickTime); a++)
		{
			OnTextTick();
		}
		TickTimer = FMath::Fmod(TickTimer,CurTickTime);
	}
}

void UInkleDialog::OnTextTick()
{
/*	
	//Increment the Character Number
	charNo++;
	//Assign the Previous and Current Character values

	if(charNo > 0)
	{
		PrevChar = CurrentStory->CurrentText()[charNo-1];
	}
	CurChar = CurrentStory->CurrentText()[charNo];
	//Determine if we have reached the end of the Text string. Set IsTextTicking to false if true.
	if (charNo+1 == CurrentStory->CurrentText().Len())
	{
		IsTextTicking = false;
	}else
	{
		//NextChar = CurrentStory->CurrentText()[charNo+1];
	}
	//Append Current
	TextToDisplay.AppendChar(CurChar);
	//TODO: Determine if we have reached an inline command, if so skip charNo over it and perform the command
	
	*/
}

void UInkleDialog::OnTextTickTerminated()
{
	
}

void UInkleDialog::OnCmdReached()
{
}

void UInkleDialog::OnAdvance()
{
	TextToDisplay.Empty();
}

void UInkleDialog::OnStartStory()
{
}

void UInkleDialog::OnChoiceReached()
{
}

void UInkleDialog::OnChoiceChosen()
{
}
