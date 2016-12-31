// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "TimeDirectionBTDecorator.h"
#include "SuperTimeCommandoGameState.h"


UTimeDirectionBTDecorator::UTimeDirectionBTDecorator()
{
	NodeName = "Is Time Backward?";
}

bool UTimeDirectionBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ASuperTimeCommandoGameState* GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();

	return GameState->IsTimeBackward();
}
