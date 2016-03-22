// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MainMenuGameState.h"
#include "UnrealNetwork.h"

AMainMenuGameState::AMainMenuGameState() : Super()
{
	bReplicates = true;
}

void AMainMenuGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainMenuGameState, JoinedPlayers);
}
