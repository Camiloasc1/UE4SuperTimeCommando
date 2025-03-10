// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "LoSObstacle.h"


// Sets default values
ALoSObstacle::ALoSObstacle()
{
}

// Calculates the corners based on the actor's bounds
TArray<FVector2D> ALoSObstacle::GetCorners() const
{
	TArray<FVector2D> Corners;

	FVector Orgin;
	FVector BoxExtent;
	GetActorBounds(false, Orgin, BoxExtent);

	Corners.Empty();
	Corners.Add(FVector2D(Orgin.X + BoxExtent.X, Orgin.Y + BoxExtent.Y));
	Corners.Add(FVector2D(Orgin.X + BoxExtent.X, Orgin.Y - BoxExtent.Y));
	Corners.Add(FVector2D(Orgin.X - BoxExtent.X, Orgin.Y + BoxExtent.Y));
	Corners.Add(FVector2D(Orgin.X - BoxExtent.X, Orgin.Y - BoxExtent.Y));

	return Corners;
}
