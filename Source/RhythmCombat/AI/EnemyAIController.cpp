// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
}

void AEnemyAIController::DecideDesires()
{
}

void AEnemyAIController::DecideMove()
{
	int32 randomMove = FMath::RandRange(0,3);
}
