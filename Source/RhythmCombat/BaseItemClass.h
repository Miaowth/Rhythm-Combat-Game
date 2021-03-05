// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemClass.generated.h"
/**
 * 
 */
UCLASS(Blueprintable)
class RHYTHMCOMBAT_API UBaseItemClass : public UObject
{
public:
	//constructor and deconstructor
	UBaseItemClass();
	//~BaseItemClass();
	GENERATED_BODY()
public:
//Important static properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 BuyPrice;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 SellPrice;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 MaxStack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* Image2D;
	//TODO: Add Combat Relevant stuff like 
//Overridable Functions
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
		bool OnUse(AActor* Instigator, AActor* UsedOn, bool& ShouldDelete);
        bool OnUse_Implementation(AActor* Instigator, AActor* UsedOn, bool& ShouldDelete);
//Dynamic properties
	UPROPERTY(BlueprintReadWrite)
		int32 Quantity;
		
};
