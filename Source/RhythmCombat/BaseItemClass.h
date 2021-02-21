// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemClass.generated.h"
/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API UBaseItemClass : public UObject
{
public:
	//constructor and deconstructor
	UBaseItemClass();
	//~BaseItemClass();
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 BuyPrice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SellPrice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Image2D;
};
