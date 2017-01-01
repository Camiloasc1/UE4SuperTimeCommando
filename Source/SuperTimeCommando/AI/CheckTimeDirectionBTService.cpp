// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "CheckTimeDirectionBTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SuperTimeCommandoGameState.h"

UCheckTimeDirectionBTService::UCheckTimeDirectionBTService()
{
	NodeName = "Update The Time Direction";
}

FString UCheckTimeDirectionBTService::GetStaticDescription() const
{
	return "Check the time direction";
}

void UCheckTimeDirectionBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	ASuperTimeCommandoGameState* GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();

	Blackboard->SetValueAsBool("IsTimeBackward", GameState->IsTimeBackward());
}
