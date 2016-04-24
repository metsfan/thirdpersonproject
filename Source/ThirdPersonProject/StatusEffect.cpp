// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "StatusEffect.h"
#include "BaseCharacter.h"

UStatusEffect::UStatusEffect(): Super()
{
	MaxStacks = FMath::Max(MaxStacks, 1);
}

void UStatusEffect::Tick(float DeltaSeconds, ABaseCharacter* Character)
{
	TimeAlive += DeltaSeconds;
	TimeSinceTick += DeltaSeconds;

	if (TimeSinceTick >= TickTime) {
		TimeSinceTick -= TickTime;

		// Apply Damage Effects, if needed
		if (ModHealthPerTick) {
			Character->AddHealth(ModHealthPerTick * StackCount, Instigator);
		}
	}

	// Apply all other effects
	Character->SetMovementSpeedMultiplier(ModMovementSpeed * StackCount);
	Character->SetAttackDamageMultiplier(ModAttackDamage * StackCount);
	Character->SetDefenseMultiplier(ModDefense * StackCount);
	Character->SetSizeScale(ModSize * StackCount);
}

void UStatusEffect::Refresh()
{
	TimeAlive = 0;
}

void UStatusEffect::AddStack()
{
	StackCount = FMath::Min(MaxStacks, StackCount + 1);
	this->Refresh();
}


