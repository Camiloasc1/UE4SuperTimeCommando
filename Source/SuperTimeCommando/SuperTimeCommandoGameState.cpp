// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "SuperTimeCommandoGameState.h"


bool ASuperTimeCommandoGameState::IsTimeBackward() const
{
	return bIsTimeBackward;
}

void ASuperTimeCommandoGameState::SetTimeBackward(bool Value)
{
	bIsTimeBackward = Value;
	TimePivot = bIsTimeBackward ? GetWorld()->GetTimeSeconds() : 0;
}
