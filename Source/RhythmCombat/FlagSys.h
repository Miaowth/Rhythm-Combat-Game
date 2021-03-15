// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FlagSys.generated.h"

UENUM(BlueprintType)
enum EFlagType
{
	FlagType_Bool,
	FlagType_Int,
	FlagType_Float,
	FlagType_String
};

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyFlagChanged, FString, FlagName, TEnumAsByte<EFlagType>, FlagType);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBoolFlagChanged, FString, FlagName, bool, FlagResult);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnIntFlagChanged, FString, FlagName, int32, FlagResult);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFloatFlagChanged, FString, FlagName, float, FlagResult);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStringFlagChanged, FString, FlagName, FString, FlagResult);

/**
 * 
 */
UCLASS()
class RHYTHMCOMBAT_API UFlagSys : public UObject
{
	GENERATED_BODY()

private:

	TMap<FString,bool> BoolFlags;
	TMap<FString,int32> IntFlags;
	TMap<FString,float> FloatFlags;
	TMap<FString,FString> StringFlags;

public:
	//Get a Boolean Flag from this Flag System
	UFUNCTION(BlueprintCallable,Category="Flags|Boolean")
	bool GetFlagAsBool(FString FlagName) const;
	//Set a Boolean Flag in this Flag System
	UFUNCTION(BlueprintCallable,Category="Flags|Boolean")
    void SetFlagAsBool(FString FlagName, bool NewValue);

	//Get an Integer Flag from this Flag System
	UFUNCTION(BlueprintCallable,Category="Flags|Integer")
    int32 GetFlagAsInt(FString FlagName) const;
	//Set an Integer Flag in this Flag System
	UFUNCTION(BlueprintCallable,Category="Flags|Integer")
    void SetFlagAsInt(FString FlagName, int32 NewValue);
	//Increment an Integer Flag from this Flag System
	UFUNCTION(BlueprintCallable,Category="Flags|Integer")
    void IncrementFlagAsInt(FString FlagName, int32 Change);

	//Get a Float Flag from this Flag System
	UFUNCTION(BlueprintCallable,Category="Flags|Float")
    float GetFlagAsFloat(FString FlagName) const;
	//Set a Float Flag in this Flag System
	UFUNCTION(BlueprintCallable,Category="Flags|Float")
    void SetFlagAsFloat(FString FlagName, float NewValue);
	//Increment a Float Flag from this Flag System
	UFUNCTION(BlueprintCallable,Category="Flags|Float")
    void IncrementFlagAsFloat(FString FlagName, float Change);

	//Get a String Flag from this Flag System
	UFUNCTION(BlueprintCallable,Category="Flags|String")
    FString GetFlagAsString(FString FlagName) const;
	//Get a String Flag in this Flag System
	UFUNCTION(BlueprintCallable,Category="Flags|String")
    void SetFlagAsString(FString FlagName, FString NewValue);

	UPROPERTY(BlueprintAssignable, Category="Flags")
	FOnAnyFlagChanged OnAnyFlagChanged;
	UPROPERTY(BlueprintAssignable, Category="Flags|Boolean")
	FOnBoolFlagChanged OnBoolFlagChanged;
	UPROPERTY(BlueprintAssignable, Category="Flags|Integer")
	FOnIntFlagChanged OnIntFlagChanged;
	UPROPERTY(BlueprintAssignable, Category="Flags|Float")
	FOnFloatFlagChanged OnFloatFlagChanged;
	UPROPERTY(BlueprintAssignable, Category="Flags|String")
	FOnStringFlagChanged OnStringFlagChanged;
	
};
