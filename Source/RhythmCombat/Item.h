// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Item.generated.h"
/**
 * 
 */

class UInventory;

UCLASS(Blueprintable)
class RHYTHMCOMBAT_API UItem : public UObject
{
public:
	//constructor and deconstructor
	UItem();
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
    	int32 Itemid;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* Image2D;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FString> Tags;
	UPROPERTY(BlueprintReadOnly)
		UInventory* ContainedIn;
	//TODO: Add Combat Relevant stuff like 
//Overridable Functions
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
		bool Use(AActor* Instigator, AActor* UsedOn, bool& ShouldDelete);
        bool Use_Implementation(AActor* Instigator, AActor* UsedOn, bool& ShouldDelete);
//Dynamic properties
	UPROPERTY(BlueprintReadWrite)
		int32 Quantity;

//Getters
	
		
};
