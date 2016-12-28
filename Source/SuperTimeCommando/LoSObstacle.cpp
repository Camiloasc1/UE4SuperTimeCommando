// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "LoSObstacle.h"


// Sets default values
ALoSObstacle::ALoSObstacle()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALoSObstacle::BeginPlay()
{
	Super::BeginPlay();

	if (Corners.Num() == 0)
	{
		UpdateCorners();
	}
}

// Called every frame
void ALoSObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Calculates the corners based on the actor's bounds
void ALoSObstacle::UpdateCorners()
{
	FVector Orgin;
	FVector BoxExtent;
	GetActorBounds(false, Orgin, BoxExtent);
	/*FString CoordinateString = FString::Printf(TEXT("Character Position is %s"), *Orgin.ToCompactString());
	UE_LOG(LogActor, Warning, TEXT("%s"), *CoordinateString);
	CoordinateString = FString::Printf(TEXT("Bounds Extent is %s"), *BoxExtent.ToCompactString());
	UE_LOG(LogActor, Warning, TEXT("%s"), *CoordinateString);*/
	Corners.Empty();
	Corners.Add(FVector2D(Orgin.X + BoxExtent.X, Orgin.Y + BoxExtent.Y));
	Corners.Add(FVector2D(Orgin.X + BoxExtent.X, Orgin.Y - BoxExtent.Y));
	Corners.Add(FVector2D(Orgin.X - BoxExtent.X, Orgin.Y + BoxExtent.Y));
	Corners.Add(FVector2D(Orgin.X - BoxExtent.X, Orgin.Y - BoxExtent.Y));
}
