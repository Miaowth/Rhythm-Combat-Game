// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * The Interface applied to anything that is interactive.
 * Also needs a collider assigned to the "Interactable" Collision Profile
 */
class RHYTHMCOMBAT_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool DoInteract(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FString GetTooltip();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
    FTransform GetInteractControlPoint(AActor* Instigator);
	
};
