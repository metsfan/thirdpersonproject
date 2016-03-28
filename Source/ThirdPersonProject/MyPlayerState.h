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
	
	void Update(ABaseCharacter* Character);

	bool IsDead() { return Health == 0;  }
};
