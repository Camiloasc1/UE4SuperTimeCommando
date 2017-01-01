// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "EnemyAIController.h"
#include "../ActorHistory.h"

AEnemyAIController::AEnemyAIController()
{
	ActorHistory = CreateDefaultSubobject<UActorHistory>(TEXT("ActorHistory"));
	ActorHistory->SetupAttachment(RootComponent);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	ActorHistory->PushSpawn();
}
