// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "CheckTimeDirectionBTService.generated.h"

/**
 * 
 */
UCLASS()
class SUPERTIMECOMMANDO_API UCheckTimeDirectionBTService : public UBTService
{
	GENERATED_BODY()

public:
	UCheckTimeDirectionBTService();

	FString GetStaticDescription() const override;

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
