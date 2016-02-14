// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "DirectDamageSpellEffect.h"


void UDirectDamageSpellEffect::ApplyEffect(TArray<AThirdPersonProjectCharacter*> characters)
{
	for (auto character : characters) {
		character->AddHealth(Damage * -1);
	}
}

