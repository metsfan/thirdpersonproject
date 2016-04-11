// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MainMenuGameState.h"
#include "UnrealNetwork.h"
#include "MainPlayerController.h"

AMainMenuGameState::AMainMenuGameState() : Super()
{
	bReplicates = true;
}

void AMainMenuGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainMenuGameState, JoinedPlayers);
}

void AMainMenuGameState::NotifyPlayerJoinedLobby_Implementation(const TArray<AMyPlayerState*>& players)
{
	auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	pc->NotifyPlayerJoinedLobby(players);
}
