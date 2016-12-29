// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "SuperTimeCommandoGameState.generated.h"

UCLASS()
class SUPERTIMECOMMANDO_API ASuperTimeCommandoGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsTimeBackward;
};
