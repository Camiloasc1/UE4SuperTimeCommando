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

	UPROPERTY(VisibleAnywhere)
	class UProceduralMeshComponent* ProceduralMesh;

public:
	// The field of view
	UPROPERTY(EditAnywhere, Category="Sight", meta = (ClampMin = 0, ClampMax = 180, DisplayName = "Field of View"))
	float FoV;

	// The maximum sight distance
	UPROPERTY(EditAnywhere, Category = "Sight")
	float MaxDistance;

	// The delta for detailed corners
	UPROPERTY(EditAnywhere, Category = "Sight",meta = (ClampMin = 0.1, ClampMax = 180))
	float Delta;

	// The number of segments used to give more detail to the sight cone
	UPROPERTY(EditAnywhere, Category = "Sight", meta = (ClampMin = 0))
	int8 Segments;

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
	//  Calculate the corners for the sight cone
	virtual void CalculateCorners(TArray<FVector2D>& OutCorners);
	// Generate the sight cone mesh
	virtual void UpdateProceduralMesh();
	// Set the sphere radius as MaxDistance
	virtual void UpdateSphereRadius();
};

class LoSObstacle;
