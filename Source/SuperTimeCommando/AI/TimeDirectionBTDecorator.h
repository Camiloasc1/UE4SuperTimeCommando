// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "TimeDirectionBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SUPERTIMECOMMANDO_API UTimeDirectionBTDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UTimeDirectionBTDecorator();

protected:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
