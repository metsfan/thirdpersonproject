// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MainGameState.h"

void AMainGameState::ServerSetPlayerName(const FGuid& id, const FString& name)
{
	auto controller = ConnectedPlayers[id];
}