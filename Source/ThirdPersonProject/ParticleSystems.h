// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "ParticleSystems.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UParticleSystems : public UObject
{
	GENERATED_BODY()

public:
	static UParticleSystem* GetParticleSystem(const FString& name);

private:
	UParticleSystems();

	static UParticleSystems* GetInstance();

	TMap<FString, UParticleSystem*> ParticleSystems;
	
};
