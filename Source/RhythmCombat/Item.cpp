// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
	Tags.Add("All");
}

bool UItem::Use_Implementation(AActor* Instigator, AActor* UsedOn, bool& ShouldDelete)
{
	Quantity--;
	if(Quantity <= 0)
	{
		ShouldDelete = true;
	}
	return true;
}

//UBaseItemClass::~UBaseItemClass()
//{
//}
