// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
#include "Structs.h"
#include "CombatManager.h"
#include "RhythmCombatCharacter.generated.h"


UCLASS(config=Game)
class ARhythmCombatCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ARhythmCombatCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ACombatManager* CombatManagerRef;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	virtual void Tick(float DeltaTime) override;
	virtual void BattleAction1();
	virtual void BattleAction2();
	virtual void BattleAction3();
	virtual void BattleAction4();
	virtual void NavigateUp();
	virtual void NavigateDown();
};

