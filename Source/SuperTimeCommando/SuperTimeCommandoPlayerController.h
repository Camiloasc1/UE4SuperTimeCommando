// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "SuperTimeCommandoPlayerController.generated.h"

UCLASS()
class ASuperTimeCommandoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class UActorHistory* ActorHistory;

public:
	ASuperTimeCommandoPlayerController();

	void BeginPlay() override;

protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void OnReverseTimePressed();
	void OnReverseTimeReleased();

	void MoveForward(float Value);
	void MoveRight(float Value);

private:
	class ASuperTimeCommandoGameState* GameState;
	bool bHasMoved;
};
