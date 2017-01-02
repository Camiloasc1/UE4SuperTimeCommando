// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "ActorHistory.h"
#include "AIController.h"

// Sets default values for this component's properties
UActorHistory::UActorHistory()
{
}

// Called when the game starts
void UActorHistory::BeginPlay()
{
	Super::BeginPlay();

	ASuperTimeCommandoGameState* GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();
	GameState->OnTimeBeginBackward.AddDynamic(this, &UActorHistory::OnTimeBeginBackward);
	GameState->OnTimeEndBackward.AddDynamic(this, &UActorHistory::OnTimeEndBackward);
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

void UActorHistory::PushCheckpoint(int32 PatrolIndex)
{
	Push(Checkpoint, PatrolIndex);
}

void UActorHistory::Push(ECheckpointType CheckpointType)
{
	Push(CheckpointType, 0);
}

void UActorHistory::Push(ECheckpointType CheckpointType, int32 PatrolIndex)
{
	APawn* OwnerPawn = GetOwnerPawn();
	if (OwnerPawn != nullptr)
	{
		Checkpoints.Push(FCheckpoint(CheckpointType, GetWorld()->GetTimeSeconds(), OwnerPawn->GetActorTransform(), PatrolIndex));
	}
}

void UActorHistory::OnTimeBeginBackward()
{
}

void UActorHistory::OnTimeEndBackward()
{
	float Delta = GetWorld()->GetTimeSeconds() - GetWorld()->GetGameState<ASuperTimeCommandoGameState>()->GetTimePivot();
	for (auto& Checkpoint : Checkpoints)
	{
		Checkpoint.Time += 2 * Delta;
	}
}

APawn* UActorHistory::GetOwnerPawn() const
{
	AActor* Owner = GetOwner();
	if (Owner->IsA(AController::StaticClass()))
	{
		return Cast<AController>(Owner)->GetPawn();
	}
	return nullptr;
}
