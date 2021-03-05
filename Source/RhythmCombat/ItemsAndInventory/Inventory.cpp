// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

bool UInventory::AddItemByItemAmt(FItemAmt ItemAmt)
{
	int32 Index;
	UBaseItemClass* Item = GetItemByClassRef(ItemAmt.Item, Index);
	if(Item)
	{
		Item->Quantity += ItemAmt.Quantity;
		return true;
	}
	
	Inventory.Add(NewObject<UBaseItemClass>(ItemAmt.Item));
	return true;
	
}

bool UInventory::AddItemByClass(UBaseItemClass* ItemClass)
{
	int32 Index;
	UBaseItemClass* Item = GetItemByClassRef(ItemClass->StaticClass(), Index);
	if(Item)
	{
		Item->Quantity += ItemClass->Quantity;
		return true;
	}
	
	Inventory.Add(ItemClass);
	return true;
}

UBaseItemClass* UInventory::GetItemByClassRef(TSubclassOf<UBaseItemClass> ItemClass, int32& Index)
{
	for(int i=0; i<Inventory.Num(); i++)
	{
		if(Inventory[i]->GetClass() == ItemClass.DebugAccessRawClassPtr())
		{
			Index = i;
			return Inventory[i];
		}
	}
	return nullptr;
}

bool UInventory::RemoveItem(TSubclassOf<UBaseItemClass> ItemClass)
{
	int32 Index;
	GetItemByClassRef(ItemClass, Index);
	Inventory.RemoveAt(Index, 1, true);
	return true;
}
