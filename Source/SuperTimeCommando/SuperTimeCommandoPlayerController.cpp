// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SuperTimeCommando.h"
#include "SuperTimeCommandoPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "SuperTimeCommandoCharacter.h"
#include "SuperTimeCommandoGameState.h"
#include "ActorHistory.h"

ASuperTimeCommandoPlayerController::ASuperTimeCommandoPlayerController()
{
	ActorHistory = CreateDefaultSubobject<UActorHistory>(TEXT("ActorHistory"));
	ActorHistory->SetupAttachment(RootComponent);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ASuperTimeCommandoPlayerController::BeginPlay()
{
	GameState = GetWorld()->GetGameState<ASuperTimeCommandoGameState>();
	ActorHistory->PushSpawn();
	bHasMoved = true;
}

void ASuperTimeCommandoPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (GameState->bIsTimeBackward)
	{
		ActorHistory->PopCheckpoint();
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

void ASuperTimeCommandoPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASuperTimeCommandoPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ASuperTimeCommandoCharacter* MyPawn = Cast<ASuperTimeCommandoCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UNavigationSystem::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ASuperTimeCommandoPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ASuperTimeCommandoPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ASuperTimeCommandoPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ASuperTimeCommandoPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ASuperTimeCommandoPlayerController::OnReverseTimePressed()
{
	GameState->bIsTimeBackward = true;
}

void ASuperTimeCommandoPlayerController::OnReverseTimeReleased()
{
	GameState->bIsTimeBackward = false;
}


void ASuperTimeCommandoPlayerController::MoveForward(float Value)
{
	if (Value != 0.0f && !GameState->bIsTimeBackward)
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
	if (Value != 0.0f && !GameState->bIsTimeBackward)
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
