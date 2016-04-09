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
		OnPlayerAdded.Broadcast(myPlayer);
	}

	ConnectedPlayers.Empty();
}

void AMainGameState::RemovePlayerState(APlayerState* Player)
{
	Super::RemovePlayerState(Player);

	OnPlayerRemoved.Broadcast(Cast<AMyPlayerState>(Player));

	ConnectedPlayers.Empty();
}

const TMap<int32, AMyPlayerState*>& AMainGameState::GetConnectedPlayers()
{
	if (ConnectedPlayers.Num() == 0) {
		for (auto player : PlayerArray) {
			if (player->PlayerId > 0) {
				ConnectedPlayers.Emplace(player->PlayerId, Cast<AMyPlayerState>(player));
			}
		}
	}

	return ConnectedPlayers;
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
