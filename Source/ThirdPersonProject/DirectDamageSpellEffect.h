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
	UFUNCTION(BlueprintCallable, Category = "Default")
		virtual void ApplyEffect(TArray<ABaseCharacter*> characters);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Damage;
};
