// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "ActorHistory.h"
#include "AIController.h"

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

	ASuperTimeCommandoGameState* GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();
	GameState->OnTimeBeginBackward.AddDynamic(this, &UActorHistory::OnTimeBeginBackward);
	GameState->OnTimeEndBackward.AddDynamic(this, &UActorHistory::OnTimeEndBackward);
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

void UActorHistory::Push(ECheckpointType CheckpointType)
{
	APawn* OwnerPawn = GetOwnerPawn();
	if (OwnerPawn != nullptr)
	{
		Checkpoints.Push(FCheckpoint(CheckpointType, GetWorld()->GetTimeSeconds(), OwnerPawn->GetActorTransform()));
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
		Checkpoint.Time += Delta;
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
