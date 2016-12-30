// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "SuperTimeCommandoGameState.h"
#include "ActorHistory.generated.h"

UENUM(BlueprintType)
enum ECheckpointType
{
	Spawn,
	Death,
	Checkpoint,
};

USTRUCT()
struct FCheckpoint
{
	GENERATED_BODY()

		ECheckpointType CheckpointType;

	float Time;

	FVector Location;

	FORCEINLINE FCheckpoint()
	{
	}

	FORCEINLINE FCheckpoint(ECheckpointType CheckpointType, float Time, const FVector& Location)
		: CheckpointType(CheckpointType),
		  Time(Time),
		  Location(Location)
	{
	}

	friend bool operator<(const FCheckpoint& Lhs, const FCheckpoint& Rhs)
	{
		return Lhs.Time < Rhs.Time;
	}

	friend bool operator<=(const FCheckpoint& Lhs, const FCheckpoint& Rhs)
	{
		return !(Rhs < Lhs);
	}

	friend bool operator>(const FCheckpoint& Lhs, const FCheckpoint& Rhs)
	{
		return Rhs < Lhs;
	}

	friend bool operator>=(const FCheckpoint& Lhs, const FCheckpoint& Rhs)
	{
		return !(Lhs < Rhs);
	}
};

UCLASS()

class SUPERTIMECOMMANDO_API UActorHistory : public USceneComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCheckpoint> Checkpoints;

public:
	// Sets default values for this component's properties
	UActorHistory();
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void PushSpawn();
	void PushDeath();
	void PushCheckpoint();

	template <class ACTION_CLASS>
	void PopCheckpoint(const ACTION_CLASS& Action);

protected:
	void Push(ECheckpointType CheckpointType);

private:
	APawn* GetOwnerPawn() const;
};


template <class ACTION_CLASS>
void UActorHistory::PopCheckpoint(const ACTION_CLASS& Action)
{
	if (Checkpoints.Num() > 0 && Checkpoints.Top().CheckpointType == Checkpoint)
	{
		ASuperTimeCommandoGameState* GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();

		// Check if enough time has passed since the pivot
		float CurrentTime = GetWorld()->GetTimeSeconds();
		float CheckpointTime = Checkpoints.Top().Time;
		float PivotTime = GameState->GetTimePivot();
		if (CurrentTime - PivotTime >= PivotTime - CheckpointTime)
		{
			Action(Checkpoints.Pop());
		}
	}
}
