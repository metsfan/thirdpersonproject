// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "StatusEffectSpellEffect.h"

void UStatusEffectSpellEffect::ApplyEffect(TArray<ABaseCharacter*> characters)
{
	for (auto Character : characters) {
		Character->AddStatusEffect(StatusEffectClass, Cast<ABaseCharacter>(this->GetOwner()->GetInstigator()));
	}
}


