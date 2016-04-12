// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "SpawnPoint.h"
#include "ThirdPersonProjectGameMode.generated.h"

UCLASS(minimalapi)
class AThirdPersonProjectGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AThirdPersonProjectGameMode();
	~AThirdPersonProjectGameMode();
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;

	void RestartGameIfAllReady();

	void GameStartTimerCallback();
	virtual void PostLogin(APlayerController * NewPlayer) override;

protected:
	void StartMatch() override;
	void EndMatch() override;

private:
	TArray<ASpawnPoint *> SpawnPoints;
	FTimerHandle SpawnTimer;
	FTimerHandle GameStartTimer;

	void UpdateSpawnPoints();

	void SpawnEnemies();

	void BeginSpawningEnemies();
};



