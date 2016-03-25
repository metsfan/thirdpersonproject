// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AreaEffectSpell.h"
#include "SlashSpell.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API ASlashSpell : public AAreaEffectSpell
{
	GENERATED_BODY()

	ASlashSpell();

	virtual void BeginPlay() override;
};
