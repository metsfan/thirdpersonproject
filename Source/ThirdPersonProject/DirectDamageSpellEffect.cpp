// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "DirectDamageSpellEffect.h"
#include "BaseCharacter.h"


void UDirectDamageSpellEffect::ApplyEffect(TArray<ABaseCharacter*> characters)
{
	for (auto character : characters) {
		character->AddHealth(Damage * -1, Cast<ABaseCharacter>(this->GetOwner()->GetOwner()));
	}
}

