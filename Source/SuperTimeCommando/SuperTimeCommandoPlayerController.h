// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "ActorHistory.h"
#include "SuperTimeCommandoPlayerController.generated.h"

UCLASS()
class ASuperTimeCommandoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UActorHistory* ActorHistory;

public:
	ASuperTimeCommandoPlayerController();

	void BeginPlay() override;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void OnReverseTimePressed();
	void OnReverseTimeReleased();

	void MoveForward(float Value);
	void MoveRight(float Value);

private:
	bool bHasMoved;
};
