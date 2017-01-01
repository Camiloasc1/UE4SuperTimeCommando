// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "PopCheckpointBTTaskNode.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API UPopCheckpointBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPopCheckpointBTTaskNode();
	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
