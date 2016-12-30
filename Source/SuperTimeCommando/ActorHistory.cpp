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

	// ...

	UE_LOG(LogTemp, Warning, TEXT("Bind"));

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
	if (HasOwnerPawn())
	{
		Checkpoints.Push(FCheckpoint(CheckpointType, GetWorld()->GetTimeSeconds(), GetOwnerPawn()->GetActorLocation()));
	}
}

void UActorHistory::OnTimeBeginBackward()
{
}

void UActorHistory::OnTimeEndBackward()
{
	ASuperTimeCommandoGameState* GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();
	for (auto& Checkpoint : Checkpoints)
	{
		Checkpoint.Time += GetWorld()->GetTimeSeconds() - GameState->GetTimePivot();
	}
}

bool UActorHistory::HasOwnerPawn() const
{
	return GetOwnerPawn() != nullptr;
}

APawn* UActorHistory::GetOwnerPawn() const
{
	AActor* Owner = GetOwner();
	if (Owner->IsA(APlayerController::StaticClass()))
	{
		return Cast<APlayerController>(Owner)->GetPawn();
	}
	if (Owner->IsA(AAIController::StaticClass()))
	{
		return Cast<AAIController>(Owner)->GetPawn();
	}
	return nullptr;
}
