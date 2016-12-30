// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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
	UFUNCTION(BlueprintCallable, Category = "Actor History")
	void PushSpawn();
	UFUNCTION(BlueprintCallable, Category = "Actor History")
	void PushDeath();
	UFUNCTION(BlueprintCallable, Category = "Actor History")
	void PushCheckpoint();

	UFUNCTION(BlueprintCallable, Category = "Actor History")
	void PopCheckpoint();

protected:
	UFUNCTION(BlueprintCallable, Category = "Actor History")
	void Push(ECheckpointType CheckpointType);

private:
	APawn* GetOwnerPawn() const;
};
