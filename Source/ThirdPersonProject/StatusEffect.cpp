// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "StatusEffect.h"
#include "BaseCharacter.h"

void UStatusEffect::Tick(float DeltaSeconds, ABaseCharacter* Character)
{
	TimeAlive += DeltaSeconds;

	if (TimeSinceTick >= TickTime) {
		TimeSinceTick -= TickTime;

		// Apply Effects
		if (ModHealthPerTick) {
			Character->AddHealth(ModHealthPerTick, Instigator);
		}

		if (ModMovementSpeed > 0) {
			Character->SetMovementSpeedMultiplier(ModMovementSpeed);
		}

		if (ModAttackDamage > 0) {
			Character->SetAttackDamageMultiplier(ModAttackDamage);
		}

		if (ModDefense > 0) {
			Character->SetDefenseMultiplier(ModDefense);
		}

		if (ModSize > 0) {
			Character->SetSizeScale(ModSize);
		}
	}
}


