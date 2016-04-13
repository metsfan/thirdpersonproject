// Fill out your copyright notice in the Description page of Project Settings.
#include "ThirdPersonProject.h"
#include "MainGameState.h"
#include "UnrealNetwork.h"
#include "MainPlayerController.h"

void AMainGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, GameStartCountdown);
	DOREPLIFETIME(AMainGameState, ConnectedPlayersArray);
}

void AMainGameState::AddPlayerState(APlayerState* Player)
{
	Super::AddPlayerState(Player);

	if (Player->PlayerId > 0) {
		OnPlayerAdded.Broadcast(Cast<AMyPlayerState>(Player));
	}

	ConnectedPlayersMap.Empty();
}

void AMainGameState::OnPlayerJoined_Implementation(AMyPlayerState* NewPlayer)
{
}

void AMainGameState::RemovePlayerState(APlayerState* Player)
{
	Super::RemovePlayerState(Player);

	if (Player->PlayerId > 0) {
		OnPlayerRemoved.Broadcast(Cast<AMyPlayerState>(Player));
	}

	ConnectedPlayersMap.Empty();
}

const TMap<int32, AMyPlayerState*>& AMainGameState::GetConnectedPlayers()
{
	if (ConnectedPlayersMap.Num() == 0) {
		for (auto player : ConnectedPlayersArray) {
			ConnectedPlayersMap.Emplace(player->PlayerId, player);
		}
	}

	return ConnectedPlayersMap;
}


void AMainGameState::TrackKill(int32 PlayerId)
{
	auto Players = this->GetConnectedPlayers();
	if (Players.Contains(PlayerId)) {
		Players[PlayerId]->Kills += 1;
	}
}

void AMainGameState::TrackAssist(int32 PlayerId)
{
	auto Players = this->GetConnectedPlayers();
	if (Players.Contains(PlayerId)) {
		Players[PlayerId]->Assists += 1;
	}
}
