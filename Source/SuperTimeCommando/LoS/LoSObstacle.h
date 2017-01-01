// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LoSObstacle.generated.h"

UCLASS(ClassGroup = (SuperTimeCommando), meta = (BlueprintSpawnableComponent))
class SUPERTIMECOMMANDO_API ULoSObstacle : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ULoSObstacle();

public:
	// Get the corners based on the actor's bounds
	TArray<FVector2D> GetCorners() const;
};
