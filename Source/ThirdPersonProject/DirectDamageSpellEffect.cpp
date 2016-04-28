// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "DirectDamageSpellEffect.h"
#include "BaseCharacter.h"


void UDirectDamageSpellEffect::ApplyEffect_Implementation(const TArray<ABaseCharacter*>& Characters)
{
	for (auto Character : Characters) {
		Character->AddHealth(Damage * -1, Cast<ABaseCharacter>(this->GetOwner()->GetOwner()));
	}
}

