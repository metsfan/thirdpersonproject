// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileSpell.h"
#include "BaseCharacter.h"
#include "HomingProjectileSpell.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API AHomingProjectileSpell : public AProjectileSpell
{
	GENERATED_BODY()

	TWeakObjectPtr<ABaseCharacter> Target;
	
	virtual void Tick(float DeltaSeconds) override;
};
