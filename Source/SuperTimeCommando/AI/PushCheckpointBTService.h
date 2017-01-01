// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "PushCheckpointBTService.generated.h"

/**
 * 
 */
UCLASS()
class SUPERTIMECOMMANDO_API UPushCheckpointBTService : public UBTService
{
	GENERATED_BODY()
	
public:
	UPushCheckpointBTService();

	FString GetStaticDescription() const override;

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
