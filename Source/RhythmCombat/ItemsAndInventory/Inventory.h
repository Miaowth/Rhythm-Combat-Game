// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RhythmCombat/Structs.h"
#include "RhythmCombat/Item.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, UItem*, Item);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUsed, UItem*, Item);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoneyChanged, int32, Initial, int32, New);

/**
 * 
 */
UCLASS(BlueprintType)
class RHYTHMCOMBAT_API UInventory : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UItem*> Inventory;
	UPROPERTY()
	int32 Money;
public:
	//Add Item
	UFUNCTION(BlueprintCallable, Category="Inventory|Item")
		bool AddItemByItemAmt(FItemAmt ItemAmt);
	UFUNCTION(BlueprintCallable, Category="Inventory|Item")
		bool AddItemByClass(UItem* ItemClass);
	//Get Item
	UFUNCTION(BlueprintCallable, Category="Inventory|Item")
		UItem* GetItemByClassRef(TSubclassOf<UItem> ItemClass, int32& Index);
		UItem* GetItemByClassRef(TSubclassOf<UItem> ItemClass);
	//Remove Item
	UFUNCTION(BlueprintCallable, Category="Inventory|Item")
		bool RemoveItem(TSubclassOf<UItem> ItemClass);
	//GetMoney
	UFUNCTION(BlueprintPure, Category="Inventory|Money")
		FORCEINLINE int32 GetMoney() const{return Money;};
	//Pay Money
	UFUNCTION(BlueprintCallable, Category="Inventory|Money")
        bool PayMoney(int32 MoneyPaid, bool BottomOut);
	//Can Pay
	UFUNCTION(BlueprintCallable, Category="Inventory|Money")
        FORCEINLINE bool CanPay(int32 MoneyPaid){return Money >= MoneyPaid;};
	//Add Money
	UFUNCTION(BlueprintCallable, Category="Inventory|Money")
        void AddMoney(int32 MoneyPaid);
	//Find Items by tag
	UFUNCTION(BlueprintCallable, Category="Inventory|Item")
		TArray<UItem*> FindItemsByTags(TArray<FString> Tags);
	UFUNCTION(BlueprintCallable, Category="Inventory|Item")
        TArray<UItem*> GetItems(){return Inventory;};
	UFUNCTION(BlueprintCallable, Category="Inventory|Money")
        bool UseItem(TSubclassOf<UItem> Item, AActor* Instigator, AActor* UseOn, bool& ShouldDelete);

	UPROPERTY(BlueprintAssignable, Category="Inventory|Item")
	FOnItemAdded OnItemAdded;
	UPROPERTY(BlueprintAssignable, Category="Inventory|Item")
	FOnItemUsed OnItemUsed;
	UPROPERTY(BlueprintAssignable, Category="Inventory|Money")
	FOnMoneyChanged OnMoneyChanged;
};
