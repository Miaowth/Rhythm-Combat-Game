// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemClass.h"

UBaseItemClass::UBaseItemClass()
{
}

bool UBaseItemClass::OnUse_Implementation(AActor* Instigator, AActor* UsedOn, bool& ShouldDelete)
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
