// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = History, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UActorHistory* ActorHistory;

public:
	FORCEINLINE  UActorHistory* GetActorHistory() const
	{
		return ActorHistory;
	}

public:
	AEnemyAIController();
};
