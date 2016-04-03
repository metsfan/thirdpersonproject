// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MainGameState.h"
#include "UnrealNetwork.h"

void AMainGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, GameStartCountdown);
}

void AMainGameState::AddPlayerState(APlayerState* Player)
{
	Super::AddPlayerState(Player);

	if (Player->PlayerId > 0) {
		auto myPlayer = Cast<AMyPlayerState>(Player);
		ConnectedPlayers.Emplace(Player->PlayerId, myPlayer);

		OnPlayerAdded.Broadcast(myPlayer);
	}
}

void AMainGameState::RemovePlayerState(APlayerState* Player)
{
	Super::RemovePlayerState(Player);

	OnPlayerRemoved.Broadcast(Cast<AMyPlayerState>(Player));
}