// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SuperTimeCommando.h"
#include "SuperTimeCommandoPlayerController.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "SuperTimeCommandoCharacter.h"
#include "SuperTimeCommandoGameState.h"
#include "ActorHistory.h"
#include "Util/Util.h"

ASuperTimeCommandoPlayerController::ASuperTimeCommandoPlayerController()
{
	ActorHistory = CreateDefaultSubobject<UActorHistory>(TEXT("ActorHistory"));
	ActorHistory->SetupAttachment(RootComponent);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ASuperTimeCommandoPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();
	GameState->OnGameEnd.AddDynamic(this, &ASuperTimeCommandoPlayerController::OnGameEnd);

	ActorHistory->PushSpawn();
	bHasMoved = true;
}

void ASuperTimeCommandoPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (!bHasMoved)
	{
		Rotate(DeltaTime);
	}

	if (GameState->IsTimeBackward())
	{
		ActorHistory->PopCheckpoint([&](const FCheckpoint& Checkpoint)
			{
				GetPawn()->SetActorTransform(Checkpoint.Transform);
			});
	}
	else
	{
		if (bHasMoved)
		{
			ActorHistory->PushCheckpoint();
			bHasMoved = false;
		}
	}
}

void ASuperTimeCommandoPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Movement
	InputComponent->BindAxis("MoveForward", this, &ASuperTimeCommandoPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASuperTimeCommandoPlayerController::MoveRight);

	// Time rewind
	InputComponent->BindAction("ReverseTime", IE_Pressed, this, &ASuperTimeCommandoPlayerController::OnReverseTimePressed);
	InputComponent->BindAction("ReverseTime", IE_Released, this, &ASuperTimeCommandoPlayerController::OnReverseTimeReleased);
}

void ASuperTimeCommandoPlayerController::OnGameEnd(bool bHasWin)
{
	DisableInput(this);
}

void ASuperTimeCommandoPlayerController::OnReverseTimePressed()
{
	GameState->SetTimeBackward(true);
}

void ASuperTimeCommandoPlayerController::OnReverseTimeReleased()
{
	GameState->SetTimeBackward(false);
}

void ASuperTimeCommandoPlayerController::MoveForward(float Value)
{
	if (Value != 0.0f && !GameState->IsTimeBackward())
	{
		bHasMoved = true;

		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// add movement in that direction
		GetPawn()->AddMovementInput(Direction, Value);
	}
}

void ASuperTimeCommandoPlayerController::MoveRight(float Value)
{
	if (Value != 0.0f && !GameState->IsTimeBackward())
	{
		bHasMoved = true;

		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		GetPawn()->AddMovementInput(Direction, Value);
	}
}

void ASuperTimeCommandoPlayerController::Rotate(float DeltaTime)
{
	ASuperTimeCommandoCharacter* PossessedPawn = Cast<ASuperTimeCommandoCharacter>(GetPawn());

	FVector Forward = PossessedPawn->GetActorForwardVector() * -1;
	FVector Target = PossessedPawn->GetActorLocation() - PossessedPawn->GetCursorToWorld()->GetComponentLocation();

	float Angle = GUtil::SignedAngle2D(Forward, Target);
	if (FMath::Abs(Angle) > 5)
	{
		FRotator Rotator = PossessedPawn->GetActorRotation();
		Angle /= FMath::Abs(Angle);
		Rotator.Yaw += Angle * DeltaTime * PossessedPawn->GetCharacterMovement()->RotationRate.Yaw;
		PossessedPawn->SetActorRotation(Rotator);
	}
}
