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
	UFUNCTION(BlueprintCallable, Category = "Default")
	virtual void ApplyEffect(TArray<ABaseCharacter*> characters);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UStatusEffect> StatusEffectClass;
};
