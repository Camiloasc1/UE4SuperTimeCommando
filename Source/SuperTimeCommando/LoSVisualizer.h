// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LoSVisualizer.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API ALoSVisualizer : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere;

public:
	// The field of view
	UPROPERTY(EditAnywhere, Category="Sight", meta = (ClampMin = 0, ClampMax = 360, DisplayName = "Field of View"))
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

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void UpdateSphereRadius();
};

class LoSObstacle;
