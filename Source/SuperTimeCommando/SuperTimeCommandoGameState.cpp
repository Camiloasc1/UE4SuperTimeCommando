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
	if (bIsTimeBackward)
	{
		TimePivot = GetWorld()->GetTimeSeconds();
		OnTimeBeginBackward.Broadcast();
	}
	else
	{
		OnTimeEndBackward.Broadcast();
	}
}

void ASuperTimeCommandoGameState::Win()
{
	OnGameEnd.Broadcast(true);
}

void ASuperTimeCommandoGameState::Lose()
{
	OnGameEnd.Broadcast(false);
}

void ASuperTimeCommandoGameState::AddHit()
{
	if (++HitCount >= 3)
	{
		Lose();
	}
}

void ASuperTimeCommandoGameState::UndoHit()
{
	HitCount--;
	UE_LOG(LogTemp, Warning, TEXT("UndoHit %d"), HitCount);
}
