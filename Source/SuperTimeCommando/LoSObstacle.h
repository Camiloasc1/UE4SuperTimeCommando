// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LoSObstacle.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API ALoSObstacle : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

protected:
	// The corners of the actor
	// If empty the corners will be automatically calculated based on the actor's bounds
	UPROPERTY(EditAnywhere, Category = "Obstacle")
	TArray<FVector2D> Corners;

public:
	// Sets default values for this actor's properties
	ALoSObstacle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public:
	// Calculates the corners based on the actor's bounds
	virtual void UpdateCorners();
};
