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

	UFUNCTION()
	void OnRep_ConnectedPlayers();

	UPROPERTY(ReplicatedUsing = OnRep_ConnectedPlayers)
	TMap<int32, AMyPlayerState*> ConnectedPlayers;

private:
	
	
};
