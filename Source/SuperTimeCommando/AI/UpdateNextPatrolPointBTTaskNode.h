// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "UpdateNextPatrolPointBTTaskNode.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API UUpdateNextPatrolPointBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUpdateNextPatrolPointBTTaskNode();
	FString GetStaticDescription() const override;

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
