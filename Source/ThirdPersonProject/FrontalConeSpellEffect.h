// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpellEffect.h"
#include "FrontalConeSpellEffect.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class THIRDPERSONPROJECT_API UFrontalConeSpellEffect : public USpellEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		float Radius;
	
	UPROPERTY(BlueprintReadWrite)
		float Length;
};
