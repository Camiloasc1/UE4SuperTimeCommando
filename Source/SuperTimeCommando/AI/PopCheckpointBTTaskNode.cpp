// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "PopCheckpointBTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyAICharacter* AIPawn = Cast<AEnemyAICharacter>(AIController->GetPawn());

	AIController->GetActorHistory()->PopCheckpoint([&](const FCheckpoint& Checkpoint)
		            {
			            AIPawn->SetActorTransform(Checkpoint.Transform);
			            int32 PatrolTarget = (Checkpoint.PatrolTarget - 1) % AIPawn->PatrolPoints.Num();
			            PatrolTarget += PatrolTarget < 0 ? AIPawn->PatrolPoints.Num() : 0;
			            Blackboard->SetValueAsInt("TargetIndex", PatrolTarget);
		            });

	return EBTNodeResult::Succeeded;
}
