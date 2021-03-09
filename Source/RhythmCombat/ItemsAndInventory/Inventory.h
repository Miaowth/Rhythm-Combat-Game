// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RhythmCombat/Structs.h"
#include "RhythmCombat/BaseItemClass.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API UInventory : public UObject
{
	GENERATED_BODY()

private:
	TArray<UBaseItemClass*> Inventory;
	int32 Money;
public:
	//Add Item
	UFUNCTION(BlueprintCallable)
		bool AddItemByItemAmt(FItemAmt ItemAmt);
	UFUNCTION(BlueprintCallable)
		bool AddItemByClass(UBaseItemClass* ItemClass);
	//Get Item
	UFUNCTION(BlueprintCallable)
		UBaseItemClass* GetItemByClassRef(TSubclassOf<UBaseItemClass> ItemClass, int32& Index);
	//Remove Item
	UFUNCTION(BlueprintCallable)
		bool RemoveItem(TSubclassOf<UBaseItemClass> ItemClass);
	//GetMoney
	UFUNCTION(BlueprintGetter)
		FORCEINLINE int32 GetMoney() const{return Money;};
	//Pay Money
	UFUNCTION(BlueprintCallable)
        bool PayMoney(int32 MoneyPaid, bool BottomOut);
	//Can Pay
	UFUNCTION(BlueprintCallable)
        FORCEINLINE bool CanPay(int32 MoneyPaid){return Money > MoneyPaid;};
	//Add Money
	UFUNCTION(BlueprintCallable)
        void AddMoney(int32 MoneyPaid){Money += MoneyPaid;};
};
