// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "LoSVisualizer.generated.h"

UENUM()
enum LoSVisualizerState
{
	Normal,
	Warning,
	Danger,
};

UCLASS(ClassGroup = (SuperTimeCommando), meta = (BlueprintSpawnableComponent))
class SUPERTIMECOMMANDO_API ULoSVisualizer : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Visualizer, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Sphere;

	UPROPERTY(Category = Visualizer, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UProceduralMeshComponent* ProceduralMesh;

public:
	// The field of view
	UPROPERTY(EditAnywhere, Category="Sight", meta = (ClampMin = 0, ClampMax = 180, DisplayName = "Field of View"))
	float FoV;

	// The maximum sight distance
	UPROPERTY(EditAnywhere, Category = "Sight")
	float MaxDistance;

	// The delta for detailed corners
	UPROPERTY(EditAnywhere, Category = "Visualizer",meta = (ClampMin = 0.1, ClampMax = 180))
	float Delta;

	// The number of segments used to give more detail to the sight cone
	UPROPERTY(EditAnywhere, Category = "Visualizer", meta = (ClampMin = 0))
	int8 Segments;

	// The normal material
	UPROPERTY(EditAnywhere, Category = "Visualizer")
	UMaterial* MaterialNormal;

	// The warning material
	UPROPERTY(EditAnywhere, Category = "Visualizer")
	UMaterial* MaterialWarning;

	// The danger material
	UPROPERTY(EditAnywhere, Category = "Visualizer")
	UMaterial* MaterialDanger;

	// The projectile
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class AProjectile> Projectile;

	// The cooldown
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float Cooldown;

public:
	// Sets default values for this actor's properties
	ULoSVisualizer();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	void SetState(LoSVisualizerState NewState);

protected:
	//  Calculate the corners for the sight cone
	virtual void CalculateCorners(TArray<FVector2D>& OutCorners);
	// Generate the sight cone mesh
	virtual void UpdateProceduralMesh();
	// Set the sphere radius as MaxDistance
	virtual void UpdateSphereRadius();
	// Check if player in range and shot
	virtual void TryShot();
	// Shot a projectile to the target position
	virtual void Shot(FVector Target);

	bool HasClearSightOfPoint(FVector& Target) const;

private:
	LoSVisualizerState State;
	float LastShot;
};
