// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MainMenuGameMode.h"
#include "MainMenuGameState.h"
#include "MainPlayerController.h"

void AMainMenuGameMode::CheckIfGameReady()
{
	auto gameState = Cast<AMainMenuGameState>(GetWorld()->GetGameState());

	bool allReady = true;
	for (auto player : gameState->JoinedPlayers) {
		allReady = player->ReadyToPlay && allReady;
	}

	if (allReady) {
		//UGameplayStatics::OpenLevel(this, TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"));
		//bUseSeamlessTravel = true;
 		GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen", true);
	}
}