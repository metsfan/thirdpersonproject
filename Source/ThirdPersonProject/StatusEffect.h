// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SpellData.h"
#include "StatusEffect.generated.h"

/**
 * 
 */

class ABaseCharacter;

UCLASS(Blueprintable)
class THIRDPERSONPROJECT_API UStatusEffect : public UObject
{
	GENERATED_BODY()
	
public:
	UStatusEffect();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Duration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TickTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ModHealthPerTick;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ModMovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ModAttackDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ModDefense;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ModSize;

	UPROPERTY(BlueprintReadOnly)
		ABaseCharacter* Instigator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxStacks;

	virtual void Tick(float DeltaSeconds, ABaseCharacter* Character);

	void Refresh();
	void AddStack();

	bool IsExpired() { return TimeAlive >= Duration; }

private:
	float TimeSinceTick = 0;
	float TimeAlive = 0;
	int32 StackCount = 1;

};
