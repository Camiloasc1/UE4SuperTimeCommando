// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LoSObstacle.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API ALoSObstacle : public AActor
{
	GENERATED_BODY()

public:
	ALoSObstacle();

public:
	// Get the corners based on the actor's bounds
	TArray<FVector2D> GetCorners() const;
};
