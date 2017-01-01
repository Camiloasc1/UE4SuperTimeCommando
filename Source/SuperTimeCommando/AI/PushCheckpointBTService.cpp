// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "PushCheckpointBTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "../ActorHistory.h"

UPushCheckpointBTService::UPushCheckpointBTService()
{
	NodeName = "Push Checkpoint";
}

FString UPushCheckpointBTService::GetStaticDescription() const
{
	return "Push a Checkpoint in the ActorHistory";
}

void UPushCheckpointBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	AIController->GetActorHistory()->PushCheckpoint(Blackboard->GetValueAsInt("TargetIndex"));
}
