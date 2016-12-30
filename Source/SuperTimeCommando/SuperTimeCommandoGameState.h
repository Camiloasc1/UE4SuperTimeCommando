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

private:
	// Is the time going back?
	bool bIsTimeBackward;
	// When the time started to go back
	float TimePivot;
};
