// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTimeCommando.h"
#include "SuperTimeCommandoGameState.h"


bool ASuperTimeCommandoGameState::IsTimeBackward() const
{
	return bIsTimeBackward;
}

void ASuperTimeCommandoGameState::SetTimeBackward(bool Value)
{
	if (Value == bIsTimeBackward)
	{
		return;
	}

	bIsTimeBackward = Value;
	TimePivot = bIsTimeBackward ? GetWorld()->GetTimeSeconds() : 0;
	if (bIsTimeBackward)
	{
		OnTimeBeginBackward.Broadcast();
	}
	else
	{
		OnTimeEndBackward.Broadcast();
	}
}
