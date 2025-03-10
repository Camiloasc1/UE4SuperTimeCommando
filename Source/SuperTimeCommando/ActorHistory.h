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

	FTransform Transform;

	int32 PatrolTarget;

	FORCEINLINE FCheckpoint()
	{
	}

	FCheckpoint(ECheckpointType CheckpointType, float Time, const FTransform& Transform, int32 PatrolTarget)
		: CheckpointType(CheckpointType),
		  Time(Time),
		  Transform(Transform),
		  PatrolTarget(PatrolTarget)
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

UCLASS(ClassGroup = (SuperTimeCommando), meta = (BlueprintSpawnableComponent))
class SUPERTIMECOMMANDO_API UActorHistory : public USceneComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCheckpoint> Checkpoints;

public:
	UActorHistory();

	virtual void BeginPlay() override;

public:
	void PushSpawn();
	void PushDeath();
	void PushCheckpoint();
	void PushCheckpoint(int32 PatrolIndex);

	template <class ACTION_CLASS>
	void PopCheckpoint(const ACTION_CLASS& Action);

protected:
	void Push(ECheckpointType CheckpointType);
	void Push(ECheckpointType CheckpointType, int32 PatrolIndex);

	UFUNCTION()
	void OnTimeBeginBackward();
	UFUNCTION()
	void OnTimeEndBackward();

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
