// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "MainMenuGameState.generated.h"

/**
 * 
 */

class AMyPlayerState;

UCLASS()
class THIRDPERSONPROJECT_API AMainMenuGameState : public AGameState
{
	GENERATED_BODY()

	AMainMenuGameState();



public:
	UPROPERTY(BlueprintReadOnly, Replicated)
	TArray<AMyPlayerState *> JoinedPlayers;

	UFUNCTION(NetMulticast, Reliable)
		void NotifyPlayerJoinedLobby(const TArray<AMyPlayerState*>& players);
};
