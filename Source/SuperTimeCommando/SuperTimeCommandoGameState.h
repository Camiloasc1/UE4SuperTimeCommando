// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "SuperTimeCommandoGameState.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API ASuperTimeCommandoGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	bool IsTimeBackward() const;
	void SetTimeBackward(bool BIsTimeBackward);

private:
	// Is the time going back?
	bool bIsTimeBackward;
	// When the time started to go back
	float TimePivot;
};
