// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "ActorHistory.h"

// Sets default values for this component's properties
UActorHistory::UActorHistory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UActorHistory::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UActorHistory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActorHistory::PushSpawn()
{
	Push(Spawn);
}

void UActorHistory::PushDeath()
{
	Push(Death);
}

void UActorHistory::PushCheckpoint()
{
	Push(Checkpoint);
}

void UActorHistory::PopCheckpoint()
{
	if (Checkpoints.Num() > 0 && Checkpoints.Top().CheckpointType == Checkpoint)
	{
		FCheckpoint Checkpoint = Checkpoints.Pop();
		FVector Movement = Checkpoint.Location - GetOwnerPawn()->GetActorLocation();
		GetOwnerPawn()->AddMovementInput(Movement, 1.f);
		// If it is so far then teleport
		if (Movement.Size() > 100)
		{
			GetOwnerPawn()->SetActorLocation(Checkpoint.Location);
		}
	}
}

void UActorHistory::Push(ECheckpointType CheckpointType)
{
	Checkpoints.Push(FCheckpoint(CheckpointType, GetWorld()->GetTimeSeconds(), GetOwnerPawn()->GetActorLocation()));
}

APawn* UActorHistory::GetOwnerPawn() const
{
	return Cast<APlayerController>(GetOwner())->GetPawn();
}
