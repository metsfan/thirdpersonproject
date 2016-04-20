// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileSpell.h"
#include "FlamestrikeSpell.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API AFlamestrikeSpell : public AProjectileSpell
{
	GENERATED_BODY()
	
	
		virtual void OnCollision(class AActor* OtherActor) override;
	
};
