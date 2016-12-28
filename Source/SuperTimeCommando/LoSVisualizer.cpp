// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "LoSVisualizer.h"
#include "ProceduralMeshComponent.h"
#include "LoSObstacle.h"
#include "Util.h"


// Sets default values
ALoSVisualizer::ALoSVisualizer()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(MaxDistance);

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));

	RootComponent = Sphere;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALoSVisualizer::BeginPlay()
{
	Super::BeginPlay();

	UpdateSphereRadius();
}

// Called every frame
void ALoSVisualizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Forward3D = GetActorForwardVector();
	FVector2D Forward2D = FVector2D(Forward3D.X, Forward3D.Y);
	FVector Location3D = GetActorLocation();
	FVector2D Location2D = FVector2D(Location3D.X, Location3D.Y);

	TArray<FVector2D> Corners;
	TArray<AActor*> OverlappingActors;
	Sphere->GetOverlappingActors(OverlappingActors, ALoSObstacle::StaticClass());
	for (const auto& Actor : OverlappingActors)
	{
		ALoSObstacle* Obstacle = Cast<ALoSObstacle>(Actor);
		for (const auto& Corner : Obstacle->GetCorners())
		{
			FVector2D V = Corner - Location2D;
			V.Normalize();
			Corners.Add(V);
		}
	}

	// Take just the corners inside the FoV
	Corners = Corners.FilterByPredicate([&](const FVector2D& A)
		{
			return FUtil::Angle2D(Forward2D, A) <= FoV;
		});

	// Sort by the angle
	Corners.HeapSort([&](const FVector2D& A, const FVector2D& B)
		{
			return FUtil::SignedAngle2D(Forward2D, A) < FUtil::SignedAngle2D(Forward2D, B);
		});

	for (const auto& V : Corners)
	{
		UE_LOG(LogActor, Warning, TEXT("U: %f A: %f F: %s V: %s"), FUtil::Angle2D(Forward2D, V), FUtil::SignedAngle2D(Forward2D, V), *Forward2D.ToString(), *V.ToString());
	}

	TArray<FVector> Vertices;

	Vertices.Add(GetActorLocation() + FVector(0, 0, 0));
	Vertices.Add(GetActorLocation() + FVector(0, 100, 0));
	Vertices.Add(GetActorLocation() + FVector(100, 0, 0));

	TArray<int32> Triangles;
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	TArray<FVector> Normals;
	Normals.Init(FVector(0.f, 0.f, 1.f), Vertices.Num());

	TArray<FVector2D> UV0;
	UV0.Init(FVector2D(0.f, 0.f), Vertices.Num());

	TArray<FColor> VertexColors;
	VertexColors.Init(FColor(255, 0, 0), Vertices.Num());

	TArray<FProcMeshTangent> Tangents;
	Tangents.Init(FProcMeshTangent(), Vertices.Num());

	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, false);
}

#if WITH_EDITOR
void ALoSVisualizer::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//Get the name of the property that was changed
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	// We test using GET_MEMBER_NAME_CHECKED so that if someone changes the property name
	// in the future this will fail to compile and we can update it.
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ALoSVisualizer, MaxDistance))
	{
		UpdateSphereRadius();
	}
}
#endif

void ALoSVisualizer::UpdateSphereRadius()
{
	Sphere->SetSphereRadius(MaxDistance, true);
}
