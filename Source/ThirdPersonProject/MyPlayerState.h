// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"



/**
 * 
 */

class ABaseCharacter;

UCLASS()
class THIRDPERSONPROJECT_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

		AMyPlayerState();

public:
	UPROPERTY(BlueprintReadOnly, Replicated)
		float Health;

	UPROPERTY(BlueprintReadOnly, Replicated)
		float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Replicated)
		float HealthPercent;

	UPROPERTY(BlueprintReadOnly, Replicated)
		float Energy;

	UPROPERTY(BlueprintReadOnly, Replicated)
		float MaxEnergy;

	UPROPERTY(BlueprintReadOnly, Replicated)
		float EnergyPercent;

	UPROPERTY(BlueprintReadOnly, Replicated)
		FString Name;

	UPROPERTY(BlueprintReadOnly, Replicated)
		bool ReadyToRestart;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 Kills;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 Assists;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 DamageDone;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 DamageTaken;

	UPROPERTY(BlueprintReadWrite, Replicated)
		bool ReadyToPlay;

	UPROPERTY(BlueprintReadWrite, Replicated)
		bool Initialized;

	UFUNCTION(Server, Reliable, WithValidation)
	void SetPlayerReady(bool ready);
	
	void Update(ABaseCharacter* Character);

	bool IsAlive() { return Health > 0;  }

	virtual void CopyProperties(class APlayerState* PlayerState) override;
};
