// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "SuperTimeCommandoGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimeBeginBackwardSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimeEndBackwardSignature);

UCLASS()

class SUPERTIMECOMMANDO_API ASuperTimeCommandoGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	// Event called when the time starts to go back
	UPROPERTY(BlueprintAssignable, Category = "Game State|Time")
	FTimeBeginBackwardSignature OnTimeBeginBackward;
	// Event called when the time ends to go back
	UPROPERTY(BlueprintAssignable, Category = "Game State|Time")
	FTimeEndBackwardSignature OnTimeEndBackward;

public:
	UFUNCTION(BlueprintCallable, Category = "Game State|Time")
	bool IsTimeBackward() const;
	UFUNCTION(BlueprintCallable, Category = "Game State|Time")
	void SetTimeBackward(bool BIsTimeBackward);
	UFUNCTION(BlueprintCallable, Category = "Game State|Time")
	FORCEINLINE float GetTimePivot() const
	{
		return TimePivot;
	}

	UFUNCTION(BlueprintCallable, Category = "Game State|State")
	void Win();
	UFUNCTION(BlueprintCallable, Category = "Game State|State")
	void Lose();

	UFUNCTION(BlueprintCallable, Category = "Game State|Player Health")
	void AddHit();
	UFUNCTION(BlueprintCallable, Category = "Game State|Player Health")
	void UndoHit();

	UFUNCTION(BlueprintCallable, Category = "Game State|Player Health")
	FORCEINLINE float GetHealt() const
	{
		return 1 - HitCount / 3.;
	}

private:
	// Is the time going back?
	bool bIsTimeBackward;
	// When the time started to go back
	float TimePivot;
	// The hit count
	uint8 HitCount;
};
