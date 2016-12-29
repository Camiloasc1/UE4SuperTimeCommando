// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum ECheckpointType
{
	Spawn,
	Die,
	Checkpoint,
};


struct FCheckpoint
{
	ECheckpointType CheckpointType;

	float Time;

	FVector Location;

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

struct FActorHistory
{
	TArray<FCheckpoint> Checkpoints;
};
