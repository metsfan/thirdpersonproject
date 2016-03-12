// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "MainPlayerController.h"
#include "MainGameState.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API AMainGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	float GameStartCountdown;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetPlayerName(uint32 id, const FString& name);

private:
	TMap<uint32, AMainPlayerController*> ConnectedPlayers;
};
