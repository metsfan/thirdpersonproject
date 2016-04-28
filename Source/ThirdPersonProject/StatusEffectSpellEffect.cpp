// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "StatusEffectSpellEffect.h"

void UStatusEffectSpellEffect::ApplyEffect_Implementation(const TArray<ABaseCharacter*>& Characters)
{
	for (auto Character : Characters) {
		Character->AddStatusEffect(StatusEffectClass, Cast<ABaseCharacter>(this->GetOwner()->GetInstigator()));
	}
}


