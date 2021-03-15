// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

#include "MyGameInstance.h"

UFlagSys* UMyBlueprintFunctionLibrary::GetGlobalFlagSystem(UWorld* ThisWorld)
{
	if(ThisWorld)
	{
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(ThisWorld->GetGameInstance());
		return GameInstance->FlagSystem;
	}
	return nullptr;
}

UInventory* UMyBlueprintFunctionLibrary::GetPlayerInventory(UWorld* ThisWorld)
{
	if(ThisWorld)
	{
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(ThisWorld->GetGameInstance());
		return GameInstance->PlayerInventory;
	}
	return nullptr;
}

FString UMyBlueprintFunctionLibrary::ZeroBuffer(float Number, int Numbers, int DecimalPlaces)
{
	int RoundedNumber = FMath::FloorToInt(Number);
	float Decimal = 0.0f;
	if (DecimalPlaces > 0)
	{
		Decimal = FMath::RoundToZero(FGenericPlatformMath::Fmod(Number, 1.0f) * (FMath::Pow(10, DecimalPlaces))) / FMath::Pow(10, DecimalPlaces);
		
	}
	FString String = FString::FromInt(RoundedNumber);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, String);
	if (String.Len() < Numbers + 1)
	{
		int toAdd = Numbers - String.Len();
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::FromInt(toAdd));
		for (int x=0;x<toAdd;x++)
		{
			String.InsertAt(0, "0");
			
		}

		FString DecimalString = FString::SanitizeFloat(Decimal, DecimalPlaces);
		DecimalString.RemoveFromStart("0", ESearchCase::IgnoreCase);
		
		String.Append(DecimalString);
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Bad Float");
	}

	return String;
}

FString UMyBlueprintFunctionLibrary::FormatTimeAsMMSS(float Number, int DecimalPlaces)
{
	FString Format = ZeroBuffer(Number / 60, 2, 0);
	Format.Append(":");
	Format.Append(ZeroBuffer(FGenericPlatformMath::Fmod(Number, 60.0f), 2, DecimalPlaces));
	
	return Format;
}
