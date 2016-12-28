// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LoSVisualizer.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API ALoSVisualizer : public AActor
{
	GENERATED_BODY()

public:
	// The field of view
	UPROPERTY(EditAnywhere, Category="Sight")
	float FoV;

	// The maximum sight distance
	UPROPERTY(EditAnywhere, Category = "Sight")
	float MaxDistance;

public:
	// Sets default values for this actor's properties
	ALoSVisualizer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
};
