// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "UpdateNextPatrolPointBTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "EnemyAICharacter.h"

UUpdateNextPatrolPointBTTaskNode::UUpdateNextPatrolPointBTTaskNode()
{
	NodeName = "Update Next Patrol Point";
}

FString UUpdateNextPatrolPointBTTaskNode::GetStaticDescription() const
{
	return TEXT("Updates the next target patrol point");
}

EBTNodeResult::Type UUpdateNextPatrolPointBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyAICharacter* AIPawn = Cast<AEnemyAICharacter>(AIController->GetPawn());

	if (AIPawn->PatrolPoints.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	int32 i = Blackboard->GetValueAsInt("TargetIndex");

	// Next patrol point
	i = ++i % AIPawn->PatrolPoints.Num();

	Blackboard->SetValueAsObject("TargetPatrolPoint", AIPawn->PatrolPoints[i]);
	Blackboard->SetValueAsInt("TargetIndex", i);

	return EBTNodeResult::Succeeded;
}
