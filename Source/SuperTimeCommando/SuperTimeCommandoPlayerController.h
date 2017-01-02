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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float FocusOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float AngleDelta;

public:
	ASuperTimeCommandoPlayerController();

	void BeginPlay() override;

protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void OnGameEnd(bool bHasWin);

	UFUNCTION()
	void OnFocusPressed();
	UFUNCTION()
	void OnFocusReleased();

	UFUNCTION()
	void OnReverseTimePressed();
	UFUNCTION()
	void OnReverseTimeReleased();

	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Rotate(float DeltaTime);

private:
	class ASuperTimeCommandoGameState* GameState;
	bool bHasMoved;
};
