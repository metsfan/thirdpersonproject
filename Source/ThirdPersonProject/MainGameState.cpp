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
}

void AMainGameState::RemovePlayerState(APlayerState* Player)
{
	Super::RemovePlayerState(Player);

	OnPlayerRemoved.Broadcast(Cast<AMyPlayerState>(Player));
}

TMap<int32, AMyPlayerState*> AMainGameState::GetConnectedPlayers()
{
	TMap<int32, AMyPlayerState*> out;
	for (auto player : PlayerArray) {
		if (player->PlayerId > 0) {
			out.Emplace(player->PlayerId, Cast<AMyPlayerState>(player));
		}
	}

	return out;
}