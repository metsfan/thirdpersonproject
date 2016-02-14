// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonProject.h"
#include "ThirdPersonProjectGameMode.h"
#include "ThirdPersonProjectCharacter.h"
#include "GameFramework/HUD.h"
#include "MainPlayerController.h"

AThirdPersonProjectGameMode::AThirdPersonProjectGameMode() :
	AGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PlayerControllerClass = AMainPlayerController::StaticClass();
	}
}
