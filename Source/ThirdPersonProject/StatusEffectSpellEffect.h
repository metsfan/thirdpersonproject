// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpellEffect.h"
#include "StatusEffect.h"
#include "StatusEffectSpellEffect.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class THIRDPERSONPROJECT_API UStatusEffectSpellEffect : public USpellEffect
{
	GENERATED_BODY()
	
public:
	virtual void ApplyEffect_Implementation(const TArray<ABaseCharacter*>& Characters);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UStatusEffect> StatusEffectClass;
};
