// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "MainPlayerController.h"
#include "MyPlayerState.h"
#include "MainGameState.generated.h"

/**
 * 
 */

UCLASS()
class THIRDPERSONPROJECT_API AMainGameState : public AGameState
{
	friend class AThirdPersonProjectGameMode;

	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 GameStartCountdown;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerAddedSignature, class AMyPlayerState*, Player);
	FPlayerAddedSignature OnPlayerAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerRemovedSignature, class AMyPlayerState*, Player);
	FPlayerAddedSignature OnPlayerRemoved;


	virtual void AddPlayerState(APlayerState* Player);
	virtual void RemovePlayerState(APlayerState* Player);

	const TMap<int32, AMyPlayerState*>& GetConnectedPlayers();

	void TrackKill(int32 PlayerId);
	void TrackAssist(int32 PlayerId);

	UFUNCTION(NetMulticast, Reliable)
	void OnPlayerJoined(AMyPlayerState* NewPlayer);

	UPROPERTY(Replicated, BlueprintReadOnly)
	TArray<AMyPlayerState *> ConnectedPlayersArray;

private:
	

	TMap<int32, AMyPlayerState*> ConnectedPlayersMap;
};
