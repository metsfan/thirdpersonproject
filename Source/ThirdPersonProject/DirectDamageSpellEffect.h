// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpellEffect.h"
#include "DirectDamageSpellEffect.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class THIRDPERSONPROJECT_API UDirectDamageSpellEffect : public USpellEffect
{
	GENERATED_BODY()

public:

	virtual void ApplyEffect_Implementation(const TArray<ABaseCharacter*>& Characters);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Damage;
};
