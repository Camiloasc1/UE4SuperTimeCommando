// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "LoSVisualizer.h"
#include "ProceduralMeshComponent.h"
#include "LoSObstacle.h"
#include "Util/Util.h"


// Sets default values
ULoSVisualizer::ULoSVisualizer()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(MaxDistance);
	Sphere->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	ProceduralMesh->CastShadow = false;
	ProceduralMesh->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ULoSVisualizer::BeginPlay()
{
	Super::BeginPlay();

	UpdateSphereRadius();
	SetState(Normal);
}

// Called every frame
void ULoSVisualizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateProceduralMesh();
	// Fix the rotation error
	SetRelativeRotation(FRotator(0, -GetOwner()->GetActorRotation().Yaw, 0));
}

#if WITH_EDITOR
void ULoSVisualizer::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//Get the name of the property that was changed
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	// We test using GET_MEMBER_NAME_CHECKED so that if someone changes the property name
	// in the future this will fail to compile and we can update it.
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ULoSVisualizer, MaxDistance))
	{
		UpdateSphereRadius();
	}
}
#endif

void ULoSVisualizer::SetState(LoSVisualizerState State)
{
	switch (State)
	{
		case Normal:
		{
			ProceduralMesh->SetMaterial(0, MaterialNormal);
			break;
		}
		case Warning:
		{
			ProceduralMesh->SetMaterial(0, MaterialWarning);
			break;
		}
		case Danger:
		{
			ProceduralMesh->SetMaterial(0, MaterialDanger);
			break;
		}
	}
}

void ULoSVisualizer::UpdateSphereRadius()
{
	Sphere->SetSphereRadius(MaxDistance, true);
}

void ULoSVisualizer::CalculateCorners(TArray<FVector2D>& OutCorners)
{
	FVector Forward = GetOwner()->GetActorForwardVector();
	FVector2D Forward2D = FVector2D(Forward.X, Forward.Y);
	FVector Location = GetOwner()->GetActorLocation();
	FVector2D Location2D = FVector2D(Location.X, Location.Y);

	OutCorners.Empty();
	TArray<AActor*> OverlappingActors;
	Sphere->GetOverlappingActors(OverlappingActors, ALoSObstacle::StaticClass());
	for (const auto& Actor : OverlappingActors)
	{
		ALoSObstacle* Obstacle = Cast<ALoSObstacle>(Actor);
		for (const auto& Corner : Obstacle->GetCorners())
		{
			FVector2D V = Corner - Location2D;
			OutCorners.Add(V);
		}
	}

	// Take just the corners inside the FoV
	OutCorners = OutCorners.FilterByPredicate([&](const FVector2D& A)
		{
			return GUtil::Angle2D(Forward2D, A) <= FoV;
		});

	// Add a small tolerance arround the corners
	int32 Count = OutCorners.Num();
	for (int32 i = 0; i < Count; ++i)
	{
		OutCorners.Add(OutCorners[i].GetRotated(-Delta) * MaxDistance);
		OutCorners.Add(OutCorners[i].GetRotated(Delta) * MaxDistance);
	}

	// Add the FoV limits
	OutCorners.Add(Forward2D.GetRotated(FoV) * MaxDistance);
	OutCorners.Add(Forward2D.GetRotated(-FoV) * MaxDistance);

	// Add detail steps
	float angle = -FoV;
	for (int8 i = 0; i < Segments; ++i)
	{
		angle += 2 * FoV / (Segments + 1);
		OutCorners.Add(Forward2D.GetRotated(angle) * MaxDistance);
	}

	// Sort by the angle
	OutCorners.HeapSort([&](const FVector2D& A, const FVector2D& B)
		{
			return GUtil::SignedAngle2D(Forward2D, A) < GUtil::SignedAngle2D(Forward2D, B);
		});
}

void ULoSVisualizer::UpdateProceduralMesh()
{
	TArray<FVector2D> Corners;
	FVector Location = GetOwner()->GetActorLocation();

	CalculateCorners(Corners);

	TArray<FVector> Vertices;
	Vertices.Add(FVector(0, 0, 0));
	for (const auto& Corner : Corners)
	{
		FVector V = FVector(Corner.X, Corner.Y, 0).GetClampedToMaxSize2D(MaxDistance);

		FHitResult HitResult(ForceInit);

		FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams();

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Location, Location + V, ECC_Visibility, CollisionQueryParams))
		{
			Vertices.Add(HitResult.ImpactPoint - Location);
		}
		else
		{
			Vertices.Add(V);
		}
	}

	TArray<int32> Triangles;
	for (int32 i = 0; i < Vertices.Num() - 1; ++i)
	{
		Triangles.Add(0);
		Triangles.Add(i + 2); // In order to get the correct normals put this first
		Triangles.Add(i + 1);
	}

	TArray<FVector> Normals;
	Normals.Init(FVector(0.f, 0.f, 1.f), Vertices.Num());

	TArray<FVector2D> UV0;
	UV0.Init(FVector2D(0.f, 0.f), Vertices.Num());

	TArray<FColor> VertexColors;
	VertexColors.Init(FColor(255, 255, 255), Vertices.Num());

	TArray<FProcMeshTangent> Tangents;
	Tangents.Init(FProcMeshTangent(), Vertices.Num());

	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, false);
}
