// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "PopCheckpointBTTaskNode.h"
#include "EnemyAIController.h"
#include "EnemyAICharacter.h"
#include "../ActorHistory.h"

UPopCheckpointBTTaskNode::UPopCheckpointBTTaskNode()
{
	NodeName = "Pop Checkpoint";
}

FString UPopCheckpointBTTaskNode::GetStaticDescription() const
{
	return "Pop a Checkpoint from the ActorHistory";
}

EBTNodeResult::Type UPopCheckpointBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyAICharacter* AIPawn = Cast<AEnemyAICharacter>(AIController->GetPawn());

	AIController->GetActorHistory()->PopCheckpoint([&](const FCheckpoint& Checkpoint)
		            {
			            FVector Movement = Checkpoint.Location - AIPawn->GetActorLocation();
			            AIPawn->SetActorLocation(Checkpoint.Location);
		            });

	return EBTNodeResult::Succeeded;
}
