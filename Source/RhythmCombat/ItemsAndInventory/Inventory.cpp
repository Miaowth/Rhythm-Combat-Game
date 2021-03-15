// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

bool UInventory::AddItemByItemAmt(FItemAmt ItemAmt)
{
	int32 Index;
	UItem* Item = GetItemByClassRef(ItemAmt.Item, Index);
	if(Item)
	{
		Item->Quantity += ItemAmt.Quantity;
		return true;
	}
	UItem* NewItem = NewObject<UItem>(ItemAmt.Item->StaticClass());
	NewItem->Quantity = ItemAmt.Quantity;
	Inventory.Add(NewItem);
	OnItemAdded.Broadcast(NewItem);
	return true;
	
}

bool UInventory::AddItemByClass(UItem* ItemClass)
{
	int32 Index;
	UItem* Item = GetItemByClassRef(ItemClass->StaticClass(), Index);
	if(Item)
	{
		Item->Quantity += ItemClass->Quantity;
		return true;
	}
	
	Inventory.Add(ItemClass);
	OnItemAdded.Broadcast(ItemClass);
	return true;
}

UItem* UInventory::GetItemByClassRef(TSubclassOf<UItem> ItemClass, int32& Index)
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

bool UInventory::RemoveItem(TSubclassOf<UItem> ItemClass)
{
	int32 Index;
	GetItemByClassRef(ItemClass, Index);
	Inventory.RemoveAt(Index, 1, true);
	return true;
}

bool UInventory::PayMoney(int32 MoneyPaid, bool BottomOut)
{
	if(BottomOut)
	{
		if(CanPay(MoneyPaid))
		{
			OnMoneyChanged.Broadcast(Money,Money - MoneyPaid);
			Money -= MoneyPaid;
		}else
		{
			OnMoneyChanged.Broadcast(Money,0);
			Money = 0;
		}
		return true;
	}

	if(CanPay(MoneyPaid))
	{
		OnMoneyChanged.Broadcast(Money,Money - MoneyPaid);
		Money -= MoneyPaid;
		return true;
	}
	return false;
}

TArray<UItem*> UInventory::FindItemsByTags(TArray<FString> Tags)
{
	TArray<UItem*> Items;
	for(int x=0;x<Tags.Num();x++)
	{
		FString Tag = Tags[x];
		for(int y=0;y<Inventory.Num();y++)
		{
			UItem* Item = Inventory[y];

			if(Items.Contains(Item) || Item->Quantity == 0)
			{
				continue;
			}

			for(int z=0;z<Item->Tags.Num();z++)
			{
				if(Tag == Item->Tags[z])
				{
					Items.Add(Item);
					break;
				}
			}

		}
	}
	return Items;
}

void UInventory::AddMoney(int32 MoneyPaid)
{
	OnMoneyChanged.Broadcast(Money, Money + MoneyPaid);
	Money += MoneyPaid;
}
