// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "SpellCPP.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

	ABaseAIController();

	virtual void Tick(float deltaSeconds) override;

public:
	virtual TSubclassOf<ASpellCPP> GetNextSpell();
	
};
