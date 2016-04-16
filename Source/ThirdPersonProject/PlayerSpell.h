// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SpellData.h"
#include "PlayerSpell.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UPlayerSpell : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		USpellData* Data;

	UPROPERTY(BlueprintReadOnly)
		float CooldownRemaining;

	UPROPERTY(BlueprintReadOnly)
		FKey Hotkey;
	
};
