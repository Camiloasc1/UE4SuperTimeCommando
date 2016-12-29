// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SuperTimeCommando.h"
#include "SuperTimeCommandoGameMode.h"
#include "SuperTimeCommandoPlayerController.h"
#include "SuperTimeCommandoCharacter.h"
#include "SuperTimeCommandoGameState.h"

ASuperTimeCommandoGameMode::ASuperTimeCommandoGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASuperTimeCommandoPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameStateClass = ASuperTimeCommandoGameState::StaticClass();
}
